#include "path.h"
inherit "/std/room";
void setup()
{
  set_short("third simple room");
  set_long("This is the third example room. Will you ever get to the end? " +
           "Directly above your head is a plaque, nailed to the wall.\n");
  set_light(90);
  add_sign("The plaque is made of bronze.\n",
           "'Don't read me, I'm only an example sign you know!'\n",
           0,
           "plaque");
  add_exit("west", ROOM + "exa2", "door");
  add_exit("east", ROOM + "exa4", "door");
  set_zone("examples");
}
void reset()
{
  object bar;
  if(sizeof(match_objects_for_existence("copper bar", ({ this_object() }) )))
    return;
  bar = clone_object("/std/object");
  bar->set_name("bar");
  bar->add_adjective("copper");
  bar->set_main_plural("copper bars");
  bar->add_plural("bars");
  bar->set_short("copper bar");
  bar->set_long("This is just a treasure thingie to show you how to use " +
                  "such fun things.\n");
  bar->set_weight(80);
  bar->set_value(2000);
  bar->move(this_object());
}