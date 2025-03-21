#include <weather.h>
#include <terrain_map.h>
#include <player.h>
#define   AREA_OBSTACLE    0
#define   AREA_ROOM        1
#define   AREA_ROAD        2
#define   AREA_WORLD       3
#define   RANDOM_HANDLER   "/obj/handlers/random_num"
inherit "/std/room/inherit/terrain_map/distance_str";
#define X_DIFF 1
#define Y_DIFF 0
#define XY_DIFF 2
class char_map_data {
   string char;
   string colour;
   string path;
   string room_desc;
   mixed items;
   mixed item_desc;
   mixed chats;
   int type;
   int height;
   mapping height_rooms;
   int whole_sentance;
   string adjacent_desc;
   int room_jump;
   int room_jump_matching;
}
class feature_data {
   int range;
   string* descs;
   string* night_descs;
   mixed f_items;
   mixed f_item_desc;
   mixed f_item_night_desc;
   int whole_sentance;
   mixed chats;
   mixed night_chats;
   object feature_ob;
}
class sign_data {
   string long;
   string read_mess;
   string short;
   string name;
   string language;
}
class real_coords {
   int x1;
   int y1;
   int x2;
   int y2;
   int xdiff;
   int ydiff;
   int xydiff;
   int zdiff;
   int in_world_map;
}
private mixed     *_room_map = 0;
private mixed     *_area_map = 0;
private mixed     *_zone_map = 0;
private int       _visible_distance;
private int       _width = 0;
private int       _height = 0;
private int       _normal_skip_size = 1;
private int       _random_desc_limit = 2;
private int       _random_chat_limit = 4;
private int       _newline_mode = 1;
private mapping   _room_zones = ([ ]);
private mapping   _feature_rooms = ([ ]);
private mapping   _char_map = ([ ]);
private mapping   _zone_types = ([ ]);
private mapping   _features = ([ ]);
private mapping   _signposts = ([ ]);
private mapping   _standard_exits = ([ ]);
private mapping   _adjacent_terrains = ([ ]);
private mapping   _random_descs = ([ ]);
private mapping   _random_chats = ([ ]);
private class real_coords _real_coords;
private mapping _key = ([ ]);
private mapping   _direcs = ([ "north":     ({ 0, 1, "south", Y_DIFF, 0 }),
                       "northeast": ({ 1, 1, "southwest", XY_DIFF, ({ "obvious", 0 }) }),
                       "east":      ({ 1, 0, "west", X_DIFF, 0 }),
                       "southeast": ({ 1, -1, "northwest", XY_DIFF, ({ "obvious", 0 }) }),
                       "south":     ({ 0, -1, "north", Y_DIFF, 0 }),
                       "southwest": ({ -1, -1, "northeast", XY_DIFF, ({ "obvious", 0 }) }),
                       "west":      ({ -1, 0, "east", X_DIFF, 0 }),
                       "northwest": ({ -1, 1, "southeast", XY_DIFF, ({ "obvious", 0 }) }) ]);
private string* _direc_order = ({
                        "north", "east", "south", "west",
                        "northeast", "southeast", "southwest", "northwest" });
private mixed    *_feature_direcs = ({ ({ "southwest", "south", "southeast" }),
                               ({ "west", "Oops", "east" }),
                               ({ "northwest", "north", "northeast" }) });
void load_area_map();
void load_zone_map();
class char_map_data query_char_map(int x, int y);
void setup_area_map();
void setup_room(object room, string base_path);
string find_adjacent_terrain(int x, int y);
mixed   *query_room_map() { return _room_map; }
mixed   *query_area_map() { return _area_map; }
mixed   *query_zone_map() { return _zone_map; }
mapping query_zone_types() { return _zone_types; }
mapping query_feature_rooms() { return _feature_rooms; }
mapping query_features() { return _features; }
mapping query_room_zones() { return _room_zones; }
mapping query_char_maps() { return _char_map; }
mapping query_signposts() { return _signposts; }
mapping query_random_descs() { return _random_descs; }
mapping query_random_chats() { return _random_chats; }
mapping query_standard_exits() { return _standard_exits; }
mapping query_adjacent_terrains() { return _adjacent_terrains; }
class real_coords query_debug_real_coord() { return _real_coords; }
mixed* query_real_coords() { return ({ ({ _real_coords->x1, _real_coords->y1 }), ({ _real_coords->x2, _real_coords->y2 }) }); }
int     *query_dimensions() { return ({ _width, _height }); }
void    setup_handler() { }
string  query_map_file() { return ""; }
void set_real_coordinates_no_inform(int x1, int y1, int x2, int y2) {
   int tmp;
   if (x1 > x2) {
      tmp = x1;
      x1 = x2;
      x2 = tmp;
   }
   if (y1 > y2) {
      tmp = y1;
      y1 = y2;
      y2 = tmp;
   }
   _real_coords = new(class real_coords, x1:x1, y1:y1, x2:x2, y2:y2);
   _real_coords->xdiff = (x2 - x1) / _width;
   _real_coords->ydiff = (y2 - y1) / _height;
   _real_coords->zdiff = 15;
   _real_coords->xydiff = to_int(sqrt(to_float(_real_coords->xdiff) * to_float(_real_coords->xdiff)+
                               to_float(_real_coords->ydiff) * to_float(_real_coords->ydiff)));
}
void set_real_coordinates(int x1, int y1, int x2, int y2) {
   set_real_coordinates_no_inform(x1, y1, x2, y2);
   _real_coords->in_world_map = TERRAIN_MAP_WORLD_MAP->add_terrain(base_name(this_object()),
                                      _real_coords->x1, _real_coords->y1,
                                      _real_coords->x2, _real_coords->y2);
}
void set_real_offsets(int xoff, int yoff, int zoff) {
   _real_coords = new(class real_coords);
   _real_coords->xdiff = xoff;
   _real_coords->ydiff = yoff;
   _real_coords->xydiff = to_int(sqrt(to_float(_real_coords->xdiff) * to_float(_real_coords->xdiff)+
                               to_float(_real_coords->ydiff) * to_float(_real_coords->ydiff)));
}
class coord query_terrain_from_real_coord(int x, int y, int z) {
   return new(class coord,
       x: (x - _real_coords->x1)  / _real_coords->xdiff,
       y: (y - _real_coords->y1) / _real_coords->ydiff,
       z: z / _real_coords->zdiff
        );
}
class coord query_real_from_terrain_coord(int x, int y, int z) {
   if (!_real_coords) {
      return new(class coord, x : 0, y : 0);
   }
   return new(class coord,
      x: _real_coords->x1 + x * _real_coords->xdiff,
      y: _real_coords->y1 + y * _real_coords->ydiff,
      z: z * _real_coords->zdiff
     );
}
int query_newline_mode() { return _newline_mode; }
void set_newline_mode(int mode)
{
  _newline_mode = mode;
}
void set_visible_distance(int distance) {
   _visible_distance = distance;
}
int query_visible_distance() {
   return _visible_distance;
}
void create()
{
   setup_area_map();
   setup_handler();
}
void setup_area_map()
{
   int   index;
   load_area_map();
   load_zone_map();
   if (!arrayp(_room_map)) {
      _room_map = ({ });
      for (index = 0; index < _width; index++)
         _room_map += ({ allocate(_width) });
   }
}
object query_feature_ob(string name) {
   return _features[name]->feature_ob;
}
mapping calc_features(object room)
{
   class feature_data    feature;
   string     title;
   int        *room_coords = room->query_terrain_coords();
   int        x = room_coords[0];
   int        y = room_coords[1];
   int        z = room_coords[2];
   mapping    data;
   string direc;
   int range;
   mapping block_feature;
   mixed* features;
   mixed* tmp;
   block_feature = ([ ]);
   features = ({ });
   foreach(title, feature in _features) {
      if (!room->can_view_feature(title)) {
         continue;
      }
      if (!feature || !feature->feature_ob) {
         debug_printf("Unable to find feature object for %O\n", title);
         continue;
      }
      data = feature->feature_ob->query_feature_desc_from(x, y, z);
      if (!data || !sizeof(data)) {
         continue;
      }
      if (feature->feature_ob->query_blocking()) {
         foreach (direc, range in data) {
            if (!block_feature[direc]) {
               if (block_feature[direc] > range) {
                  block_feature[direc] = range;
               } else {
                  map_delete(data, direc);
               }
            }
         }
      }
      if (sizeof(data)) {
         features += ({ ({ title, feature, data }) });
      }
   }
   foreach (tmp in features) {
      data = tmp[2];
      if (sizeof(block_feature)) {
         foreach (direc, range in data) {
            if (block_feature[direc] && block_feature[direc] < range) {
               map_delete(data, direc);
            }
         }
      }
      if (sizeof(data)) {
         feature = tmp[1];
         title = tmp[0];
         room->add_feature(title, data, feature->f_items, feature->whole_sentance);
         if (!_feature_rooms[title]) {
            _feature_rooms[title] = ({ });
         } else {
            _feature_rooms[title] = filter(_feature_rooms[title], (: $1 && objectp($1) :));
         }
         _feature_rooms[title] |= ({ room });
      }
   }
}
void add_signposts(object room)
{
   class sign_data sign;
   int     *coords = room->query_terrain_coords();
   int     x = coords[0];
   int     y = coords[1];
   string  title = sprintf("%d:%d", x, y);
   object  sign_ob;
   sign = _signposts[title];
   if (!sign) {
      return;
   }
   sign_ob = room->add_sign(sign->long, sign->read_mess,
                  sign->short, sign->name,
                  sign->language);
   sign_ob->move(room);
}
void setup_zones(object room)
{
   string  *zones;
   int     *coords = room->query_terrain_coords();
   int     x = coords[0];
   int     y = coords[1];
   string  type;
   string  zone;
   if (!sizeof(_zone_map)) {
      return;
   }
   type = _zone_map[y][x..x];
   zones = _zone_types[type];
   if (!zones) {
      return;
   }
   foreach (zone in zones) {
      room->add_zone(zone);
   }
}
void calc_random_descs(object room, string key)
{
   int      limit = _random_desc_limit;
   int      *indices = ({ });
   int      *coords = room->query_terrain_coords();
   int      seed = (coords[0] * 2) + coords[1];
   mapping  desc;
   mixed    *descs = _random_descs[key];
   int      index;
   if (limit > sizeof(descs)) {
      limit = sizeof(descs);
   }
   if (!limit) {
      return;
   }
   while (sizeof(indices) < limit) {
      index = RANDOM_HANDLER->random(sizeof(descs), seed++);
      if (member_array(index, indices) >= 0) {
         continue;
      }
      indices += ({ index });
   }
   for (index = 0; index < limit; index++) {
      desc = descs[indices[index]];
      room->add_random_desc(desc["desc"]);
      room->add_item(desc["items"], desc["item_desc"]);
   }
}
void calc_random_chats(object room, string key)
{
}
string query_dest_coordinate_string(int x, int y, int z, string direc, string key) {
   class char_map_data  room_setup;
   room_setup = query_char_map(x, y);
   if (room_setup->type == AREA_WORLD) {
      return room_setup->path->query_dest_coordinate_string(x, y, z, direc, key);
   }
   return 0;
}
int* query_ground_room_co_ords(int x, int y) {
   class char_map_data  room_setup;
   room_setup = query_char_map(x, y);
   return ({ x, y, room_setup->height });
}
string query_ground_room(int x, int y) {
   int* co_ords;
   co_ords = query_ground_room_co_ords(x, y);
   return base_name(this_object()) + ":" + co_ords[0] + ":" + co_ords[1] + ":" + co_ords[2];
}
string query_climb_base_room(int x, int y, int z, int map_room, string ref base) {
   class char_map_data  room_setup;
   string *tmp;
   room_setup = query_char_map(x, y);
   if (!room_setup) {
      return 0;
   }
   if (room_setup->type == AREA_WORLD) {
     if(file_size(room_setup->path + ".c") == -1) {
       tmp = explode(room_setup->path, "_edge");
       if(sizeof(tmp) && file_size(tmp[0] + ".c") > 0)
         room_setup->path = tmp[0];
     }
     return room_setup->path->find_base_terrain_room(x, y, z, room_setup->path, map_room, ref base);
   } else if (room_setup->height_rooms) {
      if (z > room_setup->height) {
         if (map_room == TERRAIN_MAP_ROOM_MAP) {
            return room_setup->path;
         }
         if (map_room != TERRAIN_MAP_ROOM_CLIMB) {
            return TERRAIN_MAP_DEFAULT_AIR_ROOM;
         }
         return 0;
      }
      if (z == room_setup->height) {
         return room_setup->path;
      }
      if (room_setup->height_rooms[z]) {
         return room_setup->height_rooms[z];
      }
      if (room_setup->height_rooms["minimum"] > z) {
         return 0;
      }
      return room_setup->height_rooms["default"];
   } else if (z == room_setup->height) {
      return room_setup->path;
   } else if (map_room && z > room_setup->height) {
      return room_setup->path;
   } else if (z > room_setup->height) {
      if (map_room != TERRAIN_MAP_ROOM_CLIMB) {
         return TERRAIN_MAP_DEFAULT_AIR_ROOM;
      }
   }
   return 0;
}
string query_base_room(int x, int y, int z, int map_room) {
   string dest;
   dest = "bing";
   return query_climb_base_room(x, y, z, map_room, ref dest);
}
void setup_room(object room, string base_path)
{
   string main_base;
   string base;
   int      *room_coords = room->query_terrain_coords();
   mixed    *coords;
   int      x;
   int      y;
   string   direc;
   class char_map_data  room_setup;
   string*  dirs;
   mapping  adjacent_descs = ([ ]);
   mapping  adjacent_sent = ([ ]);
   mapping  distant;
   string   adjacent;
   string   key;
   string   room_long = "";
   string   key_here;
   mixed    *exit_mods;
   object   new_room;
   string   outside_types = "";
   mixed    *exits;
   mapping  exit;
   string   *sentances;
   mixed   tmp;
   int z;
   int road_jump;
   class coord fluff;
   string* miss_road;
   mapping ignore_exits;
   string  walk_pre;
   string  walk_full;
   string  journey_pre;
   string  new_base_path;
   if (!arrayp(room_coords)) {
      debug_printf("Unable to find room coordinates from %O\n", file_name(room));
      return ;
   }
   room_setup = query_char_map(room_coords[0], room_coords[1]);
   key_here = room_setup->char;
   if (room_setup->room_desc) {
      adjacent_descs[room_setup->room_desc] = ({ "here" });
      adjacent_sent[room_setup->char] = 1;
      if( room_setup->items ) {
          if( stringp( room_setup->items ) &&
              stringp( room_setup->item_desc ) ) {
              room->add_item( room_setup->items, room_setup->item_desc );
          } else if( arrayp( room_setup->items ) &&
              arrayp( room_setup->item_desc ) && sizeof( room_setup->items ) ) {
              if( sizeof( room_setup->items ) !=
                  sizeof( room_setup->item_desc ) ) {
                  debug_printf( "Error, unequal arrays.  Item not set." );
              } else {
                  int i;
                  for( i = 0; i < sizeof( room_setup->items ); i++ ) {
                      room->add_item( room_setup->items[i],
                          room_setup->item_desc[i] );
                  }
              }
          }
      }
   }
   if (room_setup->room_jump_matching) {
      road_jump = room_setup->room_jump;
   }
   walk_pre = room->query_terrain_map_walk_exit();
   journey_pre = room->query_terrain_map_journey_exit();
   exits = _standard_exits[sprintf("%d:%d:%d", room_coords[0], room_coords[1], room_coords[2])];
   ignore_exits = ([ ]);
   if (exits) {
      foreach(exit in exits) {
         room->add_exit(exit["direc"], exit["dest"], exit["type"]);
         if (exit["modifiers"]) {
            room->modify_exit(exit["direc"], exit["modifiers"]);
         }
         ignore_exits[exit["direc"]] = 1;
      }
   }
   main_base = base_name(this_object());
   if (room_setup->height_rooms ||
       room_setup->type == AREA_WORLD) {
      int i;
      x = room_coords[0];
      y = room_coords[1];
      for (i = 0; i < 2; i++) {
         z = room_coords[2];
         if (!i) {
            direc = "up";
            tmp = "down";
            z++;
         } else {
            direc = "down";
            tmp = "up";
            z--;
         }
         base = query_base_room(x, y, z, TERRAIN_MAP_ROOM_EXACT);
         if (base) {
            new_room = load_object(base);
            new_base_path = base;
            if (!new_room) {
               continue;
            }
            if (new_room->can_enter_from(key_here, direc, base_path) &&
                room->can_exit_to(key_here, direc, new_base_path)) {
               room->add_exit(direc, main_base + ":" + x + ":" + y + ":" + z, "path");
               exit_mods = room->get_to_same(tmp, direc, key, new_base_path);
               if (exit_mods) {
                   room->modify_exit(direc, exit_mods);
               }
            }
         }
      }
   }
   miss_road = allocate(3 * 3);
   foreach(direc in _direc_order) {
      coords = _direcs[direc];
      x = coords[0] + room_coords[0];
      y = coords[1] + room_coords[1];
      z = room_coords[2];
      if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) {
         base = find_adjacent_terrain(x, y);
         if (!base) {
            continue;
         }
         fluff = query_real_from_terrain_coord(x, y, z);
         fluff = base->query_terrain_from_real_coord(fluff->x, fluff->y, fluff->z);
         room_setup = base->query_char_map(fluff->x, fluff->y);
         if (room_setup && room_setup->type != AREA_OBSTACLE) {
            tmp = base->query_base_room(fluff->x, fluff->y, z, TERRAIN_MAP_ROOM_EXACT);
            if (tmp) {
               new_base_path = tmp;
               new_room = load_object(tmp);
               base += ":" + fluff->x + ":" + fluff->y + ":" + z;
            } else {
               new_room = 0;
               new_base_path = 0;
            }
         }
      } else {
         room_setup = query_char_map(x, y);
         if (room_setup && room_setup->type != AREA_OBSTACLE) {
            tmp = query_base_room(x, y, z, TERRAIN_MAP_ROOM_EXACT);
            new_base_path = tmp;
            if (tmp) {
               new_room = load_object(tmp);
               base = main_base + ":" + x + ":" + y + ":" + z;
            } else {
               new_room = 0;
            }
         }
      }
      if (!room_setup || !new_room) {
         continue;
      }
      key = room_setup->char;
      if (!coords[0] || !coords[1]) {
         miss_road[(coords[0] + 1) * 3 + coords[1] + 1] = new_base_path;
      } else {
         if ((miss_road[(coords[0] + 1) * 3 + 1] != new_base_path ||
              miss_road[coords[1] + 4] != new_base_path) &&
             miss_road[coords[1] + 4] &&
             miss_road[(coords[0] + 1) * 3 + 1] &&
             !miss_road[coords[1] + 4]->can_move_between(key, direc,
                                    miss_road[(coords[0] + 1) * 3 + 1],
                                    miss_road[coords[1] + 4], new_base_path)) {
            continue;
         }
      }
      switch(room_setup->type) {
         case AREA_OBSTACLE   :
            break;
         case AREA_ROAD       :
         case AREA_ROOM       :
         case AREA_WORLD      :
           if (ignore_exits[direc]) {
              break;
           }
           if (new_room->can_enter_from(key_here, direc, base_path) &&
                room->can_exit_to(key, direc, new_base_path)) {
              tmp = new_room->query_enter_exit_direction(key, key_here, direc, room, base_path);
              if (tmp) {
                 room->add_exit(tmp, base, "road");
                 walk_full = tmp;
              } else {
                 room->add_exit(direc, base, "road");
                 room->add_exit(walk_pre + direc, base, "road");
                 room->add_default_exit(direc, base);
                 walk_full = walk_pre + direc;
              }
              if (coords[4]) {
                 room->modify_exit(walk_full, coords[4]);
                 room->modify_exit(direc, coords[4]);
              }
              if (key_here == key ||
                  (road_jump &&
                   room_setup->room_jump_matching &&
                   room_setup->room_jump == road_jump)) {
                 exit_mods = room->get_to_same(_direcs[direc][2], direc, key, new_base_path);
                 if (exit_mods) {
                    room->modify_exit(direc, exit_mods);
                    room->modify_exit(walk_full, exit_mods);
                 }
                 if (room_setup->room_jump > 1) {
                    room->modify_exit(walk_full, ({ "obvious", 0 }));
                    room->add_variable_exit(journey_pre + direc);
                    room->add_exit(journey_pre + direc, base, "road");
                    exit_mods = room->get_to_same(walk_full, journey_pre + direc, key, new_base_path);
                    if (coords[4]) {
                       room->modify_exit(journey_pre + direc, coords[4]);
                    }
                    if (exit_mods) {
                        room->modify_exit(journey_pre + direc, exit_mods);
                    }
                 }
              } else {
                 exit_mods = room->get_to_other(_direcs[direc][2], direc, key, new_base_path);
                 if (exit_mods) {
                     room->modify_exit(walk_full, exit_mods);
                 }
                 exit_mods = new_room->
                             get_from_other(_direcs[direc][2], direc, key_here, base_path);
                 if (exit_mods) {
                     room->modify_exit(walk_full, exit_mods);
                 }
              }
              room->modify_exit(direc, ({ "obvious", 0 }));
           }
           break;
      }
      if ((key_here != key) && (member_array(key[0], outside_types) < 0)) {
         outside_types += key;
      }
      adjacent = room_setup->adjacent_desc;
      if (adjacent && strlen(adjacent) > 1) {
         if (room->can_view_adjacent_desc(room_setup->char,
                                          key_here,
                                          room_setup->path,
                                          z,
                                          direc)) {
            if (!room_setup->whole_sentance) {
               adjacent_sent[adjacent] = 1;
            }
            if (!adjacent_descs[adjacent]) {
               adjacent_descs[adjacent] = ({ });
               if( room_setup->items ) {
                   if (!adjacent_sent[room_setup->char]) {
                      adjacent_sent[room_setup->char] = 1;
                      if( stringp( room_setup->items ) &&
                          stringp( room_setup->item_desc ) ) {
                          room->add_item( room_setup->items,
                              room_setup->item_desc );
                      } else if( arrayp( room_setup->items ) &&
                          arrayp( room_setup->item_desc ) &&
                          sizeof( room_setup->items ) ) {
                          if( sizeof( room_setup->items ) !=
                              sizeof( room_setup->item_desc ) ) {
                              debug_printf( "Error, unequal arrays.  Item not "
                                  "set." );
                          } else {
                              int i;
                              for( i = 0; i < sizeof( room_setup->items ); i++) {
                                  room->add_item( room_setup->items[i],
                                      room_setup->item_desc[i] );
                              }
                          }
                      }
                   }
               }
            }
            adjacent_descs[adjacent] += ({ direc });
         }
      }
   }
   sentances = ({ });
   foreach(adjacent, dirs in adjacent_descs) {
      tmp = replace_string(adjacent,
                "$D", query_multiple_short(dirs, "the", 1));
      if (adjacent_sent[adjacent]) {
         if (strlen(tmp) > 1) {
            sentances += ({ tmp });
         }
      } else if (tmp != "") {
         if (query_newline_mode()) {
            room_long += tmp + "\n";
         } else {
            room_long += "  " + tmp;
         }
      }
   }
   if (sizeof(sentances)) {
      if (!query_newline_mode()) {
         room_long += "  ";
      }
      room_long += capitalize(query_multiple_short(sentances, "the", 1)) + ".";
      if (query_newline_mode()) {
         room_long += "\n";
      }
   }
   room->set_outside_types(outside_types);
   add_signposts(room);
   setup_zones(room);
   exit = calc_features(room);
   if (_real_coords && (_real_coords->x1 || _real_coords->x2)) {
      fluff = query_real_from_terrain_coord(room_coords[0], room_coords[1], 0);
      foreach (string title in TERRAIN_MAP_WORLD_MAP->query_features_at(fluff->x, fluff->y)) {
         if (!room->can_view_feature(title)) {
            continue;
         }
         distant = title->query_feature_desc_from(fluff->x, fluff->y, fluff->z);
         if (sizeof(distant)) {
            if (sizeof(exit)) {
               foreach (direc, int range in distant) {
                  if (exit[direc] && exit[direc] < range) {
                     map_delete(distant, direc);
                  }
               }
            }
            if (sizeof(distant)) {
               room->add_distant_feature(title, distant);
            }
         }
      }
   }
   calc_random_descs(room, key_here);
   calc_random_chats(room, key_here);
   room->set_extra_long(room_long);
   room->set_installed(1);
   room->calc_exits();
}
string find_adjacent_terrain(int x, int y)
{
   string index;
   class coord real;
   if (!_real_coords || !_real_coords->in_world_map) {
      return 0;
   }
   index = x + ":" + y;
   if (!undefinedp(_adjacent_terrains[index])) {
      return _adjacent_terrains[index];
   }
   real = query_real_from_terrain_coord(x, y, 0);
   _adjacent_terrains[index] = TERRAIN_MAP_WORLD_MAP->find_terrain_at(real->x, real->y);
   return _adjacent_terrains[index];
}
void find_all_adjacent_terrains() {
   find_adjacent_terrain(-1,-1);
   find_adjacent_terrain(-1,0);
   find_adjacent_terrain(-1,40);
   find_adjacent_terrain(0,40);
   find_adjacent_terrain(40,40);
   find_adjacent_terrain(40,0);
   find_adjacent_terrain(40,-1);
   find_adjacent_terrain(0,-1);
}
string* debug_adjacent_terrains() {
   return ({ find_adjacent_terrain(-1, 0),
             find_adjacent_terrain(0, -1),
             find_adjacent_terrain(0, _height),
             find_adjacent_terrain(_width, 0) });
}
mixed* query_rooms_to(int x, int y, int z, string direc, int len,
                       string main_key, int jump_len, int road_type ) {
   class char_map_data  room_setup;
   class coord real;
   string new_direc;
   string found_direc;
   string terr;
   string bit;
   int num;
   int found;
   int old_x;
   int old_y;
   int new_x;
   int new_y;
   mixed* ret;
   mixed* data;
   ret = ({ ({ }), ({ }) });
   do {
      data = _direcs[direc];
      if (!data) {
         debug_printf("Bad direction %O\n", direc);
         continue;
      }
      old_x = x;
      old_y = y;
      x += data[0];
      y += data[1];
      if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) {
         terr = find_adjacent_terrain(x, y);
         if (!terr) {
            return ret;
         }
         real = query_real_from_terrain_coord(x, y, 0);
         data = terr->query_more_terrains_rooms_from(real->x, real->y, real->z, direc,
                                 len - num, jump_len,
                                 main_key, road_type);
         if (sizeof(data)) {
            ret[0] += data[0];
            ret[1] += data[1];
         }
         return ret;
      }
      ret[0] += ({ direc });
      bit = sprintf("%d:%d:%d", x, y, z);
      ret[1] += ({ sprintf("%s:%s", base_name(this_object()), bit) });
      if (_standard_exits[bit]) {
         break;
      }
      if (road_type) {
         found = 0;
         foreach (new_direc, data in _direcs) {
            new_x = x + data[0];
            new_y = y + data[1];
            if (new_x != old_x || new_y != old_y) {
               if ((new_x < 0) || (new_x >= _width) || (new_y < 0) || (new_y >= _height)) {
                  terr = find_adjacent_terrain(new_x, new_y);
                  if (terr) {
                     real = query_real_from_terrain_coord(new_x, new_y, z);
                     real = terr->query_terrain_from_real_coord(real->x, real->y, z);
                     room_setup = terr->query_char_map(real->x, real->y);
                  } else {
                     room_setup = 0;
                  }
               } else {
                  room_setup = query_char_map(new_x, new_y);
               }
               if (room_setup && room_setup->room_jump == jump_len) {
                  found_direc = new_direc;
                  found++;
               }
            }
         }
         if (found == 1) {
            direc = found_direc;
         } else {
            break;
         }
      } else {
         room_setup = query_char_map(x + data[0], y + data[1]);
         if (!room_setup || room_setup->char != main_key) {
            break;
         }
      }
   } while (num++ < len);
   return ret;
}
mixed* query_more_terrains_rooms_from(int x, int y, int z, string direc,
                                       int moves_left, int jump,
                                       string main_key, int road_jump) {
   class coord bing;
   class char_map_data  room_setup;
   int found;
   string found_direc;
   string new_direc;
   mixed* data;
   int new_x;
   int new_y;
   bing = query_terrain_from_real_coord(x, y, 0);
   room_setup = query_char_map(bing->x, bing->y);
   if (road_jump) {
      if (room_setup->room_jump != jump) {
         data = _direcs[direc];
         bing->x -= data[0];
         bing->y -= data[1];
         foreach (new_direc, data in _direcs) {
            new_x = bing->x + data[0];
            new_y = bing->y + data[1];
            room_setup = query_char_map(new_x, new_y);
            if (room_setup && room_setup->room_jump == jump) {
               found = 1;
               found_direc = new_direc;
               break;
            }
         }
         if (!found) {
            return ({ });
         }
         direc = found_direc;
      } else {
         data = _direcs[direc];
         bing->x -= data[0];
         bing->y -= data[1];
      }
      return query_rooms_to(bing->x, bing->y, bing->z, direc, moves_left,
                            main_key, jump, road_jump);
   } else {
      if (room_setup->char == main_key) {
         data = _direcs[direc];
         bing->x -= data[0];
         bing->y -= data[1];
         return query_rooms_to(bing->x, bing->y, bing->z, direc, moves_left,
                            main_key, jump, road_jump);
      }
      return ({ });
   }
}
string* find_next_room_from(int x, int y, int z, string direc) {
   class char_map_data  room_setup;
   string test;
   object ob;
   object* obs;
   mixed* stuff;
   int pos;
   room_setup = query_char_map(x, y);
   stuff = query_rooms_to(x, y, z, direc, room_setup->room_jump,
                          room_setup->char, room_setup->room_jump,
                          room_setup->room_jump_matching);
   foreach (test in stuff[0]) {
      ob = find_object(test);
      if (ob) {
         obs = filter(all_inventory(ob), (: living($1) :));
         if (sizeof(obs) > 0) {
            return ({ test }) + stuff[0..pos];
         }
      }
      pos++;
   }
   if (sizeof(stuff[1])) {
      return ({ stuff[1][<1] }) + stuff[0];
   }
   return 0;
}
void add_room_to_zone(object room, string zone)
{
   object *zones = _room_zones[zone];
   if (!zones)
      zones = ({ room });
   else if (member_array(room, zones) == -1)
      zones += ({ room });
   _room_zones[zone] = zones - ({ 0 });
}
mixed query_room(int x, int y, int z)
{
   class char_map_data room_map = query_char_map(x, y);
   string base_path;
   object room;
   class coord real;
   base_path = query_base_room(x, y, z, TERRAIN_MAP_ROOM_EXACT);
   if (!base_path) {
      return 0;
   }
   room = clone_object(base_path);
   if (!room) {
      debug_printf("Unable to create room from %O at %O %O %O\n", base_path, x, y, z);
   } else {
      room->create_terrain_room();
      room->set_terrain_coords(x, y, z);
      real = query_real_from_terrain_coord(x, y, z);
      room->set_co_ord(({ real->x, real->y, real->z }));
      if (classp(_real_coords)) {
         room->set_room_size(({ _real_coords->xdiff, _real_coords->ydiff, _real_coords->zdiff }));
      }
      room->set_terrain_handler(base_name(this_object()));
      room->terrain_setup();
      room->add_property("base path", base_path);
      _room_map[y][x] = room;
      setup_room(room, base_path);
      if (room_map->type == AREA_WORLD && base_path != room_map->path) {
         room_map->path->setup_in_terrain(room, x, y, z);
      }
   }
   return room;
}
object query_room_at(int x, int y, int z)
{
   if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
      return 0;
   return find_object(sprintf("%s:%d:%d:%d", base_name(this_object()), x, y, z));
}
object *query_rooms_in_block(int x, int y, int z, int width, int height)
{
   int      h, v;
   mixed    *result = ({ });
   object   room;
   for (h = x; h < (x + width); h++) {
      for (v = y; v < (y + height); v++) {
         room = query_room_at(h, v, z);
         if (room)
            result = result + ({ room });
      }
   }
   return result;
}
varargs object *query_rooms_in_range(int x, int y, int z, int max, int min)
{
   int      h, v;
   mixed    *result = ({ });
   object   room;
   int    dist;
   for (h = x - max; h <= (x + max); h++) {
      for (v = y - max; v <= (y + max); v++) {
        dist = to_int(sqrt(pow(x - h, 2) + pow(y - v, 2)) + 0.4999);
        if ((dist > max) || (dist < min))
           continue;
         room = query_room_at(h, v, z);
         if (room)
            result = result + ({ room });
      }
   }
   return result;
}
object load_room_at(int x, int y, int z)
{
   class char_map_data room_map = query_char_map(x, y);
   if (!room_map) {
      debug_printf("Unable to load room at %d %d\n", x, y);
      return 0;
   }
   if (room_map->type == AREA_OBSTACLE) {
      return 0;
   }
   return load_object(sprintf("%s:%d:%d:%d", base_name(this_object()), x, y, z));
}
class char_map_data query_char_map(int x, int y)
{
   string   type;
   class char_map_data  room_map;
   if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) {
      return 0;
   }
   if (x >= sizeof(_area_map[y])) {
      debug_printf("The x value is out of range: %d > %d", x, sizeof(_area_map[y]));
      return 0;
   }
   type = _area_map[y][x..x];
   room_map = copy(_char_map[type]);
   if (!room_map) {
      debug_printf("There is no char type for '%s'", type);
      return 0;
   }
   room_map->char = type;
   return room_map;
}
string query_debug_map(int x, int y, int width, int showx, int showy) {
   int i;
   int j;
   int sx;
   int sy;
   int ny;
   string ret;
   string base;
   string new_base;
   string colour;
   ret = "";
   sx = x - width / 2;
   sy = y + width / 2;
   for (j = 0; j < width; j++) {
      if (sy - j >= 0 && sy - j < _height) {
         for (i = 0; i < width; i++) {
            if (sx + i >= 0 && sx + i < _width) {
               if (sx +i == showx && sy - j == showy) {
                  ret += "%^YELLOW%^" + _area_map[sy - j][sx + i..sx + i] +
                         "%^RESET%^";
                  colour = 0;
               } else {
                  if (colour) {
                     ret += "%^RESET%^";
                     colour = 0;
                  }
                  ret += _area_map[sy - j][sx + i..sx + i];
               }
            } else {
               if (sx + i >= _width) {
                  base = find_adjacent_terrain(_width + 1, sy - j);
               } else {
                  base = find_adjacent_terrain(-1, sy - j);
               }
               if (base) {
                  if (colour != "%^CYAN%^") {
                     ret += "%^BOLD%^%^CYAN%^";
                     colour = "%^CYAN%^";
                  }
                  if (sx + i >= _width) {
                     ret += base->query_debug_map_char(sx + i - _width, sy - j);
                  } else {
                     ret += base->query_debug_map_char(sx + i + _width, sy - j);
                  }
               } else {
                  ret += " ";
               }
            }
         }
         if (colour) {
            ret += "%^RESET%^";
            colour = 0;
         }
         ret += "\n";
      } else {
         base = find_adjacent_terrain(sx + i, sy - j);
         if (base) {
            if (sy - j < 0) {
               ny = sy - j + _height;
            } else {
               ny = sy - j - _height;
            }
            for (i = 0; i < width; i++) {
               if (sx + i >= 0 && sx + i < _width) {
                  if (colour != "%^MAGENTA%^") {
                     ret += "%^BOLD%^%^MAGENTA%^";
                     colour = "%^MAGENTA%^";
                  }
                  ret += base->query_debug_map_char(sx + i, ny);
               } else {
                  new_base = find_adjacent_terrain(sx + i, sy - j);
                  if (new_base) {
                     if (colour != "%^RED%^") {
                        ret += "%^BOLD%^%^RED%^";
                        colour = "%^RED%^";
                     }
                     if (sx + i >= _width) {
                        ret += new_base->query_debug_map_char(sx + i - _width, ny);
                     } else {
                        ret += new_base->query_debug_map_char(sx + i + _width, ny);
                     }
                  } else {
                     ret += " ";
                  }
               }
            }
            ret += "%^RESET%^\n";
            colour = 0;
         }
      }
   }
   return ret;
}
string query_debug_map_char(int x, int y) {
   return _area_map[y][x..x];
}
string query_debug_map_feature(string name) {
   int x;
   int y;
   class feature_data feature;
   mixed data;
   string ret;
   int colour;
   int found;
   feature = _features[name];
   ret = "";
   colour = 0;
   for (y = _height - 1; y >= 0; y--) {
      for (x = 0; x < _width; x++) {
         data = feature->feature_ob->query_feature_desc_from(x, y, 0, 1);
         found = sizeof(data);
         if (found) {
            if (!colour) {
               ret += "%^YELLOW%^";
               colour = 1;
            }
         } else {
            if (colour) {
               ret += "%^RESET%^";
               colour = 0;
            }
         }
         ret += _area_map[y][x..x];
      }
      ret += "%^RESET%^\n";
      colour = 0;
   }
   return ret;
}
string query_debug_map_feature_distant(string feature) {
   int x;
   int y;
   mixed data;
   string ret;
   int colour;
   class coord fluff;
   ret = "";
   colour = 0;
   for (y = _height - 1; y >= 0; y--) {
      for (x = 0; x < _width; x++) {
         fluff = query_real_from_terrain_coord(x, y, 0);
         data = feature->query_feature_desc_from(fluff->x, fluff->y, fluff->z);
         if (data && sizeof(data)) {
            if (!colour) {
               ret += "%^YELLOW%^";
               colour = 1;
            }
         } else {
            if (colour) {
               ret += "%^RESET%^";
               colour = 0;
            }
         }
         ret += _area_map[y][x..x];
      }
      ret += "%^RESET%^\n";
      colour = 0;
   }
   return ret;
}
private void add_key(mapping key, string char, string str) {
  if(strsrch(str, "intersection") != -1)
    return;
  if(!key[char])
    key[char] = str;
  else if(strsrch(key[char], str) == -1 ) {
    key[char] += ", " + str;
  }
}
private int update_map(mapping data, mixed* map, mapping key, mixed *colours,
                       int x, int y, int z, int offx, int offy) {
   class char_map_data info;
   string char, colour, tmp;
   string room;
   int block;
   object ob;
   if (x < 0) {
      if (y < 0) {
         data["-y-x"] = 1;
      } else if (y >= _height) {
         data["+y-x"] = 1;
      } else {
         data["-x"] = 1;
      }
      return 0;
   } else if (x >= _width) {
      if (y < 0) {
         data["-y+x"] = 1;
      } else if (y >= _height) {
         data["+y+x"] = 1;
      } else {
         data["+x"] = 1;
      }
      return 0;
   } else if (y < 0) {
      data["-y"] = 1;
      return 0;
   } else if (y >= _height) {
      data["+y"] = 1;
      return 0;
   }
   info = query_char_map(x, y);
   if (!info) {
      return 1;
   }
   if (info->type == AREA_OBSTACLE) {
      map[y - offy][x - offx] = info->char;
      colours[y - offy][x - offx] = info->colour;
      if(!info->colour) {
        colours[y - offy][x - offx] = "%^BLUE%^";
      }
      if (info->room_desc == "Obstacle" && stringp(info->items)) {
        add_key(key, info->char, info->items);
      } else if (info->room_desc != "") {
        add_key(key, info->char, info->room_desc);
      } else {
         map[y - offy][x - offx] = " ";
      }
      data["block" + info->char] = 1;
      return 1;
   } else {
      char = data[info->char];
      colour = data[info->colour];
      if (!char || !colour) {
         room = query_base_room(x, y, z, TERRAIN_MAP_ROOM_MAP);
         if (room) {
            ob = load_object(room);
            if (ob) {
               char = ob->query_terrain_map_character();
               colour = ob->query_terrain_map_colour();
               block = ob->query_terrain_map_block();
               if(char && ob) {
                  tmp = ob->query_key_desc();
                  if(!tmp) {
                     tmp = ob->query_short();
                  }
                  if(!tmp) {
                     debug_printf("Room %s has no short.", base_name(ob));
                  } else {
                     add_key(key, char, tmp);
                  }
               }
               if (block || info->height > z) {
                  data["block" + info->char] = 1;
               }
            } else {
               debug_printf("Unable to find %O\n", room);
            }
         }
         if (!char) {
            char = info->char;
         }
         if(!colour) {
            colour = info->colour;
         }
         data[info->char] = char;
      }
      map[y - offy][x - offx] = char;
      colours[y - offy][x - offx] = colour;
   }
   if(char && !key[char] && !data["nokey"+info->char]) {
      data["nokey" + info->char] = 1;
      debug_printf("No key for %s", char);
   }
   return data["block" + info->char];
}
private string line_in_map(mapping data, mixed* map, mapping key,
                           mixed *colours, int offx, int offy,
                           int sx, int sy, int ex, int ey, int z) {
   int x;
   int y;
   int dx;
   int dy;
   int incx;
   int incy;
   int balance;
   if (ex >= sx) {
      dx = ex - sx;
      incx = 1;
   } else {
      dx = sx - ex;
      incx = -1;
   }
   if (ey >= sy) {
      dy = ey - sy;
      incy = 1;
   } else {
      dy = sy - ey;
      incy = -1;
   }
   x = sx;
   y = sy;
   if (dx >= dy) {
      dy <<= 1;
      balance = dy - dx;
      dx <<= 1;
      while (x != ex) {
         if (update_map(data, map, key, colours, x, y, z, offx, offy)) {
            break;
         }
         if (balance >= 0) {
            y += incy;
            balance -= dx;
         }
         balance += dy;
         x += incx;
      }
   } else {
      dx <<= 1;
      balance = dx - dy;
      dy <<= 1;
      while (y != ey) {
         if (update_map(data, map, key, colours, x, y, z, offx, offy)) {
            break;
         }
         if (balance >= 0) {
            x += incx;
            balance -= dy;
         }
         balance += dx;
         y += incy;
      }
   }
   update_map(data, map, key, colours, x, y, z, offx, offy);
}
private void update_blocking(mapping data,
                             mixed* map, mixed* colours, int x, int y,
                             int distance) {
   int dx;
   int dy;
   int adx;
   int ady;
   int dist;
   int nx;
   int ny;
   int tx;
   int ty;
   int incx;
   int incy;
   string* template;
   string str;
   dx = (x - distance);
   dy = (y - distance);
   str = " ";
   if (dx < 0) {
      adx = - dx;
      incx = -1;
   } else {
      adx = dx;
      incx = 1;
   }
   if (dy < 0) {
      ady = - dy;
      incy = -1;
   } else {
      ady = dy;
      incy = 1;
   }
   if (incx != incy) {
      incx = -incx;
      incy = - incy;
   }
   if (adx > ady) {
      template = TERRAIN_MAP_WORLD_MAP->query_blocking_template(ady, adx, 0);
   } else {
      template = TERRAIN_MAP_WORLD_MAP->query_blocking_template(adx, ady, 0);
   }
   if (!template) {
      debug_printf("Error with the template");
      return ;
   }
   dist = distance + 1;
   for (tx = 0; tx < dist; tx++) {
      for (ty = 0; ty < dist; ty++) {
         if (template[tx][ty] == '*') {
            if (adx > ady) {
               nx = distance + tx * incx;
               ny = distance + ty * incy;
            } else {
               nx = distance + ty * incx;
               ny = distance + tx * incy;
            }
            if (nx < sizeof(map) && ny < sizeof(map[nx]) &&
                nx >= 0 && ny >= 0) {
               map[nx][ny] = str;
               colours[nx][ny] = 0;
            }
            if (adx == ady) {
               nx = distance + tx * incx;
               ny = distance + ty * incy;
               map[nx][ny] = str;
               colours[nx][ny] = 0;
            } else if (adx == 0) {
               nx = distance + ty * incx;
               ny = distance - tx * incy;
               map[nx][ny] = str;
            } else if (ady == 0) {
               nx = distance - tx * incx;
               ny = distance + ty * incy;
               map[nx][ny] = str;
               colours[nx][ny] = 0;
            }
         }
      }
   }
}
mapping query_player_map_internal_template(mixed* map, mapping key,
                                  mixed *colours, int x_c, int y_c, int z_c,
                                  int distance) {
   int offx;
   int offy;
   int x;
   int y;
   mapping data;
   data = ([ ]);
   offx = x_c - distance;
   offy = y_c - distance;
   for (x = 0; x < sizeof(map); x++) {
      for (y = 0; y < sizeof(map[x]); y++) {
         if (map[y][x] == 1) {
            if (update_map(data, map, key, colours, x + offx, y + offy, z_c, offx, offy)) {
               if (x > 0) {
                  if (y > 0 && data["block" + map[y-1][x-1]]) {
                     update_blocking(data, map, colours, x, y, distance);
                     update_blocking(data, map, colours, x, y-1, distance);
                  } else if (y < sizeof(map) - 1 && data["block" + map[y+1][x-1]]) {
                     update_blocking(data, map, colours, x, y, distance);
                     update_blocking(data, map, colours, x, y + 1, distance);
                  } else if (y > 0 && data["block" + map[y-1][x]]) {
                     update_blocking(data, map, colours, x, y, distance);
                     update_blocking(data, map, colours, x - 1, y - 1, distance);
                  } else {
                     update_blocking(data, map, colours, x, y, distance);
                  }
               } else {
                  update_blocking(data, map, colours, x, y, distance);
               }
            }
         }
      }
   }
   return data;
}
string query_player_map_template(int x_c, int y_c, int z_c, int visibility,
             int max_size) {
   string ret, item, base, current, *keys;
   mixed *map, *colours;
   mapping data, key;
   int i, j;
   int distance;
   distance = _visible_distance * visibility / 100;
   if (!distance) {
      distance = 1;
   }
   data = ([ ]);
   key = ([ ]);
   map = ({ });
   colours = ({ });
   map = TERRAIN_MAP_WORLD_MAP->query_map_template(distance);
   colours = TERRAIN_MAP_WORLD_MAP->query_map_template(distance);
   if (max_size && (max_size % 2) != 1) {
      max_size--;
   }
   if (max_size && sizeof(map) > max_size) {
      j = (max_size - 1) / 2;
      map = map[distance - j..distance + j];
      colours = colours[distance - j..distance + j];
      for (i = 0; i < sizeof(map); i++) {
         map[i] = map[i][distance - j..distance + j];
         colours[i] = colours[i][distance - j..distance + j];
      }
      x_c += (distance - j);
      y_c += (distance - j);
   }
   data = query_player_map_internal_template(map, key, colours, x_c, y_c, z_c,
                                    distance);
   if (data["-y"]) {
     base = find_adjacent_terrain(x_c, -1);
     if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal_template(map, key, colours, x_c,
                                            y_c + _height, z_c, distance);
         }
      }
   }
   if (data["+y"]) {
      base = find_adjacent_terrain(x_c, _height + 1);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal_template(map, key, colours, x_c,
                                            y_c - _height, z_c, distance);
         }
      }
   }
   if (data["-x"]) {
      base = find_adjacent_terrain(-1, y_c);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal_template(map, key, colours, x_c + _width,
                                            y_c, z_c, distance);
         }
      }
   }
   if (data["+x"]) {
      base = find_adjacent_terrain(_width + 1, y_c);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal_template(map, key, colours, x_c - _width,
                                            y_c, z_c, distance);
         }
      }
   }
   if (data["-y+x"]) {
      base = find_adjacent_terrain(_width + 1, -1);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal_template(map, key, colours, x_c - _width,
                                            y_c + _height, z_c,
                                            distance);
         }
      }
   }
   if (data["+y+x"]) {
      base = find_adjacent_terrain(_width + 1, _height + 1);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal_template(map, key, colours, x_c - _width,
                                            y_c - _height, z_c,
                                            distance);
         }
      }
   }
   if (data["+y-x"]) {
      base = find_adjacent_terrain(-1, _height + 1);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal_template(map, key, colours, x_c + _width,
                                            y_c - _height, z_c,
                                            distance);
         }
      }
   }
   if (data["-y-x"]) {
      base = find_adjacent_terrain(-1, -1);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal_template(map, key, colours, x_c + _width,
                                            y_c + _height, z_c,
                                            distance);
         }
      }
   }
   map[sizeof(map) / 2][sizeof(map) / 2] = "@";
   if(!this_player()->query_property(PLAYER_PLAIN_MAPS)) {
     colours[sizeof(map) / 2][sizeof(map) / 2] = "%^YELLOW%^";
     for(i=0; i<sizeof(map); i++) {
       current = "";
       for(j=0; j<sizeof(map); j++) {
         if(map[i][j] == "\r" || !stringp(map[i][j])) {
           map[i][j] = " ";
         }
         if (!current || current == " ") {
           current = "";
         }
         if(!colours[i][j] || colours[i][j] == " ") {
           colours[i][j] = "";
         }
         if(colours[i][j] != current) {
           if (colours[i][j] == "" || !stringp(colours[i][j])) {
             if(current != "" && current != " ") {
               map[i][j] = "%^RESET%^" + map[i][j];
               current = "";
             }
           } else if (colours[i][j] != "\r") {
             map[i][j] = colours[i][j] + map[i][j];
             current = colours[i][j];
           }
         }
         if(i == x_c && j == y_c && current != "") {
           map[i][j] += current;
         }
       }
       if(current) {
         map[i][j-1] += "%^RESET%^";
       }
     }
   }
   if(_key && !max_size) {
     keys = ({ });
     foreach(item in keys(key)) {
       keys += map(explode(sprintf("%s %-=40s", item, key[item]), "\n"),
                   (: "     " + $1 :));
     }
   }
   ret = "";
   for(i = sizeof(map) - 1; i >= 0; i--) {
     ret += implode(map(map[i], (: stringp($1) ? $1 : " " :)), "");
     if(!max_size && sizeof(map)-2-i>= 0 && sizeof(map)-2-i < sizeof(keys)) {
       ret += keys[sizeof(map)-2-i];
     }
     ret += "\n";
   }
   return ret;
}
mapping query_player_map_internal(mixed* map, mapping key, mixed *colours,
                                  int x_c, int y_c, int z_c, int distance) {
   int x, y, e, u, v;
   int endx, endy, offx, offy;
   mapping data;
   data = ([ ]);
   offx = x_c - distance;
   offy = y_c - distance;
   x = 0;
   y = distance;
   u = 1;
   v = 2 * distance - 1;
   e = 0;
   while (x < y) {
      endx = x_c + x;
      endy = y_c + y;
      line_in_map(data, map, key, colours, offx, offy, x_c, y_c, endx, endy, z_c);
      endx = x_c + y;
      endy = y_c - x;
      line_in_map(data, map, key, colours, offx, offy, x_c, y_c, endx, endy, z_c);
      endx = x_c - x;
      endy = y_c - y;
      line_in_map(data, map, key, colours, offx, offy, x_c, y_c, endx, endy, z_c);
      endx = x_c - y;
      endy = y_c + x;
      line_in_map(data, map, key, colours, offx, offy, x_c, y_c, endx, endy, z_c);
      x++;
      e += u;
      u += 2;
      if (v < 2 * e) {
         y--;
         e -= v;
         v -= 2;
      }
      if (x > y) {
         break;
      }
      endx = x_c + y;
      endy = y_c + x;
      line_in_map(data, map, key, colours, offx, offy, x_c, y_c, endx, endy, z_c);
      endx = x_c + x;
      endy = y_c - y;
      line_in_map(data, map, key, colours, offx, offy, x_c, y_c, endx, endy, z_c);
      endx = x_c - y;
      endy = y_c - x;
      line_in_map(data, map, key, colours, offx, offy, x_c, y_c, endx, endy, z_c);
      endx = x_c - x;
      endy = y_c + y;
      line_in_map(data, map, key, colours, offx, offy, x_c, y_c, endx, endy, z_c);
   }
   for(y=0; y<sizeof(map); y++)
     for(x=1; x<sizeof(map[y])-1; x++)
       if(map[y][x] == "\r" && map[y][x-1] != "\r" && map[y][x+1] != "\r") {
         update_map(data, map, key, colours, x + offx, y + offy, z_c, offx,
                    offy);
       }
   return data;
}
string query_player_map(int x_c, int y_c, int z_c, int visibility) {
   string ret, item, base, current, *keys;
   mixed *map, *colours;
   mapping data, key, colour_key;
   int i, j;
   int distance;
   distance = _visible_distance * visibility / 100;
   if (!distance) {
      distance = 1;
   }
   data = ([ ]);
   key = ([ ]);
   map = ({ });
   colours = ({ });
   for (i = 0; i < distance * 2 + 1; i++) {
      map += ({ allocate(distance * 2 + 1, "\r") });
      colours += ({ allocate(distance * 2 + 1, "\r") });
   }
   data = query_player_map_internal(map, key, colours, x_c, y_c, z_c,
                                    distance);
   if (data["-y"]) {
     base = find_adjacent_terrain(x_c, -1);
     if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal(map, key, colours, x_c,
                                            y_c + _height, z_c, distance);
         }
      }
   }
   if (data["+y"]) {
      base = find_adjacent_terrain(x_c, _height + 1);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal(map, key, colours, x_c,
                                            y_c - _height, z_c, distance);
         }
      }
   }
   if (data["-x"]) {
      base = find_adjacent_terrain(-1, y_c);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal(map, key, colours, x_c + _width,
                                            y_c, z_c, distance);
         }
      }
   }
   if (data["+x"]) {
      base = find_adjacent_terrain(_width + 1, y_c);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal(map, key, colours, x_c - _width,
                                            y_c, z_c, distance);
         }
      }
   }
   if (data["-y+x"]) {
      base = find_adjacent_terrain(_width + 1, -1);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal(map, key, colours, x_c - _width,
                                            y_c + _height, z_c,
                                            distance);
         }
      }
   }
   if (data["+y+x"]) {
      base = find_adjacent_terrain(_width + 1, _height + 1);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal(map, key, colours, x_c - _width,
                                            y_c - _height, z_c,
                                            distance);
         }
      }
   }
   if (data["+y-x"]) {
      base = find_adjacent_terrain(-1, _height + 1);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal(map, key, colours, x_c + _width,
                                            y_c - _height, z_c,
                                            distance);
         }
      }
   }
   if (data["-y-x"]) {
      base = find_adjacent_terrain(-1, -1);
      if (base) {
         if (!load_object(base)) {
            debug_printf("Unable to load %O\n", base);
         } else {
            base->query_player_map_internal(map, key, colours, x_c + _width,
                                            y_c + _height, z_c,
                                            distance);
         }
      }
   }
   y_c -= y_c - distance;
   x_c -= x_c - distance;
   if(!this_player()->query_property(PLAYER_PLAIN_MAPS)) {
     colour_key = ([ ]);
     map[y_c][x_c] = "%^YELLOW%^@%^RESET%^";
     for(i=0; i<sizeof(map); i++) {
       current = "";
       for(j=0; j<sizeof(map); j++) {
         if(map[i][j] == "\r")
           map[i][j] = " ";
         if(!current || current == " ") current = "";
         if(!colours[i][j] || colours[i][j] == " ") colours[i][j] = "";
         if(key[map[i][j]])
           colour_key[colours[i][j] + map[i][j] + "%^RESET%^"] =
             key[map[i][j]];
         if(colours[i][j] != current) {
           if(colours[i][j] == "") {
             if(current != "" && current != " ") {
               map[i][j] = "%^RESET%^" + map[i][j];
               current = "";
             }
           } else if(colours[i][j] != "\r") {
             map[i][j] = colours[i][j] + map[i][j];
             current = colours[i][j];
           }
         }
         if(i == x_c && j == y_c && current != "")
           map[i][j] += current;
       }
       if(current)
         map[i][j-1] += "%^RESET%^";
     }
   } else {
     map[y_c][x_c] = "@";
     colour_key = key;
   }
   if(_key) {
     keys = ({ });
     foreach(item in keys(colour_key)) {
       keys += map(explode(sprintf("%s %-=40s", item, colour_key[item]), "\n"),
                           (: "     " + $1 :));
     }
   }
   ret = "";
   for(i = sizeof(map) - 1; i >= 0; i--) {
     ret += implode(map[i], "");
     if(sizeof(map)-2-i>= 0 && sizeof(map)-2-i < sizeof(keys))
       ret += keys[sizeof(map)-2-i];
     ret += "\n";
   }
   if(this_player()->query_property(PLAYER_PLAIN_MAPS))
     ret = replace_string(ret, "\r", " ");
   return ret;
}
class char_map_data query_char_map_real_coord(int x, int y)
{
   class coord our;
   our = query_terrain_from_real_coord(x, y, 0);
   return query_char_map(our->x, our->y);
}
object *query_rooms_in_zone(string zone)
{
   if (_room_zones[zone]) {
      _room_zones[zone] -= ({ 0 });
      return _room_zones[zone];
   }
   return ({ });
}
varargs void tell_zones(mixed zones, string message, mixed mess_class)
{
   object  *rooms = ({ });
   string  zone;
   if (!mess_class)
      mess_class = "zone_shout";
   if (stringp(zones))
      zones = ({ zones });
   foreach (zone in zones)
      rooms += query_rooms_in_zone(zone);
   if (sizeof(rooms))
      message(mess_class, message, rooms);
}
varargs void tell_feature(string title, mixed message)
{
   int     index;
   string  mess_class = sprintf("feature:%s", title);
   if (!_feature_rooms[title]) {
      return;
   }
   _feature_rooms[title] -= ({ 0 });
   if (!sizeof(_feature_rooms[title])) {
      return;
   }
   if (stringp(message)) {
      message(mess_class, message, _feature_rooms[title]);
   }
   if (arrayp(message)) {
      for (index = 0; index < sizeof(message); index++) {
         message(sprintf("%s:%d", mess_class, index), message[index],
         _feature_rooms[title]);
      }
   }
}
varargs string* query_distant_feature_desc(string title, mapping direcs,
                                           int visibility) {
   int       night = (WEATHER->query_tod() == "night");
   string str;
   str = title->calc_feature_desc(direcs, night, visibility);
   if (str) {
      return ({ str });
   }
   return ({ });
}
varargs string* query_feature_desc(string title, mapping direcs,
                                   int visibility) {
   class feature_data   feature;
   string*   item_desc;
   string*   dirs;
   int       night = (WEATHER->query_tod() == "night");
   string    direc;
   int       range;
   mapping   bits;
   int       index;
   string    str;
   int       new_range;
   if (!feature) {
      feature = _features[title];
   }
   if (!feature) {
      return ({ });
   }
   if( visibility == 0 ) {
      return ({ });
   }
   if (!sizeof(feature->descs)) {
      str = feature->feature_ob->calc_feature_desc(direcs, night,
                                                       visibility);
      if (str) {
         return ({ str });
      }
      return ({ });
   }
   bits = ([ ]);
   foreach (direc, range in direcs) {
      if (night) {
         item_desc = feature->night_descs;
      } else {
         item_desc = feature->descs;
      }
      if (!item_desc) {
         debug_printf("Bad night description for %O", title);
         continue;
      }
      new_range = range * 100 / visibility;
      if (feature->range > new_range && sizeof(item_desc)) {
         index = sizeof(item_desc) * new_range / feature->range;
         str = item_desc[index];
         if (str && str != "") {
            if (!bits[str]) {
               bits[str] = ({ });
            }
            bits[str] += ({ direc });
         }
      }
   }
   item_desc = ({ });
   foreach (str, dirs in bits) {
      item_desc += ({ replace_string(str, "$D", query_multiple_short(dirs)) });
   }
   return item_desc;
}
varargs string query_feature_item_desc(string title) {
   class feature_data   feature;
   mixed   item_desc;
   int       night = (WEATHER->query_tod() == "night");
   if (!feature) {
      feature = _features[title];
   }
   if (!feature) {
      return "";
   }
   if (night) {
      item_desc = feature->f_item_night_desc;
   } else {
      item_desc = feature->f_item_desc;
   }
   if (!pointerp(item_desc)) {
      return item_desc;
   }
   return item_desc[0];
}
varargs string get_a_feature_chat(string title, int range, string direc)
{
   class feature_data   feature;
   mixed     chat;
   int       night = (WEATHER->query_tod() == "night");
   if (!feature) {
      feature = _features[title];
   }
   if (!feature) {
      return "";
   }
   if (night) {
      chat = feature->night_chats;
   } else {
      chat = feature->chats;
   }
   if (!chat) {
      return "";
   }
   if (arrayp(chat)) {
      chat = chat[random(sizeof(chat))];
   }
   if (arrayp(chat)) {
      if ((range < 0) || (range >= sizeof(chat))) {
         return "";
      }
      chat = chat[range];
   }
   if (!stringp(chat)) {
      return "";
   }
   if (direc) {
      chat = replace(chat, ({ "$D", direc }));
   }
   return chat;
}
string get_an_outside_chat(string types)
{
   class char_map_data   item;
   string    *chats = ({ });
   int       index;
   mixed     *item_chats;
   for (index = 0; index < sizeof(types); index++) {
      item = _char_map[types[index..index]];
      if (!item) {
         continue;
      }
      item_chats = item->chats;
      if (!item_chats) {
         continue;
      }
      if (stringp(item_chats))
         chats += ({ item_chats });
      else if (arrayp(item_chats))
         chats += item_chats;
   }
   if (!sizeof(chats))
      return "";
   return chats[random(sizeof(chats))];
}
varargs void add_obstacle_type(string type, string description, mixed items, mixed item_desc, string room_desc)
{
   if (!type) {
      throw("Bad type");
   }
   if (!items) {
      items = ({ });
      item_desc = ({ });
   }
   if (!room_desc) {
      room_desc = "Obstacle";
   }
   _char_map[type] = new(class char_map_data,
                         type: AREA_OBSTACLE, adjacent_desc:description,
                         room_desc : room_desc,
                         items:items, item_desc:item_desc);
}
void add_special_type(string type, string base_path, int size, int road_skip, int height,
                      mapping height_rooms)
{
   _char_map[type] = new(class char_map_data,
                         type: AREA_ROOM, path:base_path,
                         room_jump : size,
                         room_jump_matching : road_skip,
                         height : height,
                         height_rooms : height_rooms);
}
void add_room_type(string type, string base_path)
{
   _char_map[type] = new(class char_map_data,
                         type: AREA_ROOM, path:base_path);
}
varargs void add_road_type(string type, string base_path, string room_desc,
              string description, mixed items, mixed item_desc)
{
   _char_map[type] = new(class char_map_data,
                        type: AREA_ROAD, adjacent_desc:description,
                        items:items, item_desc:item_desc,
                        room_desc:room_desc, path:base_path);
}
varargs void add_world_room_type(string type, string base_path) {
   mapping bits;
   string *tmp;
   if(file_size(base_path + ".c") == -1) {
     tmp = explode(base_path, "_edge");
     if(sizeof(tmp) && file_size(tmp[0] + ".c") > 0) {
       debug_printf("%s doesn't exist, using %s",
                    base_path, tmp[0]);
       base_path = tmp[0];
     }
   }
   if (file_size(base_path + ".c") > 0) {
      bits = base_path->query_adjacent_items();
      if (!mapp(bits)) {
         debug_printf("Incorrect room type %O", type);
      } else {
         _char_map[type] = new(class char_map_data,
                        type: AREA_WORLD,
                        path: base_path,
                        adjacent_desc:base_path->query_adjacent_description(),
                        items:keys(bits),
                        item_desc:values(bits),
                         room_jump : base_path->query_room_jump_size(),
                         height : base_path->query_default_height(),
                         room_jump_matching : base_path->query_follow_road());
      }
   } else {
      debug_printf("Unable to add %O since %O doesn't exist.", type, base_path);
   }
}
varargs void add_road_special_type(string type, string base_path,
              int size, int road_skip, int height,
              string room_desc,
              string description, mixed items, mixed item_desc,
              mapping height_rooms)
{
   _char_map[type] = new(class char_map_data,
                        type: AREA_ROAD, adjacent_desc:description,
                        items:items, item_desc:item_desc,
                        room_desc:room_desc, path:base_path,
                         room_jump : size,
                         height : height,
                         height_rooms : height_rooms,
                         room_jump_matching : road_skip);
}
varargs void add_exit_at(int x, int y, string direc, string dest,
                         string type, mixed modifiers)
{
   string   title = sprintf("%d:%d:%d", x, y, 0);
   if (!dest)
      return;
   if (!type)
      type = "road";
   if (!_standard_exits[title])
      _standard_exits[title] = ({ });
   _standard_exits[title] += ({ ([ "direc":direc, "dest":dest,
                                   "type":type, "modifiers":modifiers ]) });
}
varargs void add_z_exit_at(int x, int y, int z, string direc, string dest,
                         string type, mixed modifiers)
{
   string   title = sprintf("%d:%d:%d", x, y, z);
   if (!dest)
      return;
   if (!type)
      type = "road";
   if (!_standard_exits[title])
      _standard_exits[title] = ({ });
   _standard_exits[title] += ({ ([ "direc":direc, "dest":dest,
                                   "type":type, "modifiers":modifiers ]) });
}
void set_random_desc_limit(int new_limit)
{
   _random_desc_limit = new_limit;
}
void set_random_chat_limit(int new_limit)
{
   _random_chat_limit = new_limit;
}
void add_random_desc(string types, string description, mixed items, mixed item_desc)
{
   int   index;
   for (index = 0; index < sizeof(types); index++) {
      if (!_random_descs[types[index..index]])
         _random_descs[types[index..index]] = ({ });
      _random_descs[types[index..index]] += ({ ([ "desc": description,
                               "items":items, "item_desc":item_desc ]) });
   }
}
void add_random_chat(string types, string *chats)
{
   int   index;
   for (index = 0; index < sizeof(types); index++) {
      if (!_random_chats[types[index..index]])
         _random_chats[types[index..index]] = ({ });
      _random_chats[types[index..index]] += chats;
   }
}
void set_external_chats(string type, mixed chats)
{
   if (!_char_map[type]) {
      return;
   }
   ((class char_map_data)_char_map[type])->chats = chats;
}
void add_feature(string title, int x, int y, int width, int height,
                 int range, string *descs, mixed items, mixed item_desc,
                 string* night_descs,
                 mixed night_items)
{
   object region;
   object feature;
   region = clone_object(TERRAIN_MAP_REGION_RECTANGULAR);
   region->add_feature_position(x, y, width, height);
   feature = clone_object(TERRAIN_MAP_FEATURE_BASE);
   feature->set_region(region);
   feature->set_max_day_range(range);
   feature->set_max_night_range(range);
   _features[title] = new(class feature_data,
                         range:range, descs:descs,
                         f_items:items, f_item_desc:item_desc,
                         f_item_night_desc : night_items,
                         whole_sentance:1,
                         feature_ob : feature,
                         night_descs : night_descs);
}
void add_feature_sentance(string title, int x, int y, int width, int height,
                 int range, string *descs, mixed items, mixed item_desc,
                 string* night_descs, mixed night_items)
{
   object region;
   object feature;
   region = clone_object(TERRAIN_MAP_REGION_RECTANGULAR);
   region->add_feature_position(x, y, width, height);
   feature = clone_object(TERRAIN_MAP_FEATURE_BASE);
   feature->set_region(region);
   feature->set_max_day_range(range);
   feature->set_max_night_range(range);
   _features[title] = new(class feature_data,
                         feature_ob : feature,
                         range:range, descs:descs,
                         f_items:items, f_item_desc:item_desc,
                         f_item_night_desc : night_items,
                         whole_sentance:0,
                         night_descs : night_descs);
}
void add_feature_region(string title, object region,
                 int range, string *descs, mixed items, mixed item_desc,
                 string* night_descs,
                 mixed night_items,
                 int whole_sentance)
{
   object feature;
   feature = clone_object(TERRAIN_MAP_FEATURE_BASE);
   feature->set_region(region);
   feature->set_max_day_range(range);
   feature->set_max_night_range(range);
   _features[title] = new(class feature_data,
                         range:range, descs:descs,
                         f_items:items, f_item_desc:item_desc,
                         whole_sentance:whole_sentance,
                         f_item_night_desc : night_items,
                         feature_ob : feature,
                         night_descs : night_descs);
}
void add_feature_ob(string title, object feature) {
   if (_real_coords && _real_coords->xdiff) {
      feature->set_distance_multiplier(_real_coords->xdiff);
   }
   _features[title] = new(class feature_data,
                          f_items : feature->query_items(),
                          f_item_desc : feature->query_day_items(),
                          f_item_night_desc : feature->query_night_items(),
                          feature_ob : feature);
}
varargs void modify_feature(string title, string *descs, mixed item_desc)
{
   if (!_features[title]) {
      return;
   }
   if (descs) {
      _features[title]->descs = descs;
   }
   if (item_desc) {
      _features[title]->f_item_desc = item_desc;
   }
}
void set_feature_chats(string title, mixed *chats, mixed* night_chats)
{
   if (!_features[title]) {
      return;
   }
   ((class feature_data)_features[title])->chats = chats;
   ((class feature_data)_features[title])->night_chats = night_chats;
}
void remove_feature(string title)
{
   object room;
   if (!_features[title]) {
      return;
   }
   map_delete(_features, title);
   if (!_feature_rooms[title]) {
      return;
   }
   _feature_rooms[title] -= ({ 0 });
   foreach(room in _feature_rooms[title]) {
      room->remove_feature(title);
   }
   map_delete(_feature_rooms, title);
}
void add_sign(int x, int y, string sign_long, mixed sign_read_mess,
              string sign_short, mixed sign_name, string sign_language)
{
   string   title = sprintf("%d:%d", x, y);
   _signposts[title] = new(class sign_data,
                         long:sign_long, read_mess:sign_read_mess,
                         short:sign_short, name:sign_name,
                         language:sign_language);
}
void add_zones(string type, string *zone_names)
{
   _zone_types[type] = zone_names;
}
void reset_handler()
{
   mixed *rooms;
   if (arrayp(_room_map)) {
      foreach(rooms in _room_map) {
         rooms->dest_me();
      }
   }
   _room_map = 0;
   _area_map = 0;
   setup_area_map();
}
void load_zone_map()
{
   string   map_path = query_map_file() + ".zones";
   int      index = 1;
   string   line;
   int      width;
   int      height;
   _zone_map = ({ });
   while (line = read_file(map_path, index++, 1)) {
      if (width < sizeof(line))
         width = sizeof(line);
      _zone_map += ({ line });
   }
   height = index - 1;
   if ((width != _width) || (height != _height))
      _zone_map = ({ });
}
void load_area_map()
{
   string   map_path = query_map_file() + ".map";
   int      index = 1;
   int      height;
   string   line;
   _area_map = ({ });
   while (line = read_file(map_path, index++, 1)) {
      if (sizeof(line)) {
         line = line[0..<2];
         if (_width < sizeof(line)) {
            _width = sizeof(line);
         }
         _area_map = ({ line }) + _area_map;
         height++;
      }
   }
   _height = height;
   if (!height) {
      printf("Unable to open %O\n", map_path);
   }
}
object create_virtual_object(string x_str, string y_str, string z_str)
{
   int x = to_int(x_str);
   int y = to_int(y_str);
   int z = to_int(z_str);
   if (!stringp(x_str) || !stringp(y_str) || !stringp(z_str)) {
      return 0;
   }
   return query_room(x, y, z);
}
string find_room_at_real_coord(int x, int y, int z) {
   class char_map_data room_map;
   class coord our;
   our = query_terrain_from_real_coord(x, y, z);
   if (!our) {
      return 0;
   }
   room_map = query_char_map(our->x, our->y);
   if (!room_map) {
      debug_printf("Unable to load room at %d %d (%d %d)\n", our->x, our->y, x, y);
      return 0;
   }
   if (room_map->type == AREA_OBSTACLE) {
      return 0;
   }
   return sprintf("%s:%d:%d:%d", base_name(this_object()), our->x, our->y, our->z);
}
int query_direction_distance(string dir) {
  switch (_direcs[dir][3]) {
   case X_DIFF :
      return _real_coords->xdiff;
   case Y_DIFF :
      return _real_coords->ydiff;
   case XY_DIFF :
      return _real_coords->xydiff;
   }
   return 0;
}
void dest_me() {
   class feature_data womble;
   string name;
   foreach (name, womble in _features) {
      if (womble->feature_ob) {
         womble->feature_ob->dest_me();
      }
   }
   destruct(this_object());
}