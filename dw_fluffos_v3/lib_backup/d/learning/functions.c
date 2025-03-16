#include "path.h"
#include <learning.h>
#define PATH LEARNING
inherit "/std/room/basic_room";
string *functions;
int do_list();
int word();
void setup() {
   string word;
   set_short( "room of function examples" );
   add_property( "determinate", "the " );
   set_long( "This is the room that might lead you to better understanding "
            "of how to use some of the functions we have here.\n"
            "Try \"list functions\" to get a list of the functions known by "
            "the room, "
            "take the exit named by the function to get to a room with exits "
            "to the examples.\n"
            "If you have something you'd like to see here, "
            "mail "+ CURRENT_LORD +" and suggest it.\n" );
   set_light( 50 );
   functions = SEARCH->query_functions();
   foreach( word in functions ) {
      add_exit( word, "??", "path" );
      modify_exit( word, ({ "obvious", 0 }) );
   }
   add_exit( "exit", ENTRANCE, "door" );
   add_property( "commented functions",
                ({ "set_long", "set_short", "add_property", "set_light" }) );
   add_property( "keywords", ({ }) );
}
void init() {
  ::init();
  add_command( "list","functions");
}
int do_list() {
   write( sprintf( "The following functions have examples of use:\n%#-*s\n",
                  75, implode( functions, "\n" ) ) );
   return 1;
}
void set_destination( string word ) {
   if( word != "exit" ) {
      modify_exit( word, ({ "dest", SEARCH->find_function_room( word ) }) );
   }
}