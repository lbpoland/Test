#include "path.h"
#include <map.h>
inherit "/std/room/basic_room";
string marker, *keywords, *exits;
void setup() {
   set_short( "uninitialised search room" );
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
   add_exit( "exit", LEARNING +"search", "path" );
   add_property( "commented functions",
                ({ "set_destination", "query_quit_handler",
                   "query_cloning_info" }) );
   add_property( "keywords", ({ "room", "virtual" }) );
}
string query_marker() {
   return marker;
}
string *query_keywords() {
   if( !keywords ) {
      return ({ });
   }
   return keywords;
}
void set_marker( string word, string *words ) {
   mixed search_result;
   string description, exit;
   int i;
   set_short( "\""+ word +"\" search room" );
   add_property( "determinate", "the " );
   marker = word;
   keywords = words;
   description ="You are in one of the search rooms of the learning domain "
                "and you have chosen the word"+
                ({ " \"", "s \"" })[ sizeof( words ) > 1 ] + word +"\" so far.";
   search_result = SEARCH->get_keywords( words );
   exits = search_result[ 0 ];
   if( sizeof( exits ) ) {
      description += "  Take one of the keyword exits to narrow the search to "
                     "include that keyword.";
      foreach( word in exits ) {
         add_exit( word, "/??", "path" );
      }
   }
   description += "\n";
   if( sizeof( search_result[ 1 ] ) < 6 ) {
      description += "$I$5=Take one of the numbered exits to go to that room.";
      for( i = 0; i < sizeof( search_result[ 1 ] ); i++ ) {
         exit = sprintf( "%s: %s", ({ "1", "2", "3", "4", "5" })[ i ],
                        MAP->query_short( search_result[ 1 ][ i ] ) );
         add_exit( ({ "1", "2", "3", "4", "5" })[ i ],
                  search_result[ 1 ][ i ], "path" );
         description += "\n$C$"+ exit +".";
      }
      description += "$I$0=\n";
   }
   set_long( description );
}
void set_destination( string keyword ) {
   if( member_array( keyword, exits ) != -1 ) {
      modify_exit( keyword, ({ "dest",
         SEARCH->find_room( keywords + ({ keyword }) ) }) );
   }
   if ( find_call_out( "check_empty" ) == -1 )
      call_out( "check_empty", 10 );
}
void check_empty() {
   if ( sizeof( all_inventory( this_object() ) ) )
      return;
   dest_me();
}
string query_quit_handler() { return QUIT_HANDLER; }
mixed *query_cloning_info() {
   return ({ SEARCH, "find_room", keywords });
}
void event_exit( object thing, string mess, object to ) {
   string handler;
   if ( file_name( to ) == "/room/departures" )
      return;
   handler = query_quit_handler();
   if ( (string)to->query_quit_handler() != handler )
      handler->remove_from_list( thing );
}