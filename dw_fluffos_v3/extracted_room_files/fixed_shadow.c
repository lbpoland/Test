# File: /lib/std/room/basic/topography/fixed_shadow.c

#include <dirs.h>
#include <room.h>
string topo_handler;
object fixed_room;
mapping topo_barriers = ([ ]);
mapping dirs = ([
  "north": ({ 1, 0, 0 }), "south": ({ -1, 0, 0 }),
  "east": ({ 0, 1, 0 }), "west" : ({ 0, -1, 0 }),
  "northeast": ({ 1, 1, 0 }), "northwest": ({ 1, -1, 0 }),
  "southeast": ({ -1, 1, 0 }), "southwest": ({ -1, -1, 0 }),
  "up": ({ 0, 0, 1 }), "down": ({ 0, 0, -1 })
]);
void set_area_handler(string s) { topo_handler = s; }
void set_topo_handler(string s) { topo_handler = s; }
string query_area_handler() { return topo_handler; }
string query_topo_handler() { return topo_handler; }
void add_topo_barriers(mapping m) { topo_barriers += m; }
mapping query_topo_barriers() { return topo_barriers; }
mixed query_topo_barrier(string direc) { return topo_barriers[direc]; }
int query_fixed_room() { return 1; }
varargs mixed *query_dest_other( string direc ) {
  object room;
  mixed ret;
  if (!stringp(direc)) {
    return fixed_room->query_dest_other(direc);
  }
  ret = fixed_room->query_dest_other(direc);
  if (!sizeof(ret)) {
    return 0;
  }
  if (!stringp(ret[ROOM_DEST]) || (ret[ROOM_DEST] == "/") ||
  (ret[ROOM_DEST] == "/terrain") || (ret[ROOM_DEST] == "/topography")) {
    room = (topo_handler)->find_room_at_exit(this_object(),
                           dirs[direc], direc);
    if (!objectp(room)) {
      return 0;
    }
    ret[ROOM_DEST] = file_name(room);
  }
  return ret;
}
void attach(object ob) {
  shadow(ob);
  fixed_room = ob;
}
void add_topo_exits(string *other_exits, string other_types) {
  string s;
  foreach (s in other_exits) {
    if ((s == "compass4") || (s == "compass8")) {
      if (!this_object()->query_exit("north"))
        this_object()->add_exit("north", "/topography", other_types);
      if (!this_object()->query_exit("south"))
        this_object()->add_exit("south", "/topography", other_types);
      if (!this_object()->query_exit("east"))
        this_object()->add_exit("east", "/topography", other_types);
      if (!this_object()->query_exit("west"))
        this_object()->add_exit("west", "/topography", other_types);
      if (s == "compass8") {
        if (!this_object()->query_exit("northeast"))
          this_object()->add_exit("northeast", "/topography", other_types);
        if (!this_object()->query_exit("northwest"))
          this_object()->add_exit("northwest", "/topography", other_types);
        if (!this_object()->query_exit("southeast"))
          this_object()->add_exit("southeast", "/topography", other_types);
        if (!this_object()->query_exit("southwest"))
          this_object()->add_exit("southwest", "/topography", other_types);
      }
    } else {
      this_object()->add_exit(s, "/topography", other_types);
    }
  }
}