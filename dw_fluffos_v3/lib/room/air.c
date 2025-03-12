#include <position.h>
#include <soul.h>
#include <talker.h>
#define TIME_LIMIT 15
#define BROOMSTICK "/d/guilds/witches/items/broomstick"
#define GRANNY "/d/guilds/witches/chars/granny_weatherwax"
inherit "/std/outside";
int screen_command( string cmd );
string *people;
string *allowed_commands = ({ "l", "look", "glance",  });
void setup() {
  set_light( 100 );
  set_short( "high above the Disc" );
  add_property( "determinate", "" );
  set_day_long( "You are high above the Disc, flying through the "
      "air.\n" );
  set_night_long( "You are high above the Disc, flying through the "
      "night sky.\n" );
  add_item( ({ "down", "disc", }), "The Disc spreads out below "
      "you, much too far away to make out anything distinctly." );
  people = ({ });
}
int query_flying( string who ) {
  if( member_array( who, people ) > -1 )
    return 1;
  else
    return 0;
}
void drop_non_living( object ob ) {
  object broom = load_object( BROOMSTICK );
  object player;
  object dest;
  if( ob->query_corpse() ) {
    string name = ob->query_owner();
    name = lower_case( explode( name, " " )[0] );
    player = find_player( name );
  }
  if( !player )
    player = load_object( GRANNY );
  if( !broom || !player )
    return;
  dest = broom->random_dest( player );
  ob->move( dest, "$N streaks down from above and crashes into the ground "
                  "with a thud, narrowly missing you.",
                  "$N disappear$s from view far below." );
}
void down_they_go( object witch, object *riding ) {
  object broom;
  object *brooms;
  object *held;
  string path;
  object dest;
  if( !witch )
    return;
  people -= ({ witch->query_name() });
  if( environment( witch ) != this_object() )
    return;
  if( sizeof( riding ) && riding[0] != 0 ) {
    broom = riding[0];
    tell_creator( "tannah", "broom: %O\n", broom );
  } else {
    brooms = match_objects_for_existence( "witches' broomstick",
                                          ({ witch }), 0 );
    if( !sizeof( brooms ) ) {
      if( witch->query_auto_loading() ) {
        call_out( (: down_they_go :), TIME_LIMIT, witch, riding );
        tell_object( witch, "Your thighs twitch reflexively and your "
                            "hands scrabble at the air, searching "
                            "for your broom.\n" );
        return;
      } else {
        broom = load_object( BROOMSTICK );
      }
    } else if( sizeof( brooms ) > 1 ) {
      held = filter( brooms, (: $1->query_holder() == $(witch) :) );
      if( sizeof( held ) )
        broom = held[0];
      else
        broom = brooms[0];
    } else {
      broom = brooms[0];
    }
  }
  path = broom->query_destination();
  if( path )
    dest = load_object( path );
  else
    dest = broom->random_dest(witch);
  tell_creator( "tannah", "Broom: %O\nLanding in: %O\n", broom, dest );
  broom->land( witch, dest );
}
void event_enter( object ob, string message, object from ) {
  if( !living( ob ) ) {
    ob->set_position( "dropping towards the ground" );
    call_out( (: drop_non_living :), 2, ob );
    return;
  }
  ob->command_override( (: screen_command :) );
  people += ({ ob->query_name() });
  call_out( (: down_they_go :), TIME_LIMIT, ob,
            filter( previous_object(-1), (: $1->id( "broomstick" ) :) ) );
}
mixed query_default_position() {
   return ({ "flying through the air" });
}
void event_exit(object ob, string message, object to) {
   tell_object( ob, "You plummet towards the ground.\n" );
   tell_room( this_object(), ob->the_short()
         +" plummets towards the ground.\n", ob );
   STANDING_CMD->position( ob, 1 );
}
int screen_command( string cmd ) {
  string garbage;
  sscanf( cmd, "%s %s", cmd, garbage );
  if( cmd == "END_ALIAS" ||
      (function_exists("query_aliases",this_player()) &&
       member_array( cmd, keys( this_player()->query_aliases() ) ) != -1 ))
    return notify_fail( "" );
  if( member_array( cmd, allowed_commands ) != -1  )
    return 0;
  if( this_player()->query_creator() ) {
    write( "You attempt aerial feats mere mortals dare not.\n" );
    return 0;
  }
  write( ({
      "You don't dare do that while flying so high above the ground.\n",
      "Your broom lurches alarmingly, nearly tossing you to the ground "
          "below.\n",
      "Your concentration wanes and your broom suddenly loses "
          "altitude.\n",
      })[ random( 3 ) ] );
  return 1;
  if( cmd[0] == 39 ) return 0;
  if( cmd[0] == 34 ) return 0;
}
string *query_people() { return people; }