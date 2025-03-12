#include "path.h"
inherit "/std/shops/item_shop";
void setup() {
  add_property( "determinate", "A " );
  set_short( "simple item shop" );
  set_long( "This is a nice looking shop.  Obviously your shop would have "
            "a much more interesting description.\n");
  set_light( 60 );
  set_room_size( 10 );
  set_zone( "Tiny Town");
  add_exit( "north", TTOWNROADS +"womble01", "door" );
  modify_exit( "nouth", ({
    "exit mess", "Chimes start playing as $N "
      "leave$s through the north door.",
      "enter mess", ({
        1,
          "$N enters from the south.",
          "$N enter from the south." }),
      "move mess", "Chimes start playing as you leave the shop.\n"
      }));
  add_exit("up", PATH+"shop-upstairs", "stair");
  modify_exit("up", ({"upgrade", 9 }));
}