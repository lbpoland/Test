#include <learning.h>
#define SAVE_FILE SAVEPATH +"search_quit"
inherit "/std/room/basic_room";
mapping locations;
void setup() {
   set_short( "quit handler of the search rooms" );
   set_light( 50 );
   set_long( "You are in the quit_handler of the search rooms of the learning "
            "domain.  In normal use, people only end up in the quit_handler "
            "if something goes wrong, since the event_enter() function will "
            "send them on to the correct place immediately.\n" );
   add_exit( "back", ENTRANCE, "path" );
   locations = ([ ]);
   if ( file_size( SAVE_FILE +".o" ) )
      unguarded( (: restore_object, SAVE_FILE :) );
   call_out( "check_names", 2 );
}
void save_this() { unguarded( (: save_object, SAVE_FILE :) ); }
void check_names() {
   string word;
   foreach ( word in keys( locations ) )
      if ( !"/secure/login"->test_user( word ) )
         locations = m_delete( locations, word );
   save_this();
}
void player_quitting( object player, object place ) {
   if ( player->query_property( "guest" ) )
      return;
   locations[ (string)player->query_name() ] =
         (string *)place->query_keywords();
   if ( !locations[ (string)player->query_name() ] ) {
      locations[ (string)player->query_name() ] =
          (string)place->query_marker();
   }
   save_this();
}
void remove_from_list( object player ) {
   string word;
   word = (string)player->query_name();
   if ( locations[ word ] )
      locations = m_delete( locations, word );
   save_this();
}
void event_enter( object player, string words, object from ) {
   string location, word;
   if( from ) {
      return;
   }
   word = (string)player->query_name();
   if ( !locations[ word ] ) {
      player->move( (string)player->query_start_pos(),
            "$N enter$s the game." );
      return;
   }
   if ( pointerp( locations[ word ] ) ) {
      location = (string)SEARCH->find_room( locations[ word ] );
   } else {
      location = (string)SEARCH->find_function_room( locations[ word ] );
   }
   player->move( location, "$N enter$s the game." );
}