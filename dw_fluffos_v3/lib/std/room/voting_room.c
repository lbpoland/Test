#include <board.h>
#define DEFAULT_VOTE_DURATION 2600*24*7
inherit "/std/room/basic_room";
inherit "/std/room/inherit/voting_room";
void create() {
  voting_room::create();
  do_setup++;
  add_help_file("voting_room");
  basic_room::create();
  do_setup--;
  if ( !do_setup ) {
    this_object()->setup();
    this_object()->reset();
  }
  seteuid("Room");
}
void init() {
   basic_room::init();
   voting_room::init();
}