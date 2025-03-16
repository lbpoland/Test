#include <dirs.h>
#include <room.h>
private string _topo_handler;
private mapping _look_mess = ([ ]);
mapping dirs = ([
  "north": ({ 1, 0, 0 }), "south": ({ -1, 0, 0 }),
  "east": ({ 0, 1, 0 }), "west" : ({ 0, -1, 0 }),
  "northeast": ({ 1, 1, 0 }), "northwest": ({ 1, -1, 0 }),
  "southeast": ({ -1, 1, 0 }), "southwest": ({ -1, -1, 0 }),
  "up": ({ 0, 0, 1 }), "down": ({ 0, 0, -1 })
]);
int* query_co_ord();
mixed* query_dest_other(string direc);
int query_door_open(string direc);
int query_exit(string str);
void add_exit(string dir, string location, string type);
void set_area_handler(string s) { _topo_handler = s; }
void set_topo_handler(string s) { _topo_handler = s; }
string query_topo_handler() { return _topo_handler; }
void add_look_mess(mapping m) { _look_mess += m; }
mapping query_look_mess() { return _look_mess; }
mixed query_quit_handler() {
  string s;
  s = explode(file_name(environment(this_player())), "#")[0];
  return ({ s, query_co_ord() });
}
void enter(object player) {
  object new_room;
  if (sizeof(explode(file_name(this_object()), "#")) > 1) {
    return;
  }
  new_room = (_topo_handler)->find_room_at_coord(
                 player->query_saved_co_ords());
  if (!objectp(new_room)) {
    tell_creator("jeremy", "Couldn't find area room for %O at %O...\n",
                 player, player->query_saved_co_ords());
    player->move(player->query_start_pos());
    return;
  }
  tell_creator("jeremy", "Moving %O to %O...\n",
               player, new_room);
  player->move(new_room);
}
varargs mixed *query_dest_other( string direc, mixed* other_res) {
  object room;
  mixed ret;
  if (!stringp(direc)) {
    return other_res;
  }
  room = (_topo_handler)->find_room_at_exit(this_object(), dirs[direc],
                                           direc);
  if (!objectp(room)) {
    return 0;
  }
  ret = other_res;
  if (!sizeof(ret)) {
    return 0;
  }
  ret[ROOM_DEST] = file_name(room);
  return ret;
}
string query_look(string direc, string other_result) {
  int dark;
  string s;
  string direc_s;
  mixed dest;
  direc_s = direc;
  if (other_result) {
    return s;
  }
  s = _look_mess[direc_s];
  if (s) {
    return evaluate(s);
  }
  dest = query_dest_other(direc_s);
  if (!dest) {
    return 0;
  }
  dest = dest[ROOM_DEST];
  if (!dest) {
    return 0;
  }
  if (query_door_open(direc_s) != 0) {
    dest->force_load();
    this_player()->set_looked( find_object( dest ) );
    dark = (int)this_player()->check_dark((int)dest->query_light());
    s = (string)dest->long( 0, dark );
    if (s[<1] == '\n') {
      return s[0..<2];
    }
    return s;
  }
  return 0;
}
void add_topo_exits(string *other_exits, string other_types) {
  string s;
  foreach (s in other_exits) {
    if ((s == "compass4") || (s == "compass8")) {
      if (!query_exit("north")) {
        add_exit("north", "/topography", other_types);
      }
      if (!query_exit("south")) {
        add_exit("south", "/topography", other_types);
      }
      if (!query_exit("east")) {
        add_exit("east", "/topography", other_types);
      }
      if (!query_exit("west")) {
        add_exit("west", "/topography", other_types);
      }
      if (s == "compass8") {
        if (!query_exit("northeast")) {
          add_exit("northeast", "/topography", other_types);
        }
        if (!query_exit("northwest")) {
          add_exit("northwest", "/topography", other_types);
        }
        if (!query_exit("southeast")) {
          add_exit("southeast", "/topography", other_types);
        }
        if (!query_exit("southwest")) {
          add_exit("southwest", "/topography", other_types);
        }
      }
    } else {
      add_exit(s, "/topography", other_types);
    }
  }
}