inherit "/std/room/basic_room";
inherit "/std/room/inherit/guild";
void create() {
  guild::create();
  basic_room::create();
}
void init() {
  basic_room::init();
  guild::init();
}