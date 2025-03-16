#include "path.h"
inherit "/std/room/basic_room";
string *keywords;
void setup() {
   mixed search_result;
   string word;
   set_short( "primary search room" );
   add_property( "determinate", "the " );
   set_long( "Welcome to the first room for doing keyword searches.  "
            "Take an exit to narrow the search to that keyword.  If less than "
            "five rooms or objects fit the keywords there will also be exits "
            "directly to them.\n" );
   set_light( 50 );
   search_result = SEARCH->get_keywords( ({ }) );
   keywords = search_result[ 0 ];
   foreach( word in keywords ) {
      add_exit( word, "??", "path" );
   }
   add_exit( "exit", ENTRANCE, "door" );
   add_property( "commented functions",
                ({ "add_exit", "set_destination" }) );
   add_property( "keywords", ({ "virtual", "room" }) );
   add_property( "no map", 1 );
}
void set_destination( string keyword ) {
   if( member_array( keyword, ({ "exit", "back", "a", "b", "c", "d", "e" }) ) != -1 )
      return;
   modify_exit( keyword, ({ "dest", SEARCH->find_room( ({ keyword }) ) }) );
}