inherit "/std/outsides/plain";
#include "/std/room/inherit/topography/milestone.c"
void create() {
  do_setup++;
  ::create();
  do_setup--;
  if ( !do_setup ) {
    this_object()->setup();
    this_object()->reset();
  }
  add_exit(motion_verb, "interroom", "hidden");
  call_out("setup_milestone", 0);
}