#include "path.h"
inherit "/std/room/basic_room";
void setup() {
  set_short( "bedroom" );
  set_long( "This is a small bedroom above the shop.  There is a window "
            "in the north wall.\n");
  set_light( 60 );
  set_room_size( 10 );
  set_zone( "Tiny Town");
  add_exit("window", PATH+"shop-ledge", "window");
  add_exit("down", PATH +"item-shop", "stair" );
  modify_exit("down", ({ "downgrade", 9 }));
}