#include <config.h>
#ifdef __DISTRIBUTION_LIB__
inherit "/std/room";
#else
inherit "/std/room/player_housing";
#endif
inherit "/std/shops/inherit/player_craft_shop";
void create() {
#ifdef __DISTRIBUTION_LIB__
   room::create();
#else
   player_housing::create();
#endif
   player_craft_shop::create();
   add_help_file("craft_shop");
   add_help_file("craft_shop_category");
   add_help_file("player_craft_shop");
}
void init() {
#ifdef __DISTRIBUTION_LIB__
   room::init();
#else
   player_housing::init();
#endif
   player_craft_shop::init();
}
void dest_me() {
#ifdef __DISTRIBUTION_LIB__
   room::dest_me();
#else
   player_craft_shop::dest_me();
#endif
   player_housing::dest_me();
}
void set_save_dir(string dir) {
   set_save_file(dir + "_main");
#ifndef __DISTRIBUTION_LIB__
   ::set_save_dir(dir);
#endif
}
int is_allowed(string name) {
   if (name == "pinkfish") {
      return 1;
   }
   if (lower_case(name) == lower_case(query_owner())) {
      return 1;
   }
   if (member_array(lower_case(name), query_allowed()) != -1) {
      return 1;
   }
   return 0;
}
void event_exit(object ob, string mess, object to) {
#ifdef __DISTRIBUTION_LIB__
   room::event_exit(ob, mess, to);
#else
   player_housing::event_exit(ob, mess, to);
#endif
   player_craft_shop::event_exit(ob, mess, to);
}
#ifndef __DISTRIBUTION_LIB__
int ownership_change(string old_owner, string new_owner) {
   player_craft_shop::ownership_change(old_owner, new_owner);
   return player_housing::ownership_change(old_owner, new_owner);
}
#endif