#include "path.h"
#include <map.h>
inherit "/std/room/basic_room";
string function_chosen;
void setup() {
   set_short( "uninitialised search room for functions" );
   set_long( "You are in an uninitialized search room.  "
            "This is an example of a room that gets cloned and configured "
            "afterwards.  In this room, it's the function set_marker that's "
            "used to define its look, and most if the exits as well.  And "
            "the function set_destination that is used to find, possibly "
            "clone and configure, the rooms that fit the keywords you search "
            "for.  The handler called SEARCH in the code, is \""+
            SEARCH +"\" and the one called QUIT_HANDLER, is \""+
            QUIT_HANDLER +"\".\n" );
   add_property( "no map", 1 );
   set_light( 50 );
   add_exit( "exit", PATH +"functions", "path" );
   add_property( "commented functions",
                ({ "set_destination", "query_quit_handler",
                   "query_cloning_info" }) );
   add_property( "keywords", ({ "room", "virtual" }) );
}
string query_marker() {
   return function_chosen;
}
void set_marker( string word ) {
   string description, exit_letter, exit_room, exit;
   set_short( "\""+ word +"\" search room" );
   add_property( "determinate", "the " );
   function_chosen = word;
   description = "You have chosen to see the rooms describing the use of the "
         "function "+ function_chosen +".";
   description += "$I$5=Take one of the lettered exits to go to that room.";
   exit_letter = "a";
   foreach( exit_room in (string *)SEARCH->query_rooms_with_function( word ) ) {
      exit = sprintf( "%s: %s",
                     exit_letter,
                     (string)MAP->query_short( exit_room ) );
      add_exit( exit_letter, exit_room, "path" );
      description += "\n$C$"+ exit +".";
      exit_letter[ 0 ]++;
   }
   description += "$I$0=\n";
   set_long( description );
}
void check_empty() {
   if ( sizeof( all_inventory( this_object() ) ) )
      return;
   dest_me();
}
string query_quit_handler() { return QUIT_HANDLER; }
mixed *query_cloning_info() {
   return ({ SEARCH, "find_function_room", function_chosen });
}
void event_exit( object thing, string mess, object to ) {
   string handler;
   if ( find_call_out( "check_empty" ) == -1 )
      call_out( "check_empty", 10 );
   if ( file_name( to ) == "/room/departures" )
      return;
   handler = query_quit_handler();
   if ( (string)to->query_quit_handler() != handler )
      handler->remove_from_list( thing );
}