#include <dirs.h>
#include <terrain.h>
#include <map.h>
#undef DEBUG_ROOM_SIZE
#undef DEBUG_CALC_EXITS
#define TP(x) tell_object(find_player("taffyd"), x);
#define BACKUP_TIME_OUT 1000000
inherit "/std/object";
string terrain_name;
mapping fixed_locations;
mixed *floating_locations;
private nosave int in_map;
private nosave mapping size_cache, cloned_locations, float_cache;
private nosave mapping std_types = ([ "north" : "path", "south" : "path",
  "east" : "path", "west" : "path", "northeast" : "hidden",
  "southwest" : "hidden", "southeast" : "hidden",
  "northwest" : "hidden", "up" : "stair", "down" : "stair" ]);
void setup() {
  size_cache = ([ ]);
  cloned_locations = ([ ]);
  float_cache = ([ ]);
  set_name("map");
  set_short("terrain map");
  add_adjective("terrain");
  set_long("This is a large map showing a large expanse of forest, desert, "
           "mountain or ocean.  A few locations of interest are marked on "
           "it, with most of the gaps between them blank or marked "
           "\"Here bee Draggons\" and the like, suggesting that the map-"
           "maker didn't know what was there either.\n" );
  add_adjective("terrain");
}
string member_cloned_locations(int *co_ords) {
  mapping tmp;
  if ((tmp = cloned_locations[terrain_name]) && (tmp = tmp[co_ords[0]]) &&
      (tmp = tmp[co_ords[1]])) {
      return tmp[co_ords[2]];
  }
  return 0;
}
string member_fixed_locations(int *co_ords) {
  int *loc_co_ords;
  string location;
  foreach (location, loc_co_ords in fixed_locations) {
    if ((co_ords[0] == loc_co_ords[0]) && (co_ords[1] == loc_co_ords[1]) &&
        (co_ords[2] == loc_co_ords[2])) {
      return location;
    }
  }
  return 0;
}
private int between(int limit1, int val, int limit2)
{
  if (limit1 < limit2) {
    return ((limit1 <= val) && (val <= limit2));
  } else {
    return ((limit2 <= val) && (val <= limit1));
  }
}
mixed *member_floating_locations(int *co_ords) {
  int *data;
  mixed *right_locations, *location;
  right_locations = ({ });
  foreach (location in floating_locations) {
    data = location[1];
    if (sizeof(data) == 6) {
      if (between(data[0], co_ords[0], data[3]) &&
          between(data[1], co_ords[1], data[4]) &&
          between(data[2], co_ords[2], data[5])) {
        right_locations += ({ location[0], location[2] });
      }
    } else {
      if ((co_ords[0] == data[0]) && (co_ords[1] == data[1]) &&
          (co_ords[2] == data[2])) {
        right_locations += ({ location[0], location[2] });
      }
    }
  }
  return right_locations;
}
string top_floating_location(int *co_ords) {
  int i, highest_level;
  string highest_location;
  mixed *right_locations;
  right_locations = member_floating_locations(co_ords);
  if (!sizeof(right_locations))
    return 0;
  highest_level = right_locations[1];
  highest_location = right_locations[0];
  for (i = 0; i < sizeof(right_locations); i += 2) {
    if (right_locations[i + 1] > highest_level) {
      highest_level = right_locations[i + 1];
      highest_location = right_locations[i];
    }
  }
  if (highest_location == "nothing")
    return 0;
  return highest_location;
}
private void init_data(string word) {
  terrain_name = word;
  fixed_locations = ([ ]);
  floating_locations = ({ });
}
int get_data_file(string word) {
  if (terrain_name != word) {
    if (file_size(RESTORE_PATH + word + ".o") > 0) {
      unguarded((: restore_object, RESTORE_PATH + word :));
    } else {
      init_data(word);
      return 0;
    }
  }
  return 1;
}
private void save_data_file(string word) {
  int number, last;
  string line, *lines;
  if (file_size(RESTORE_PATH + word +".o") > 0) {
    unguarded((: rename, RESTORE_PATH + word +".o",
               RESTORE_PATH +"backups/"+ word +"."+ time() :));
    lines = unguarded((: get_dir, RESTORE_PATH +"backups/"+ word +".*" :));
    if (sizeof(lines) > 3) {
      last = time() - BACKUP_TIME_OUT;
      foreach(line in lines) {
        sscanf(line, word +".%d", number);
        if (number < last)
          unguarded((: rm, RESTORE_PATH +"backups/"+ line :));
      }
    }
  }
  unguarded((: save_object, RESTORE_PATH + word :));
}
mapping query_cloned_locations(string terrain) {
  return cloned_locations[terrain];
}
mapping query_fixed_locations(string word) {
  get_data_file(word);
  return fixed_locations;
}
mixed *query_floating_locations(string word) {
  get_data_file(word);
  return floating_locations;
}
int *query_co_ord(string terrain, string file) {
  get_data_file(terrain);
  return fixed_locations[file];
}
string query_connection(string terrain, int *co_ords, string direc) {
  mapping connection_info, tmp;
  string connections;
  if (!float_cache[terrain] ||
      !(connection_info = float_cache[terrain][co_ords[0]])) {
    if (file_size(RESTORE_PATH + terrain) != -2) {
      return 0;
    }
    if (file_size(RESTORE_PATH + terrain +"/"+ co_ords[0]) == -1) {
      return 0;
    }
    connections = unguarded((: read_file,
                              RESTORE_PATH + terrain +"/"+ co_ords[0] :));
    connection_info = restore_variable(connections);
    if (!mapp(float_cache[terrain])) {
      float_cache[terrain] = ([ co_ords[0] : connection_info ]);
    } else {
      float_cache[terrain][co_ords[0]] = connection_info;
    }
  }
  if ((tmp = connection_info[co_ords[1]]) && (tmp = tmp[co_ords[2]])) {
    return tmp[direc];
  }
  return 0;
}
int query_connected(string terrain, int *co_ords) {
  mapping connection_info, tmp;
  string connections;
  if (!float_cache[terrain] ||
      !(connection_info = float_cache[terrain][co_ords[0]])) {
    if (file_size(RESTORE_PATH + terrain) != -2) {
      return 0;
    }
    if (file_size(RESTORE_PATH + terrain +"/"+ co_ords[0]) == -1) {
      return 0;
    }
    connections = unguarded((: read_file,
                              RESTORE_PATH + terrain +"/"+ co_ords[0] :));
    connection_info = restore_variable(connections);
    if (!mapp(float_cache[terrain])) {
      float_cache[terrain] = ([ co_ords[0] : connection_info ]);
    } else {
      float_cache[terrain][co_ords[0]] = connection_info;
    }
  }
  if ((tmp = connection_info[co_ords[1]]) && tmp[co_ords[2]]) {
    return 1;
  }
  return 0;
}
int add_fixed_location(string terrain, string file, int *co_ords) {
  get_data_file(terrain);
  if (fixed_locations[file]) {
    return 0;
  }
  if (sizeof(co_ords) != 3) {
    return 0;
  }
  fixed_locations[file] = co_ords;
  save_data_file(terrain_name);
  return 1;
}
private int add_connection(string terrain, int *co_ords, string direc,
                           string file) {
  mapping connection_info, tmp;
  string connections;
  if (!query_connection(terrain, co_ords, direc)) {
    if (file_size(RESTORE_PATH + terrain) != -2) {
      unguarded((: mkdir, RESTORE_PATH + terrain :));
    }
    if (file_size(RESTORE_PATH + terrain +"/"+ co_ords[0]) == -1) {
      connection_info = ([ co_ords[1] : ([ co_ords[2] : ([ direc : file ]) ])
                        ]);
      unguarded((: write_file, RESTORE_PATH + terrain + "/" + co_ords[0],
                   save_variable(connection_info), 1 :));
    } else {
      connections = unguarded((: read_file,
                                 RESTORE_PATH + terrain +"/"+ co_ords[0] :));
      connection_info = restore_variable(connections);
      if ((tmp = connection_info[co_ords[1]])) {
        if ((tmp = tmp[co_ords[2]])) {
          tmp[direc] = file;
        } else {
          connection_info[co_ords[1]][co_ords[2]] = ([ direc : file ]);
        }
      } else {
        connection_info[co_ords[1]] = ([ co_ords[2] : ([ direc : file ]) ]);
      }
      unguarded((: write_file, RESTORE_PATH + terrain + "/" + co_ords[0],
                   save_variable(connection_info), 1 :));
    }
    if (!mapp(float_cache[terrain])) {
      float_cache[terrain] = ([ co_ords[0] : connection_info ]);
    } else {
      float_cache[terrain][co_ords[0]] = connection_info;
    }
  }
}
int add_floating_location(string terrain, string file, int *co_ords,
                          int level) {
  get_data_file(terrain);
  if ((sizeof(co_ords) != 6) && (sizeof(co_ords) != 3)) {
    return 0;
  }
  if (member_array(({ file, co_ords, level }), floating_locations) != -1) {
    return 0;
  }
  floating_locations += ({ ({ file, co_ords, level }) });
  save_data_file(terrain_name);
  return 1;
}
private void add_cloned_location(string terrain, string file, int *co_ords) {
  mapping tmp, location_m;
  if (!(location_m = cloned_locations[terrain])) {
    cloned_locations[terrain] = ([ file : co_ords,
                                   co_ords[0] : ([ co_ords[1] :
                                                   ([ co_ords[2] : file ]) ])
                                ]);
  } else {
    location_m[file] = co_ords;
    if ((tmp = location_m[co_ords[0]])) {
      if ((tmp = tmp[co_ords[1]])) {
        tmp[co_ords[2]] = file;
      } else {
        location_m[co_ords[0]][co_ords[1]] = ([ co_ords[2] : file ]);
      }
    } else {
      location_m[co_ords[0]] = ([ co_ords[1] : ([ co_ords[2] : file ]) ]);
    }
  }
}
int modify_fixed_location(string terrain, string file, int *co_ords) {
  get_data_file(terrain);
  if (!fixed_locations[file]) {
    return 0;
  }
  if (sizeof(co_ords) != 3) {
    return 0;
  }
  fixed_locations[file] = co_ords;
  save_data_file(terrain_name);
  return 1;
}
int delete_cloned_location(string terrain, string file) {
  int *co_ords;
  mapping tmp, location_m;
  if (!((location_m = cloned_locations[terrain]) &&
        (co_ords = location_m[file]))) {
    return 0;
  }
  map_delete(location_m, file);
  tmp = location_m[co_ords[0]][co_ords[1]];
  map_delete(tmp, co_ords[2]);
  if (!sizeof(tmp)) {
    tmp = location_m[co_ords[0]];
    map_delete(tmp, co_ords[1]);
    if (!sizeof(tmp)) {
      map_delete(location_m, co_ords[0]);
      if (!sizeof(location_m)) {
        map_delete(cloned_locations, terrain);
      }
    }
  }
  return 1;
}
int delete_fixed_location(string terrain, string file) {
  get_data_file(terrain);
  if (!fixed_locations[file]) {
    return 0;
  }
  map_delete(fixed_locations, file);
  save_data_file(terrain_name);
  return 1;
}
int delete_floating_location(string terrain, string file, int *co_ords) {
  int i, j, flag_d, flag_m, *data;
  get_data_file(terrain);
  for (i = 0; i < sizeof(floating_locations); i++) {
    if (floating_locations[i][0] == file) {
      data = floating_locations[i][1];
      if (sizeof(data) != sizeof(co_ords)) {
        continue;
      }
      flag_m = 0;
      for (j = 0; j < sizeof(data); j++) {
        if (data[j] != co_ords[j]) {
          flag_m = 1;
          break;
        }
        if (!flag_m) {
          floating_locations = delete(floating_locations, i, 1);
          flag_d = 1;
        }
      }
    }
  }
  save_data_file(terrain_name);
  return flag_d;
}
void clear_cloned_locations(string terrain) {
  map_delete(cloned_locations, terrain);
}
void clear_connections(string terrain) {
  string line, *lines;
  if (file_size(RESTORE_PATH + terrain) != -2) {
    return;
  }
  lines = unguarded((: get_dir, RESTORE_PATH + terrain +"
private int right_co_ords(int *new_co_ords, int *co_ords, int delta,
                          int *vector) {
  int i;
  for (i = 0; i < 3; i++) {
    if (new_co_ords[i] + delta * vector[i] != co_ords[i]) {
      return 0;
    }
  }
  return 1;
}
int get_room_size(string file, int level) {
  int i, number, roomsize, *mapsize;
  string bname, parent, *lines;
  bname = base_name(file);
  if (size_cache[bname]) {
#ifdef DEBUG_ROOM_SIZE
    TP(sprintf("GRS says (cached) %s is %d\n", file, size_cache[bname]));
#endif
    return size_cache[bname];
  }
  if (find_object(file)) {
    size_cache += ([ bname : file->query_room_size() ]);
#ifdef DEBUG_ROOM_SIZE
    TP(sprintf("GRS says (loaded) %s is %d\n", file, size_cache[bname]));
#endif
    return size_cache[bname];
  }
  if (!in_map) {
    in_map = 1;
    mapsize = MAP_HANDLER->query_room_size(bname);
    in_map = 0;
  } else {
#ifdef DEBUG_ROOM_SIZE
    TP("GRS says recursion!\n");
#endif
    mapsize = 0;
  }
  if (mapsize) {
    size_cache += ([ bname : mapsize[0] ]);
#ifdef DEBUG_ROOM_SIZE
    TP(sprintf("GRS says (map) %s is %d\n", file, size_cache[bname]));
#endif
    return mapsize[0];
  }
  file = bname + ".c";
  if (file_size(file) < 0) {
    return 10;
  }
  lines = explode(read_file(file), "\n");
  roomsize = 10;
  for (i = 0; i < sizeof(lines); i++) {
    if (level < 4 &&
        sscanf(lines[i], "%*sinherit%*s\"%s\"%*s;", parent) == 4) {
      if (parent[<2..] != ".c") {
        parent += ".c";
      }
      roomsize = get_room_size(parent, level + 1);
    } else if (sscanf(lines[i], "%*sset_room_size(%*s%d%*s", number) == 4) {
      roomsize = number;
      break;
    }
  }
  size_cache += ([ bname : roomsize ]);
#ifdef DEBUG_ROOM_SIZE
  TP(sprintf("GRS says (parsed) %s is %d\n", file, size_cache[bname]));
#endif
  return roomsize;
}
private void add_exit(object place, string direc, string dest) {
  string type;
  type = (string)place->query_exit_type(direc, dest);
  if (!type) {
    type = std_types[direc];
  } else {
    if (type == "none") {
      return;
    }
  }
  place->add_exit(direc, dest, type);
}
private void calculate_exits(object place, int *co_ords) {
  int i, j, k, connected, delta, *new_co_ords;
  string actual, *exit_dirs;
  connected = query_connected(terrain_name, co_ords);
  exit_dirs = (string *)place->query_direc();
  for (i = 0; i < 20; i += 2) {
    if (member_array(STD_ORDERS[i], exit_dirs) != -1) {
      continue;
    }
    actual = query_connection(terrain_name, co_ords, STD_ORDERS[i]);
    if (actual) {
#ifdef DEBUG_CALC_EXITS
      TP(sprintf("actual room %s found\n", actual));
#endif
      add_exit(place, STD_ORDERS[i], actual);
      continue;
    }
    if (connected) {
#ifdef DEBUG_CALC_EXITS
      TP("connected, but no actual room\n");
#endif
      continue;
    }
    new_co_ords = copy(co_ords);
    for (k = 0; k < 3; k++) {
      new_co_ords[k] -= place->query_room_size() * STD_ORDERS[i+1][k];
    }
    reset_eval_cost();
    for (j = 0; j < 100; j++) {
      for (k = 0; k < 3; k++) {
        new_co_ords[k] -= 5 * STD_ORDERS[i+1][k];
      }
      if ((actual = member_fixed_locations(new_co_ords)) ||
          (actual = member_cloned_locations(new_co_ords)) ||
          (actual = top_floating_location(new_co_ords))) {
        delta = (int)place->query_room_size() + get_room_size(actual, 0);
        if (!right_co_ords(new_co_ords, co_ords, delta, STD_ORDERS[i+1])) {
          continue;
        }
#ifdef DEBUG_CALC_EXITS
        TP(sprintf("adding connection for %s\n", actual));
#endif
        add_connection(terrain_name, co_ords, STD_ORDERS[i],
                       base_name(actual));
        add_exit(place, STD_ORDERS[i], actual);
        break;
      }
    }
  }
}
object find_location(string terrain, int *co_ords) {
  string dest_name;
  object destination;
  if (!(get_data_file(terrain)) || (sizeof(co_ords) != 3)) {
    return 0;
  }
  reset_eval_cost();
  if ((dest_name = member_fixed_locations(co_ords))) {
    if (!(destination = find_object(dest_name))) {
      destination = load_object(dest_name);
    }
    return destination;
  }
  if (dest_name = member_cloned_locations(co_ords)) {
    if ((destination = find_object(dest_name))) {
      return destination;
    } else {
      delete_cloned_location(terrain, dest_name);
    }
  }
  if (dest_name = top_floating_location(co_ords)) {
    destination = clone_object(dest_name);
    destination->set_co_ord(co_ords);
    destination->set_terrain(terrain_name);
    calculate_exits(destination, co_ords);
    add_cloned_location(terrain, file_name(destination), co_ords);
    return destination;
  }
  return 0;
}
void setup_location(object place, string terrain) {
  int *co_ords;
  get_data_file(terrain);
  if (!fixed_locations[base_name(place)]) {
    return;
  }
  co_ords = fixed_locations[base_name(place)];
  place->set_co_ord(co_ords);
  calculate_exits(place, co_ords);
}
mixed *stats() {
  return ::stats() + ({
    ({ "roomsize cache size", sizeof(size_cache) }),
      ({ "cloned_locations", sizeof(cloned_locations) }),
        ({ "float_cache", sizeof(float_cache) }),
          ({ "terrain name", terrain_name }),
            ({ "fixed locations", sizeof(fixed_locations) }),
              ({ "floating locations", sizeof(floating_locations) }),
  });
}