inherit "/std/room/basic_room";
inherit "/std/shops/inherit/craft_shop_category";
void create() {
   add_help_file("craft_shop");
   add_help_file("craft_shop_category");
   basic_room::create();
   craft_shop_category::create();
}
void init() {
   basic_room::init();
   craft_shop_category::init();
}
void dest_me() {
   craft_shop_category::dest_me();
   basic_room::dest_me();
}