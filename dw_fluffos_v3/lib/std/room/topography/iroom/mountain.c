inherit "/std/outsides/mountain";
#include "/std/room/inherit/topography/iroom.c"
void create() {
  do_setup++;
  ::create();
  do_setup--;
  if ( !do_setup ) {
    this_object()->setup();
    this_object()->reset();
  }
  add_exit(motion_verb, "interroom", "hidden");
}