#include <armoury.h>
#include <money.h>
#include <move_failures.h>
inherit "/std/room/basic_room";
inherit "/std/shops/inherit/item_shop";
void create() {
  do_setup++;
  basic_room::create();
  item_shop::create();
  do_setup--;
  if ( !do_setup ) {
    this_object()->setup();
    this_object()->reset();
  }
}
void init() {
   basic_room::init();
   item_shop::init();
}
void event_theft( object command_ob, object thief, object victim,
  object *stolen ) {
    basic_room::event_theft( command_ob, thief, victim, stolen );
    item_shop::event_theft( command_ob, thief, victim, stolen );
}
void dest_me() {
   item_shop::dest_me();
   basic_room::dest_me();
}