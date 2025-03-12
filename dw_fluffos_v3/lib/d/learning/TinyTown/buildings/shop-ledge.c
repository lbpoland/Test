#include "path.h"
inherit "/std/room/rooftop";
void setup() {
  set_short( "small ledge" );
  set_long( "This is a small ledge just outside the upstairs window of "
						"the item shop.\n");
  set_room_size( 10 );
	set_slope(60, "ledge", TTOWNROADS + "womble01");
	set_weak_messages("The ledge crumbles under your weight.\n",
										"$short$ falls from the crumbling ledge.",
										"$short$ comes crashing to the ground.",
                                                                                "The ledge makes a strange sound.");
	set_weak_roof(2500, TTOWNROADS + "womble01");
	add_exit("window", PATH+"shop-upstairs", "window");
	set_wall( ({ "bottom", ({ TTOWNROADS + "womble01", 200 }), }) );
	set_wall( ({ "move", ({ "down", 30, TTOWNROADS + "womble01",
														"$N climb$s down from above." }) }) );
}