#include <terrain_map.h>
#include "path.h"
inherit TERRAIN_MAP_HANDLER_BASE;
string query_map_file() {
    return __DIR__ + "terrain";
}
void setup_handler() {
    set_newline_mode(0);
   set_visible_distance(5);
   add_obstacle_type("H", "a lush, thick hedge surrounds the small garden",
     "hedge", "The hedge surrounds the garden, stretching thick and "
     "impenetrable towards the sky, protecting anyone in the garden from the "
     "gawking eyes of passers-by.");
   add_obstacle_type("*", "s big high lump that you cannot avoid looking at",
     "lump", "The lump is very lumpy.");
   add_feature("lump",
               16, 3,
               1, 1,
               15,
               ({
                  "a lump towers above you to the $D",
                }),
               "lump", "A lumpy thing that lumps around.",
               ({
                  "a lump at night to the $D",
                }),
               "It looks just like a lump, even though it is dark.");
   add_road_type("=", __DIR__ "plainpath",
     "", "a nice sandy path leads through the plains.");
   add_road_type("+", __DIR__ "woodpath",
     "", "a nice sandy path leads through the woods.");
   add_road_special_type("-", __DIR__ "desertpath",
     3,
     1,
     0,
     "", "a nice sandy path leads through the woods.");
   add_room_type("L", __DIR__ "plains");
   add_room_type("W", __DIR__ "woods");
   add_room_type("d", __DIR__ "desert");
   add_exit_at(0, 1, "west", GUMBOOT + "gumboot5", "road");
   add_exit_at(0, 18, "west", RABBIT + "rabbit4", "road");
}