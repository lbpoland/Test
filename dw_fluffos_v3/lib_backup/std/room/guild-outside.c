inherit "/std/room/outside";
inherit "/std/room/inherit/guild";
void create() {
  guild::create();
  outside::create();
}
void init() {
  outside::init();
  guild::init();
}