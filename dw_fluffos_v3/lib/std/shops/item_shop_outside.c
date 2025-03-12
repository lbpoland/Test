#include <armoury.h>
#include <money.h>
#include <move_failures.h>
inherit "/std/room/outside";
inherit "/std/shops/inherit/item_shop";
void create() {
   item_shop::create();
   outside::create();
}
void init() {
   outside::init();
   item_shop::init();
}
void event_theft( object command_ob, object thief, object victim,
  object *stolen ) {
    outside::event_theft( command_ob, thief, victim, stolen );
    item_shop::event_theft( command_ob, thief, victim, stolen );
}
void dest_me() {
   item_shop::dest_me();
   outside::dest_me();
}