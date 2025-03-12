inherit "/std/room/basic_room";
inherit "/std/room/inherit/bath_house";
void create() {
    basic_room::create();
    bath_house::create();
}
void init() {
    basic_room::init();
    bath_house::init();
}