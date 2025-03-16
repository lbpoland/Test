inherit "/std/room/basic_room";
inherit "/std/shops/inherit/craft_shop";
void create() {
   add_help_file("craft_shop");
   basic_room::create();
   craft_shop::create();
}
void init() {
   basic_room::init();
   craft_shop::init();
}
void dest_me() {
   craft_shop::dest_me();
   basic_room::dest_me();
}