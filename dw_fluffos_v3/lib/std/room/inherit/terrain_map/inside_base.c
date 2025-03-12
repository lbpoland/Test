#include <room.h>
#include <login_handler.h>
#include <terrain_map.h>
inherit "/std/room/basic_room";
inherit TERRAIN_MAP_ROOM_BASE;
void create() {
   set_not_replaceable(1);
   terrain_room::create();
   basic_room::create();
}
void init() {
   terrain_room::init();
   basic_room::init();
}
varargs mixed* query_dest_other(string exit) {
   mixed* data;
   data = basic_room::query_dest_other(exit);
   return terrain_room::query_dest_other(exit, data);
}
mixed* query_dest_dir(object thing) {
   mixed* data;
   data = basic_room::query_dest_dir(thing);
   return terrain_room::query_dest_dir();
}
mixed stats() {
   return basic_room::stats() + terrain_room::stats();
}