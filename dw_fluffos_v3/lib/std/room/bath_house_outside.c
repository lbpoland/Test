inherit "/std/room/outside";
inherit "/std/room/inherit/bath_house";
void create() {
    bath_house::create();
    outside::create();
}
void init() {
    outside::init();
    bath_house::init();
}