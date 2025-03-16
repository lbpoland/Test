#include <terrain_map.h>
private int _room_jump_size;
private int _follow_road;
private int _default_height;
private int _min_height;
private string _adjacent_desc;
private mapping _height_info;
private mapping _adjacent_items;
void create() {
   _adjacent_items = ([ ]);
}
void set_room_jump_size(int jump) {
   _room_jump_size = jump;
}
int query_room_jump_size() {
   return _room_jump_size;
}
void set_follow_road(int follow) {
  _follow_road = follow;
}
int query_follow_road() {
   return _follow_road;
}
void set_default_height(int height) {
   _default_height = height;
}
void set_adjacent_description(string desc) {
   _adjacent_desc = desc;
}
string query_adjacent_description() {
   return _adjacent_desc;
}
int query_default_height() {
   return _default_height;
}
void set_minimum_height(int height) {
   _min_height = height;
}
int query_minimum_height() {
   return _min_height;
}
void set_height_rooms(mapping map) {
   _height_info = map;
}
string find_base_terrain_room(int x, int y, int z, string base_name, int map_room, string ref base) {
   if (_height_info && _height_info[z]) {
      return _height_info[z];
   }
   if (z > _default_height) {
      if (map_room == TERRAIN_MAP_ROOM_CLIMB) {
         return 0;
      }
      if (map_room == TERRAIN_MAP_ROOM_EXACT) {
         return TERRAIN_MAP_DEFAULT_AIR_ROOM;
      }
      if (!_height_info) {
         return base_name;
      }
      return _height_info[_default_height];
   }
   if (!_height_info) {
      if (z == _default_height) {
         return base_name;
      }
      return 0;
   }
   if (_min_height > z) {
      return 0;
   }
   if (z == _default_height) {
      return base_name;
   }
   return _height_info["default"];
}
void add_adjacent_item(string name, string desc) {
   _adjacent_items[name] = desc;
}
mapping query_adjacent_items() {
   return _adjacent_items;
}
mixed stats() {
   return ({
  ({ "room jump", _room_jump_size }),
  ({ "follow road", _follow_road }),
  ({ "adjacent desc", _adjacent_desc }) });
}