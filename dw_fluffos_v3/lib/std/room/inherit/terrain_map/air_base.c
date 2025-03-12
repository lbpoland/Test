#include <room.h>
#include <login_handler.h>
#include <terrain_map.h>
inherit "/std/room/outside";
inherit TERRAIN_MAP_ROOM_BASE;
void create() {
   set_not_replaceable(1);
   terrain_room::create();
   outside::create();
}
void init() {
   terrain_room::init();
   outside::init();
}
varargs mixed* query_dest_other(string exit) {
   mixed* data;
   data = outside::query_dest_other(exit);
   return terrain_room::query_dest_other(exit, data);
}
mixed* query_dest_dir(object thing) {
   mixed* data;
   data = outside::query_dest_dir(thing);
   return terrain_room::query_dest_dir(data);
}
mixed stats() {
   return outside::stats() + terrain_room::stats();
}