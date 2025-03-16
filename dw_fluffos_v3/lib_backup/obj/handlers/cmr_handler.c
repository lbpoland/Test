#include <cmr.h>
#include <colour.h>
#include <library.h>
#define SAVE_FILE "/save/cmr_handler"
inherit "/std/object";
string *colour_names;
mapping colour_details;
string *material_names;
mapping material_details;
void load_cmr_handler();
void save_cmr_handler();
void create();
string add_colour( string word, int fine, int crude, int qp_thresh,
                int sp_thresh );
int *query_colour_details( string word );
int delete_colour( string word );
string *query_colour_names();
string identify_colour( string word, object player );
string add_material( string word, int colour, int type, int skill_reqd,
                  int skill_thresh );
int *query_material_details( string word );
int delete_material( string word );
string *query_material_names();
string identify_material( string word, object player, int article );
string query_material_adjective( string word );
void load_cmr_handler() {
  if ( file_size( SAVE_FILE +".o" ) > 0 )
    unguarded((: restore_object, SAVE_FILE :));
}
void save_cmr_handler() {
  unguarded((: save_object, SAVE_FILE :));
}
void create() {
  colour_names = ({ });
  colour_details = ([ ]);
  material_names = ({ });
  material_details = ([ ]);
  ::create();
  load_cmr_handler();
}
string add_colour( string word, int fine, int crude, int qp_thresh,
                int sp_thresh ) {
  int temp;
  temp = member_array( word, colour_names );
  if ( temp != -1 ) return "colour already exists";
  colour_names += ({ word });
  colour_details += ([ word : ({ fine, crude, qp_thresh, sp_thresh }) ]);
  save_cmr_handler();
  return "the colour "+ word +", a shade of "+ ( ( fine == crude )?
         "pure ":MODIFIERS[fine] ) + COLOURS[crude] +", with thresholds of "+
         qp_thresh +" xp and "+ sp_thresh +" sp";
}
int *query_colour_details( string word ) {
  int temp;
  temp = member_array( word, colour_names );
  if ( temp == -1 ) return ({ -1 });
  return colour_details[word];
}
int delete_colour( string word ) {
  int temp;
  temp = member_array( word, colour_names );
  if ( temp == -1 ) return 0;
  colour_names -= ({ word });
  colour_details = m_delete( colour_details, word );
  save_cmr_handler();
  return 1;
}
string *query_colour_names() { return colour_names + ({ }); }
string identify_colour( string word, object player ) {
  int temp, *args;
  temp = member_array( word, colour_names );
  if ( temp == -1 )
    return "unknown colour";
  args = allocate( 4 );
  args = colour_details[word];
  if ( !player )
    return word;
  switch ( ( ( LIBRARY->query_quest_points(player->query_name()) ) > args[2] )+
           ( ( player->query_max_gp() ) > args[3] ) ) {
  case 0:
    return COLOURS[args[1]];
  case 1:
    return ( ( ( args[0] == args[1] )?"pure ":MODIFIERS[args[0]] ) +
             COLOURS[args[1]] );
  default:
    return word;
  }
}
string add_material( string word, int colour, int type, int skill_reqd,
                  int skill_thresh ) {
  int temp;
  string text;
  temp = member_array( word, material_names );
  if ( temp != -1 ) return "material already exists";
  material_names += ({ word });
  material_details += ([ word : ({ colour, type, skill_reqd,
                         skill_thresh }) ]);
  save_cmr_handler();
  if ( !skill_reqd )
    text = " that is always recognised";
  else
    if ( skill_reqd == LEARNT )
      text = " that is recognised through knowledge";
    else
      text = " that has a threshold of "+ skill_thresh +" in "+
             SKILLS[skill_reqd];
  return word +", a"+ ( ( colour == COL_ORANGE )?"n ":" " ) +
         COLOURS[colour] +" "+ MATERIALS[type] + text;
}
int *query_material_details( string word ) {
  int temp;
  temp = member_array( word, material_names );
  if ( temp == -1 ) return ({ -1 });
  return material_details[word];
}
int delete_material( string word ) {
  int temp;
  temp = member_array( word, material_names );
  if ( temp == -1 ) return 0;
  material_names -= ({ word });
  material_details = m_delete( material_details, word );
  save_cmr_handler();
  return 1;
}
string *query_material_names() { return material_names + ({ }); }
string identify_material( string word, object player, int article ) {
  int temp, *args;
  string prefix;
  temp = member_array( word, material_names );
  if ( temp == -1 ) return "unknown material";
  args = allocate( 4 );
  args = material_details[word];
  prefix = ( ( article )?"a"+ ( ( args[0] == COL_ORANGE )?"n ":" " ):"" );
   if ( !args[ 2 ] || !player )
      return word;
  if ( args[2] == LEARNT )
    if ( member_array( word,
        (string *)CMR_LIBRARY->query_known_materials( player->query_name() ) )
        == -1 )
      return prefix + COLOURS[ args[ 0 ] ] +" "+
          MATERIALS[ args[ 1 ] ];
    else
      return word;
  if ( ( player->query_skill_bonus( SKILLS[args[2]] ) ) > args[3] )
    return word;
  else return prefix + COLOURS[args[0]] +" "+ MATERIALS[args[1]];
}
string query_material_adjective( string word ) {
  int temp, *args;
  temp = member_array( word, material_names );
  if ( temp == -1 ) return "an unknown material";
  args = allocate( 4 );
  args = material_details[word];
  return COLOURS[args[0]] +" "+ MATERIAL_ADJECTIVES[args[1]];
}
string query_material_ansi_colour( string word ) {
  int temp, *args;
  temp = member_array( word, material_names );
  if ( temp == -1 ) return "";
  args = allocate( 4 );
  args = material_details[word];
  return ANSI_COLOURS[args[0]];
}