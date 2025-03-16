#include "path.h"
#define MAX 100;
inherit PATH + "inside";
string *arr0;
object sign, dummy, trainer;
void setup() {
  set_short("John's Boot Camp");
  add_property("determinate", "");
  set_light( 75 );
  add_property("no teleport", 1);
  set_long("This is a small training room, designed to help the new "
           "adventurer get off to a good start on Discworld.  The air is "
           "stale with the combined stench of sweat, beer, and old "
           "warriors.  Off to one side is a rather unusual training "
           "dummy above which is a small plaque.\n");
  add_item( "face", "As you stare at it, squinting and turning your head "
            "side to side, you realise it looks rather like your old maths "
            "teacher!\n");
  add_item( "floor", "The floor is made of flagstones, cemented together "
            "with centuries of accumulated muck.\n");
  add_item( "wall", "The walls are marked with mysterious stains that may or "
            "may not be blood.  But surely training dummies don't bleed.\n");
  add_item( "ceiling", "The ceiling appears to be dingy patches of plaster "
            "stuck between old oak rafters that have turned black with "
            "age.\n");
  add_property("no godmother", 1);
  add_exit( "combat", PATH + "combat", "door" );
  add_alias( "southeast", "foyer");
}
void reset() {
  if(!sign) {
    sign=add_sign("This is a plaque that seems to describe how to have "
                   "your combat skills assessed.\n", "To assess your "
                   "skills, attack the dummy with the weapon you want to "
                   "test your proficiency in.  Each time you hit the "
                   "dummy, the instructor will comment on your "
                   "performance.  After a number of rounds, the "
                   "instructor will stop you and give you an overall "
                   "performance rating.\n\n"
                   "Don't forget to hold your weapon of choice before "
                   "attacking the training dummy!\n",
                   "small plaque", "plaque", "general");
    sign->add_property("there", "on the wall");
  }
  if(!dummy)
    dummy = clone_object(PATH + "dummy");
  dummy->move(this_object());
  call_out("get_trainer", 1);
}
void dest_me() {
  if(sign)
    sign->dest_me();
  if(dummy)
    dummy->dest_me();
  if(trainer)
    trainer->dest_me();
  ::dest_me();
}
void get_trainer() {
  if(!trainer)
    trainer = clone_object(PATH +"trainer");
  if (trainer) {
    trainer->whichone("john");
    trainer->move( this_object(), "$N hobble$s toward you on his straw-filled stumps." );
    dummy->set_trainer(trainer);
  }
}
void stop_them(object who) {
  if(trainer && dummy)
    trainer->stop_them(who, dummy);
}
string query_quit_handler() {
  return "/d/liaison/NEWBIE/combat";
}