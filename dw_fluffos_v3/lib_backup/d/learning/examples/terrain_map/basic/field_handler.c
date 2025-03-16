#include <terrain_map.h>
inherit TERRAIN_MAP_HANDLER_BASE;
string query_map_file() { return __DIR__ + "field"; }
void  setup_handler()
{
   add_obstacle_type("*", "A tall fence blocks your way to the $D.",
                "fence", "A tall, unclimable wooden fence.");
   add_room_type(".", __DIR__ + "field");
   add_road_type(",", __DIR__ + "path",
            "The path meanders $D.",
            "A small path meanders its way across the field to the $D.",
            "path",
            "The path has been trampled down by the hooves of time.");
   add_feature("bigtree", 4, 1, 1, 1, 4,
                ({ "A giant tree towers over you to the $D.",
                   "A little way to the $D, you can see a huge tree.",
                   "You can just make out a large tree, a way off in an "
                   "$Derly direction." }),
                   "tree", "A fairly large, and quite beautiful tree." );
   set_feature_chats("bigtree",
                     ({ "The branches on the tree to the $D "
                        "sway slightly in the breeze." }) );
   add_exit_at(2, 0, "south", __DIR__ + "entrance", "road");
}