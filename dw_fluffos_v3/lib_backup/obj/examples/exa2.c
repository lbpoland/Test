#include "path.h"
inherit "/std/room";
void setup()
{
  set_short("second simple room");
  set_long("This is the second example room. It introduces items, and " +
           "aliasing - again use 'more here' to look at it. Over by the " +
           "north wall you can see a table.\n");
  set_light(90);
 add_item("table",
          "The table is one step away from being firewood. Upon it rests " +
          "a blotter.\n");
 add_item( ({ "north wall", "wall" }),
          "It is very flat and is holding up rather a ricketty table.\n");
 add_item("blotter",
          "It is covered in random ink blots.\n");
  add_exit("west", ROOM + "exa1", "door");
  add_exit("east", ROOM + "exa3", "door");
  set_zone("examples");
}