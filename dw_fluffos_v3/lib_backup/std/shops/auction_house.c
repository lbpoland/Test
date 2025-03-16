inherit "/std/room/basic_room";
inherit "/std/shops/inherit/auction_house";
void create() {
   auction_house::create();
   basic_room::create();
   add_help_file("auction_house");
}
void init() {
   basic_room::init();
   auction_house::init();
}