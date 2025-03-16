#include <move_failures.h>
#include <player.h>
inherit "/std/room/basic_room";
inherit "/std/room/inherit/room_save";
inherit "/std/basic/auto_load";
void create() {
   do_setup++;
   basic_room::create();
   room_save::create();
   do_setup--;
   if ( !do_setup ) {
     this_object()->setup();
     this_object()->reset();
   }
}
int test_remove(object thing, int flag, mixed dest) {
  int result;
  result = basic_room::test_remove(thing, flag, dest);
  if(result) {
    room_save::test_remove(thing, flag, dest);
  }
  return result;
}
int test_add( object ob, int flag) {
  room_save::test_add(ob, flag);
  return basic_room::test_add(ob, flag);
}
#ifdef DONT_USE
void dest_me() {
  room_save::dest_me();
  basic_room::dest_me();
}
#endif