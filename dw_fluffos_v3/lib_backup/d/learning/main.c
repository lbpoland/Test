#include "path.h"
inherit "/std/room/basic_room";
void setup() {
   set_short( "entrance to learning" );
   add_property( "determinate", "the " );
   set_long( "Welcome to the entrance room of the learning domain.  "
            "The purpose of this domain is to help beginning creators, by "
            "giving examples of the way to use the different functions that "
            "are available, and show ways to solve common problems.\n"
            "To see the code used in a room or an object you can use the "
            "commands \"more here\" and \"more <object name>\" "
            "respectively.  If you have something you'd like to see here, "
            "mail "+ CURRENT_LORD +" and suggest it.\n"
            "The search exit will take you to a special room with exits "
            "for each of the keywords defined in the different files in the "
            "domain, this will enable you to search for examples by "
            "selecting keywords, and is also an example of the use of "
            "virtual or cloned rooms.\n"
            "If you want to find examples of how to use specific functions, "
            "use the functions exit.\n"
            );
   set_light( 50 );
   set_co_ord( ({ 30, 0, 40 }) );
   add_exit( "search", PATH + "search", "door" );
   add_exit( "functions", PATH + "functions", "door" );
   add_exit( "common", "/w/common", "door" );
   "/w/common"->add_exit( "learning", ENTRANCE, "door" );
   add_property( "commented functions",
                ({ "set_long", "set_short", "add_property", "set_light",
                   "add_exit" }) );
   add_property( "keywords", ({ "room" }) );
}