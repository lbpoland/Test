#include "path.h"
inherit "/std/outside";
inherit PATH + "common";
void create() {
  do_setup++;
  ::create();
  do_setup--;
  if ( !do_setup ) {
    this_object()->setup();
    this_object()->reset();
  }
}
void init() {
  ::init();
  this_player()->add_command("speak", this_object(), "<string'language'>" );
}
int do_speak(string str) {
  write("Sorry, you cannot do that here.\n");
  return 1;
}