#include <dirs.h>
#include "path.h"
inherit "/std/basic/setup";
class bounding_box {
   int* topleft;
   int* bottomright;
}
class FIXED_INFO {
  string path;
  object ob;
  int *coord;
  mixed bbox;
}
private mapping opposites = ([
  "north": "south", "south": "north", "west": "east",
  "east": "west", "northeast": "southwest", "southwest": "northeast",
  "northwest": "southeast", "southeast": "northwest", "up": "down",
  "down": "up"
]);
private int _dbg_lvl = 0;
private string _debugger;
private object *_area_handlers = ({ });
private object *_iroom_handlers = ({ });
private class FIXED_INFO *_fixed_rooms = ({ });
private mapping _fixed_room_index = ([ ]);
private class bounding_box _topo_box;
void set_debugger(string s) { _debugger = s; }
string query_debugger() { return _debugger; }
void set_debug_level(int l) { _dbg_lvl = l; }
int query_debug_level() { return _dbg_lvl; }
void create() {
  do_setup();
}
class bounding_box query_bounding_box() {
   return _topo_box;
}
int in_bbox(int *coord, class bounding_box bbox) {
  if ((coord[0] < bbox->topleft[0]) || (coord[0] > bbox->bottomright[0])) {
    return 0;
  }
  if ((coord[1] < bbox->topleft[1]) || (coord[1] > bbox->bottomright[1])) {
    return 0;
  }
  return 1;
}
class bounding_box bounding_box(int *coord, mixed s) {
  int *size;
  class bounding_box bbox;
  if (sizeof(coord) != 3) {
    return 0;
  }
  if (arrayp(s)) {
    if (sizeof(s) == 3) {
      size = s;
    } else {
      return 0;
    }
  } else if (intp(s)) {
    size = ({ s, s, s });
  } else {
    return 0;
  }
  bbox = new(class bounding_box);
  bbox->topleft = ({ coord[0]-size[0], coord[1]-size[1], coord[2]-size[2] });
  bbox->bottomright = ({ coord[0]+size[0], coord[1]+size[1], coord[2]+size[2] });
  return bbox;
}
void add_area_handler(mixed h) {
  object oh;
  if (stringp(h)) {
    oh = load_object(h);
    oh->set_handler(base_name(this_object()));
    if (objectp(oh)) {
      _area_handlers += ({ oh });
    } else {
      error(sprintf("Couldn't find area handler %s.\n", h));
    }
  } else if (objectp(h)) {
    h->set_handler(base_name(this_object()));
    _area_handlers += ({ h });
  } else {
    error(sprintf("Couldn't find area handler %O.\n", h));
  }
}
void add_iroom_handler(mixed h) {
  object oh;
  if (stringp(h)) {
    oh = load_object(h);
    oh->set_handler(base_name(this_object()));
    if (objectp(oh)) {
      _iroom_handlers += ({ oh });
    } else {
      error(sprintf("Couldn't find interroom handler %s.\n", h));
    }
  } else if (objectp(h)) {
    h->set_handler(base_name(this_object()));
    _iroom_handlers += ({ h });
  } else {
    error(sprintf("Couldn't find interroom handler %O.\n", h));
  }
}
private void add_internal_fixed_room(string path,
                                     object ob,
                                     int* coord,
                                     class bounding_box bbox) {
  class FIXED_INFO cf;
  cf = new(class FIXED_INFO);
  cf->path = path;
  cf->ob = ob;
  cf->coord = coord;
  cf->bbox = bbox;
  _fixed_room_index[cf->path] = sizeof(_fixed_rooms);
  _fixed_rooms += ({ cf });
}
void add_fixed_room(string f) {
  object of;
  of = load_object(f);
  if (!objectp(of)) {
    error(sprintf("Couldn't load fixed room %s.\n", f));
    return;
  }
  add_internal_fixed_room(f, of, of->query_co_ord(),
                      bounding_box(of->query_co_ord(), of->query_room_size()));
}
void add_fixed_room_object(object of) {
  add_internal_fixed_room(file_name(of), of, of->query_co_ord(),
                    bounding_box(of->query_co_ord(), of->query_room_size()));
}
void add_fixed_room_coordinate(string f, int* coord, int* size) {
    add_internal_fixed_room(f, 0, coord, bounding_box(coord, size));
}
void setup_fixed_room() {
  object shad, r;
  int i;
  r = previous_object();
  shad = clone_object(FIXED_SHADOW);
  if (!objectp(shad)) {
    error(sprintf("Couldn't create shadow for fixed room %O.\n", r));
    return;
  }
  shad->attach(r);
  shad->set_area_handler(file_name(this_object()));
  if (undefinedp(i = _fixed_room_index[file_name(r)])) {
    error(sprintf("Couldn't find entry for fixed room %O.\n", r));
  }
  r->set_co_ord(_fixed_rooms[i]->coord);
}
object find_room_at_coord(int *coord) {
  int i;
  object ob;
  if (_dbg_lvl > 0) {
    tell_creator(_debugger, "%s::find_room_at_coord()\n"
                 "  coord: %O\n",
                 file_name(this_object()), coord);
  }
  for (i = 0; i < sizeof(_fixed_rooms); i++) {
    if (in_bbox(coord, _fixed_rooms[i]->bbox)) {
      if (!objectp(_fixed_rooms[i]->ob)) {
        _fixed_rooms[i]->ob = load_object(_fixed_rooms[i]->path);
      }
      return _fixed_rooms[i]->ob;
    }
  }
  for (i = 0; i < sizeof(_iroom_handlers); i++) {
    if (objectp(ob = _iroom_handlers[i]->find_room_at_coord(coord))) {
      return ob;
    }
  }
  for (i = 0; i < sizeof(_area_handlers); i++) {
    if (objectp(ob = _area_handlers[i]->find_room_at_coord(coord))) {
      return ob;
    }
  }
  return 0;
}
object create_virtual_object(int x, int y, int z) {
   if (undefinedp(x) || undefinedp(y) || undefinedp(z)) {
      return 0;
   }
   return find_room_at_coord(({ x, y, z }));
}
object find_room_at_exit(object r, int *d, string direc) {
  int i, s, dist, max_dist, max_iroom, *coord, *coord_r, *coord_ob;
  string msg;
  object ob, *irooms = ({ });
  mixed size_r;
  class bounding_box bbox_r;
  if (_dbg_lvl > 0) {
    tell_creator(_debugger, "%s::find_room_at_exit()\n"
                 "  r: %O\n"
                 "  d: %O\n"
                 "  direc: %O\n",
                 file_name(this_object()), r, d, direc);
  }
  if (!arrayp(d)) {
    return 0;
  }
  coord = r->query_co_ord();
  size_r = r->query_actual_room_size();
  if (!arrayp(size_r)) {
    size_r = r->query_room_size();
    if (!arrayp(size_r)) {
      size_r = ({ size_r, size_r, size_r });
    }
  }
  coord_r = allocate(3);
  for (i = 0; i < 3; i++) {
    coord_r[i] = coord[i] + 2 * size_r[i] * d[i];
  }
  for (i = 0; i < sizeof(_fixed_rooms); i++) {
    if (in_bbox(coord_r, _fixed_rooms[i]->bbox)) {
      if (!objectp(_fixed_rooms[i]->ob)) {
        _fixed_rooms[i]->ob = load_object(_fixed_rooms[i]->path);
      }
      msg = evaluate(_fixed_rooms[i]->ob->query_topo_barrier(direc));
      if (!undefinedp(msg)) {
        if (!stringp(msg)) {
          msg = "You can't go that way.\n";
        }
        notify_fail(msg);
        return 0;
      }
      return _fixed_rooms[i]->ob;
    }
  }
  bbox_r = bounding_box(coord, size_r);
  for (i = 0; i < sizeof(_iroom_handlers); i++) {
    ob = _iroom_handlers[i]->find_room_at_crossing(coord, coord_r);
    tell_creator("rhinehold", "ob = %O\n", ob);
    if (objectp(ob )
        && (ob != r)) {
      if (_dbg_lvl > 1) {
        tell_creator(_debugger, "%s::find_room_at_exit()\n"
                     "  %O->find_room_at_crossing() returned %O\n",
                     file_name(this_object()), _iroom_handlers[i], ob);
      }
      if (!arrayp(ob->query_co_ord())) {
        return ob;
      }
      if (r->query_fixed_room() && in_bbox(ob->query_co_ord(), bbox_r)) {
        continue;
      }
      irooms += ({ ob });
    }
  }
  if ((s = sizeof(irooms)) > 0) {
    if (s == 1) {
      return irooms[0];
    } else {
      max_dist = 0;
      max_iroom = -1;
      for (i = 0; i < s; i++) {
        coord_ob = irooms[i]->query_co_ord();
        dist = (coord[0] - coord_ob[0])*(coord[0] - coord_ob[0]) +
          (coord[1] - coord_ob[1])*(coord[1] - coord_ob[1]);
        if (dist > max_dist) {
          max_dist = dist;
          max_iroom = i;
        }
      }
      if (max_iroom >= 0) {
        return irooms[max_iroom];
      }
    }
  }
  for (i = 0; i < sizeof(_area_handlers); i++) {
    if (objectp(ob = _area_handlers[i]->find_room_at_exit(r, d))) {
      if (_dbg_lvl > 1) {
        tell_creator(_debugger, "%s::find_room_at_exit()\n"
                     "  %O->find_room_at_exit() returned %O\n",
                     file_name(this_object()), _area_handlers[i], ob);
      }
      return ob;
    }
  }
  return 0;
}
int goto_room_at_coord(int *coord) {
  return this_player()->move_with_look(find_room_at_coord(coord));
}
string query_text_map(int width) {
   int x;
   int y;
   int maxy;
   string map;
   object room;
   map = "";
   for (y = 0; y < maxy; y++) {
      for (x = 0; x < width; x++) {
         room = find_room_at_coord( ({ x, y, 0 }) );
         if (!room) {
            map += " ";
         } else if (!room->query_room_letter()) {
            map += "?";
         } else {
            map += room->query_room_letter();
         }
      }
      map += "\n";
   }
   return map;
}