#include "path.h"
inherit "/std/room";
void setup()
{
  set_short("first simple room");
  set_long("This is a simple room, have fun with it. To read the code " +
           "simply type 'more here'. For help with more, type 'h' in it.\n");
  set_light(90);
  add_exit("east", ROOM + "exa2", "door");
  set_zone("examples");
}