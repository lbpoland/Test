#include <dirs.h>
#include <image.h>
inherit "/std/room";
mapping direction_bits = ([
    "north": 1,
    "northeast": 2,
    "east": 4,
    "southeast": 8,
    "south": 16,
    "southwest": 32,
    "west": 64,
    "northwest": 128,
    "up": 256,
    "down": 512,
]);
class AREA_INFO {
  string base;
  int *origin;
  int *size;
  mixed *bbox;
  mixed *vertices;
  class IMAGE_INFO height;
  class IMAGE_INFO exits;
}
private int dbg_lvl = 0;
private string debugger = "jeremy";
private string _handler;
private class AREA_INFO *areas = ({ });
private mapping room_cache = ([ ]);
private mapping area_cache = ([ ]);
void set_handler(string handler) {
   _handler = handler;
}
string query_handler() {
   return _handler;
}
void set_debugger(string s) { debugger = s; }
string query_debugger() { return debugger; }
void set_debug_level(int l) { dbg_lvl = l; }
int query_debug_level() { return dbg_lvl; }
mixed query(string s) { return fetch_variable(s); }
void set_base(int i, string s) { areas[i]->base = s; }
string query_base(int i) { return areas[i]->base; }
void set_origin(int i, int *o) { areas[i]->origin = copy(o); }
int *query_origin(int i) { return copy(areas[i]->origin); }
void create() {
  do_setup++;
  ::create();
  do_setup--;
  set_keep_room_loaded(1);
  if ( !do_setup ) {
    this_object()->setup();
    this_object()->reset();
  }
}
int *quantize_to_origin(int *coord_r, int a) {
  int size2, i, *coord_q;
  coord_q = allocate(3);
  for (i = 0; i < 3; i++) {
    size2 = areas[a]->size[i] * 2;
    if (coord_r[i] < areas[a]->origin[i]) {
      coord_q[i] = coord_r[i] - areas[a]->size[i];
    } else {
      coord_q[i] = coord_r[i] + areas[a]->size[i];
    }
    coord_q[i] = ((coord_q[i] - areas[a]->origin[i]) / size2) * size2
      + areas[a]->origin[i];
  }
  return coord_q;
}
void set_size(int i, mixed s) {
  if (intp(s)) {
    areas[i]->size = ({ s, s, s });
  } else if (arrayp(s) && (sizeof(s) == 3)) {
    areas[i]->size = copy(s);
  } else {
    error("Illegal size; must be int or 3-element array.\n");
  }
}
varargs void set_height_map(int i, string map_file, int rle) {
  int *nw;
  areas[i]->height = IMAGE_HANDLER->load_image(map_file, rle);
  if (arrayp(areas[i]->bbox)) {
    nw = copy(areas[i]->bbox[0]);
    nw[0] = areas[i]->bbox[1][0] - 1;
    nw[1] += 1;
    nw[2] += 1;
    areas[i]->height->nw_coord = quantize_to_origin(nw, i);
  }
}
varargs void set_exits_map(int i, string map_file, int rle) {
  int *nw;
  areas[i]->exits = IMAGE_HANDLER->load_image(map_file, rle);
  if (arrayp(areas[i]->bbox)) {
    nw = copy(areas[i]->bbox[0]);
    nw[0] = areas[i]->bbox[1][0] - 1;
    nw[1] += 1;
    nw[2] += 1;
    areas[i]->exits->nw_coord = quantize_to_origin(nw, i);
  }
}
int new_area() {
  areas += ({ new(class AREA_INFO) });
}
void set_vertices(int a, mixed *vs) {
  int v, i;
  if (!arrayp(areas[a]->origin)) {
    error("Origin unset - setting to (0,0,0).\n");
    areas[a]->origin = ({ 0, 0, 0 });
  }
  areas[a]->vertices = copy(vs);
  areas[a]->bbox = ({ copy(vs[0]), copy(vs[0]) });
  for (i = 0; i < 3; i++) {
    areas[a]->bbox[0][i] += areas[a]->origin[i];
    areas[a]->bbox[1][i] += areas[a]->origin[i];
  }
  for (v = 0; v < sizeof(areas[a]->vertices); v++) {
    for (i = 0; i < 3; i++) {
      areas[a]->vertices[v][i] += areas[a]->origin[i];
      if (areas[a]->vertices[v][i] < areas[a]->bbox[0][i]) {
        areas[a]->bbox[0][i] = areas[a]->vertices[v][i];
      } else if (areas[a]->vertices[v][i] > areas[a]->bbox[1][i]) {
        areas[a]->bbox[1][i] = areas[a]->vertices[v][i];
      }
    }
  }
}
int in_bbox(int *coord, mixed *bbox) {
  if ((coord[0] < bbox[0][0]) || (coord[0] > bbox[1][0])) {
    return 0;
  }
  if ((coord[1] < bbox[0][1]) || (coord[1] > bbox[1][1])) {
    return 0;
  }
  if ((coord[2] < bbox[0][2]) || (coord[2] > bbox[1][2])) {
    return 0;
  }
  return 1;
}
int in_area(int a, int *v) {
  int crossings, i, i0, i1, de, int_n, below_vertex;
  mixed *vs;
  if (!in_bbox(v, areas[a]->bbox)) {
    return 0;
  }
  vs = allocate(2);
  for (i = 0; i < sizeof(areas[a]->vertices); i++) {
    below_vertex = 0;
    vs[0] = areas[a]->vertices[i];
    if (i < sizeof(areas[a]->vertices)-1) {
      vs[1] = areas[a]->vertices[i+1];
    } else {
      vs[1] = areas[a]->vertices[0];
    }
    if ((v[1] < vs[0][1]) && (v[1] < vs[1][1])) {
      continue;
    }
    if ((v[1] > vs[0][1]) && (v[1] > vs[1][1])) {
      continue;
    }
    if ((v[0] > vs[0][0]) && (v[0] > vs[1][0])) {
      continue;
    }
    if ((v[0] < vs[0][0]) && (v[0] < vs[1][0])) {
      if (v[1] != vs[0][1]) {
        if (v[1] != vs[1][1]) {
          crossings++;
        }
        continue;
      } else {
        below_vertex = 1;
      }
    }
    if (vs[0][1] == vs[1][1]) {
      if (!below_vertex) {
        return 1;
      }
      continue;
    }
    if ((v[0] == vs[0][0]) && (v[1] == vs[0][1])) {
      return 1;
    }
    if ((vs[0][0] == vs[1][0]) && !below_vertex) {
      return 1;
    }
    if (v[1] == vs[1][1]) {
      continue;
    }
    if (v[1] == vs[0][1]) {
      if (v[0] > vs[0][0]) {
        continue;
      }
      i0 = i;
      while (areas[a]->vertices[i0][1] == v[1]) {
        i0--;
        if (i0 < 0) i0 = sizeof(areas[a]->vertices) - 1;
      }
      i1 = i;
      while (areas[a]->vertices[i1][1] == v[1]) {
        i1++;
        if (i1 >= sizeof(areas[a]->vertices)) i1 = 0;
      }
      crossings++;
      if (((areas[a]->vertices[i0][1] > v[1]) &&
           (areas[a]->vertices[i1][1] > v[1])) ||
          ((areas[a]->vertices[i0][1] < v[1]) &&
           (areas[a]->vertices[i1][1] < v[1]))) {
        crossings++;
      }
      continue;
    }
    de = vs[1][1] - vs[0][1];
    int_n = ceil(to_float(vs[1][0] - vs[0][0])*(v[1] - vs[0][1])/de
                 + vs[0][0] + 0.5);
    if (int_n > v[0]) {
      crossings++;
    }
  }
  return (crossings & 1);
}
object clone_room(int a, int *coord_q, string coord_s) {
  int i, j, e, bit;
  string dir;
  object room;
  room = clone_object(areas[a]->base);
  room_cache[coord_s] = room;
  area_cache[coord_s] = a;
  room->set_room_size(areas[a]->size);
  room->set_co_ord(coord_q);
  if (areas[a]->exits) {
    i = (areas[a]->origin[0] - coord_q[0])/(2*areas[a]->size[0]);
    j = (coord_q[1] - areas[a]->origin[1])/(2*areas[a]->size[1]);
    if ((i < areas[a]->exits->size[0]) && (j < areas[a]->exits->size[1])
        && (i >= 0) && (j >= 0)) {
      e = areas[a]->exits->image[i][j];
      foreach (dir, bit in direction_bits) {
        if (e & bit) {
          room->add_exit(dir, "", "path");
        }
      }
      room->add_property("image_cell", ({ i, j }));
    }
  }
  return room;
}
object find_room_at_coord(int *coord) {
  int a, ac, *coord_q;
  string coord_s;
  object room;
  coord_s = sprintf("%d:%d:%d", coord[0], coord[1], coord[2]);
  if (objectp(room = room_cache[coord_s])) {
    return room;
  }
  if (!undefinedp(ac = area_cache[coord_s])) {
    return clone_room(ac, coord, coord_s);
  }
  for (a = 0; a < sizeof(areas); a++) {
    coord_q = quantize_to_origin(coord, a);
    coord_s = sprintf("%d:%d:%d", coord_q[0], coord_q[1], coord_q[2]);
    if (objectp(room = room_cache[coord_s])) {
      return room;
    }
    if (!undefinedp(ac = area_cache[coord_s])) {
      return clone_room(ac, coord_q, coord_s);
    }
    if (!in_area(a, coord_q)) {
      continue;
    }
    return clone_room(a, coord_q, coord_s);
  }
  return 0;
}
object find_room_at_exit(object r, int *d, string direc) {
  int a, ac, i, *coord, *coord_r, *coord_q;
  string coord_s;
  object room;
  mixed size_r;
  if (dbg_lvl > 0) {
    tell_creator(debugger, "%s::find_room_at_exit()\n"
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
  for (a = 0; a < sizeof(areas); a++) {
    for (i = 0; i < 3; i++) {
      coord_r[i] = coord[i] + (size_r[i] + areas[a]->size[i]) * d[i];
    }
    coord_s = sprintf("%d:%d:%d", coord_r[0], coord_r[1], coord_r[2]);
    return load_object(_handler + ":" + coord_s);
#if 0
    if (objectp(room = room_cache[coord_s])) {
      if (dbg_lvl > 0) {
        tell_creator(debugger, "%s::find_room_at_exit()\n"
                 "  found room %O cached at %s...\n",
                 file_name(this_object()), room, coord_s);
      }
      return room;
    }
    if (!undefinedp(ac = area_cache[coord_s])) {
      if (dbg_lvl > 0) {
        tell_creator(debugger, "%s::find_room_at_exit()\n"
                 "  found area %O cached at %s...\n",
                 file_name(this_object()), ac, coord_s);
      }
      return clone_room(ac, coord_r, coord_s);
    }
    coord_q = quantize_to_origin(coord_r, a);
    coord_s = sprintf("%d:%d:%d", coord_q[0], coord_q[1], coord_q[2]);
    if (objectp(room = room_cache[coord_s])) {
      return room;
    }
    if (!undefinedp(ac = area_cache[coord_s])) {
      return clone_room(ac, coord_q, coord_s);
    }
    if (!in_area(a, coord_q)) {
      continue;
    }
    return clone_room(a, coord_q, coord_s);
#endif
  }
  return 0;
}
int goto_room_at_coord(int *coord) {
  return this_player()->move_with_look(find_room_at_coord(coord));
}
int goto_room_at_exit(int *d, string direc) {
  return this_player()->move_with_look(find_room_at_exit(
                        environment(this_player()), d, direc));
}
void print_images(int a) {
  if (areas[a]->height) {
    printf("-------- Height:\n");
    IMAGE_HANDLER->print_image(areas[a]->height);
  }
  if (areas[a]->exits) {
    printf("-------- Exits:\n");
    IMAGE_HANDLER->print_image(areas[a]->exits);
  }
}
void print_map(int a) {
  int s, e;
  string l = "";
  class IMAGE_INFO exits;
  if (areas[a]->exits) {
    exits = areas[a]->exits;
    for (s = 0; s < exits->size[1]; s++) {
      for (e = 0; e < exits->size[0]; e++) {
        l += (exits->image[s][e] & 128)?"\\":" ";
        l += (exits->image[s][e] & 1)  ?"|":" ";
        l += (exits->image[s][e] & 2)  ?"/":" ";
      }
      l += "\n";
      for (e = 0; e < exits->size[0]; e++) {
        l += (exits->image[s][e] & 64) ?"-":" ";
        l += "*";
        l += (exits->image[s][e] & 4)  ?"-":" ";
      }
      l += "\n";
      for (e = 0; e < exits->size[0]; e++) {
        l += (exits->image[s][e] & 32) ?"/":" ";
        l += (exits->image[s][e] & 16) ?"|":" ";
        l += (exits->image[s][e] & 8)  ?"\\":" ";
      }
      l += "\n";
    }
    write(l);
  }
}