#include <room.h>
#include <login_handler.h>
#include <terrain_map.h>
inherit TERRAIN_MAP_FACTORY_BASE;
#define BLOCKING_FLAG 2
#define INSTALLED_FLAG 1
private nosave int     _x_coord = -1;
private nosave int     _y_coord = -1;
private nosave int     _z_coord = -1;
private nosave int     _flag = 0;
private nosave string  _extra_long = "";
private nosave object  _map_handler;
private nosave mapping _dist_features = ([ ]);
private nosave mapping _features = ([ ]);
private nosave string  _outside_types;
private nosave string  _random_desc = 0;
private nosave object  _terrain_chatter = 0;
private nosave string* _variable_exits;
private nosave mapping _default_exits;
private nosave string  _terrain_handler;
private nosave string  _terrain_char;
varargs int add_property(string var, mixed val, int tim);
string  query_feature_item_desc(string title);
string  query_handler_path();
varargs void terrain_chat( mixed *args, object chatobj );
int do_outside_chats();
void add_zone(string zone);
void add_extra_look(object ob);
int remove_item(string word);
varargs int add_item( mixed shorts, mixed desc, int no_plural );
int* query_co_ord();
int query_visibility();
string long(string str, int dark);
string query_terrain_handler();
class feature {
   mapping direcs;
   mixed items;
   int sentance;
   int index;
   int visible;
}
void create() {
   _variable_exits = ({ });
   _default_exits = ([ ]);
   this_object()->add_help_file("terrain_room");
   ::create();
}
string long_test(string str, int dark) {
   string ret;
   string map;
   string* map_lines;
   ret = long(str, dark);
   map = query_terrain_handler()->query_player_map_template(_x_coord,
             _y_coord, _z_coord, query_visibility(), 9);
   map_lines = map(explode(map, "\n"), (: $1 + "   " :));
   ret = "$COLUMN$12=" + implode(map_lines, "\n") + "$COLUMN$" +
         ret;
   return ret;
}
int hash(int mod) {
   mixed* my_coord;
   int x;
   int y;
   int z;
   int grid;
   int val;
   string str;
   my_coord = query_co_ord();
   if (!my_coord) {
      return 0;
   }
   grid = TERRAIN_MAP_GRID_SIZE / 10;
   x = (my_coord[0]) / grid;
   y = (my_coord[1]) / grid;
   z = (my_coord[2]) / grid;
   str = "" + x + ":" + y + ":" + z;
   val = crc32(str) % mod;
   if (val < 0) {
      return - val;
   }
   return val;
}
int hash_time(int mod, int period) {
   mixed* my_coord;
   int x;
   int y;
   int z;
   int grid;
   int val;
   string str;
   my_coord = query_co_ord();
   if (!my_coord) {
      return 0;
   }
   grid = TERRAIN_MAP_GRID_SIZE / 10;
   x = (my_coord[0]) / grid;
   y = (my_coord[1]) / grid;
   z = (my_coord[2]) / grid;
   str = x + ":" + y + ":" + z + ":" + (time() /period);
   val = crc32(str) % mod;
   if (val < 0) {
      return - val;
   }
   return val;
}
string query_terrain_handler() {
   return _terrain_handler;
}
void set_terrain_handler(string handler) {
   _terrain_handler = handler;
}
mixed *query_terrain_coords() { return ({ _x_coord, _y_coord, _z_coord }); }
void create_terrain_room()
{
   _x_coord = -1;
   _y_coord = -1;
   _z_coord = -1;
   add_property("terrain_map", 1);
   add_extra_look(this_object());
   if (do_outside_chats())
      terrain_chat(({ 60, 120, ({ "#do_a_feature_chat",
                             "#do_an_outside_chat" }) }) );
}
void terrain_setup()
{
}
void set_terrain_coords(int x, int y, int z)
{
   _x_coord = x;
   _y_coord = y;
   _z_coord = z;
}
object query_map_handler()
{
   return load_object(query_terrain_handler());
}
void reset_handler()
{
   if (query_map_handler())
      query_map_handler()->reset_handler();
}
void receive_message(string mess_class, string message, string title)
{
   class    feature feature;
   if (mess_class == "feature") {
      feature = _features[title];
      if (!feature) {
         return;
      }
   } else if (mess_class == "direction") {
   }
   tell_room(this_object(), message);
}
void do_a_feature_chat()
{
   string   *chats = ({ });
   string   feature_chat;
   string   title;
   class  feature feature;
   if ((_x_coord < 0) || (_y_coord < 0)) {
      return;
   }
   foreach(title, feature in _features) {
      if (feature_chat) {
         chats += ({ feature_chat });
      }
   }
   if (sizeof(chats)) {
      tell_room(this_object(), chats[random(sizeof(chats))] + "\n");
   }
}
void do_an_outside_chat()
{
   string chat = query_map_handler()->get_an_outside_chat(_outside_types);
   if (chat && strlen(chat)) {
      tell_room(this_object(), chat + "\n");
   }
}
int can_view_adjacent_desc(string char, string key_here, string path,
                           int z, string direc) {
   return char != key_here;
}
int can_view_feature(string name)
{
   return 1;
}
int can_view_feature_from(string name, string direc, int distance)
{
   return 1;
}
int can_exit_to(string type, string direc, string base_path)
{
   return 1;
}
int can_enter_from(string type, string direc, string base_path)
{
   return 1;
}
int can_move_between(string my_type, string direc,
                     string first_type, string second_type,
                     string new_base_path)
{
   return 1;
}
string query_enter_exit_direction(string key, string key_here,
                                  string direc, object room, string base_path) {
   return 0;
}
int do_outside_chats()
{
   return 1;
}
varargs void terrain_chat( mixed *args, object chatobj ) {
   if (!args)  {
      return;
   }
   if ( !pointerp( args[ 2 ] ) ) {
      write( "Error: second argument of room_chat args is not an array.\n" );
      return;
   }
  if ( _terrain_chatter ) {
    _terrain_chatter->setup_chatter( this_object(), args );
    return;
  }
  if (objectp(chatobj)) {
    _terrain_chatter = chatobj;
    log_file("CHATTER", "%s cloned set terrain chatter: %O\n",
             file_name(this_object()), chatobj);
  } else {
    _terrain_chatter = clone_object( CHATTER_OBJECT );
    log_file("CHATTER", "%s cloned terrain chatter: %O\n",
             file_name(this_object()), _terrain_chatter);
  }
  _terrain_chatter->setup_chatter( this_object(), args );
}
void add_random_desc(string desc)
{
   if (!_random_desc) {
      _random_desc = "";
   }
   _random_desc += desc + " ";
}
void terrain_add_zone(string zone)
{
   add_zone(zone);
   query_map_handler()->add_room_to_zone(this_object(), zone);
}
string query_dest_coordinate_string(int x, int y, int z,
                                    string direc, string key) {
   return ":" + x + ":" + y + ":" + z;
}
varargs mixed *query_to_same(string type, string to_direc, string from_direc, string path_to) {
   return 0;
}
varargs mixed *query_to_other(string type, string to_direc, string from_direc, string path_to) {
   return 0;
}
varargs mixed *query_from_other(string type, string to_direc, string from_direc, string path_from) {
   return 0;
}
mixed *get_to_same(string from, string to, string type, string path_to)
{
   mixed *result = query_to_same(type, to, from);
   if (arrayp(result)) {
      return map(result, (: stringp($1)?replace($1, ({ "$T", $2, "$F", $3 }) ):$1 :), to, from);
   }
   return 0;
}
mixed *get_to_other(string from, string to, string type, string path_to)
{
   mixed *result = query_to_other(type, to, from);
   if (arrayp(result)) {
      return map(result, (: stringp($1)?replace($1, ({ "$T", $2, "$F", $3 }) ):$1 :), to, from);
   }
   return 0;
}
mixed *get_from_other(string from, string to, string type, string path_from)
{
   mixed *result = query_from_other(type, to, from);
   if (arrayp(result)) {
      return map(result, (: stringp($1)?replace($1, ({ "$T", $2, "$F", $3 }) ):$1 :), to, from);
   }
   return 0;
}
void set_extra_long(string extra)
{
   _extra_long = extra;
}
void set_outside_types(string types)
{
   _outside_types = types;
}
string query_my_real_file_name() {
   return __FILE__;
}
string extra_look() {
   string   result = _extra_long;
   string   title;
   string*   tmp;
   class  feature feature;
   int new_line;
   string* descs;
   int visibility;
   new_line = query_map_handler()->query_newline_mode();
   descs = ({ });
   visibility = query_visibility();
   foreach (title, feature in _features) {
      tmp = query_map_handler()->query_feature_desc(title,
                                          feature->direcs, visibility);
      if (sizeof(tmp)) {
         feature->visible = 1;
         descs += tmp;
      }
   }
   foreach (title, feature in _dist_features) {
      tmp = query_map_handler()->query_distant_feature_desc(title,
                                        feature, visibility);
      if (sizeof(tmp)) {
         descs += tmp;
      }
   }
   if (sizeof(descs)) {
      result += "  " + capitalize(query_multiple_short(descs)) + ".";
   }
   if (_random_desc) {
      result = result + _random_desc;
   }
   if (new_line) {
      return result;
   } else {
      return result + "\n";
   }
}
void add_feature(string title, mapping bits, mixed items, int sentance)
{
   _features[title] = new(class feature,
                          items : items, direcs : bits);
   if (items) {
      add_item(items, (: query_feature_item_desc($(title)) :));
   }
}
void add_distant_feature(string title, mapping bits) {
   _dist_features[title] = bits;
}
void remove_feature(string title)
{
   class feature  feature = _features[title];
   mixed    items;
   if (!feature) {
      return;
   }
   map_delete(_features, title);
   items = feature->items;
   if (stringp(items)) {
      remove_item(items);
   } else {
      remove_item(items[0]);
   }
}
string query_feature_item_desc(string title)
{
   if (_features[title]->visible) {
      return query_map_handler()->query_feature_item_desc(title);
   }
   return 0;
}
mapping query_features() { return _features; }
int query_installed() { return _flag & INSTALLED_FLAG; }
void set_installed() { _flag |= INSTALLED_FLAG; }
void set_terrain_map_block(int blocking) {
   if (blocking) {
      _flag |= BLOCKING_FLAG;
   } else {
      _flag &= ~BLOCKING_FLAG;
   }
}
int query_terrain_map_block() {
   return _flag & BLOCKING_FLAG;
}
void set_terrain_map_character(string terr) {
   _terrain_char = terr;
}
string query_terrain_map_character() {
   return _terrain_char;
}
string query_cloning_info()
{
  return file_name(this_object());
}
object create_virtual_object(string x_str, string y_str)
{
   int x = to_int(x_str);
   int y = to_int(y_str);
   return query_map_handler()->load_room_at(x, y);
}
void add_variable_exit(string exit) {
   _variable_exits += ({ exit });
}
void add_default_exit(string exit, string location) {
   _default_exits[exit] = location;
}
mapping query_default_exits() {
   return _default_exits;
}
string query_terrain_map_walk_exit() {
   return TERRAIN_MAP_WALK_EXIT;
}
string query_terrain_map_journey_exit() {
   return TERRAIN_MAP_JOURNEY_EXIT;
}
string query_room_path(int x, int y, int z) {
   return sprintf("%s:%d:%d:%d", query_terrain_handler(), x, y, z);
}
string query_direction_distance_str(int num, string dir) {
   int dist;
   string dist_mess;
   dist = query_map_handler()->query_direction_distance(dir);
   switch (dist) {
   case 0..2 :
      if (dist > 1) {
         dist_mess = query_num(dist) + " foot section";
      } else {
         dist_mess = "foot";
      }
      break;
   case 3..TERRAIN_MAP_ONE_MILE / 2 - 1 :
      dist /= 3;
      if (dist > 1) {
         dist_mess = query_num(dist) + " yard section";
      } else {
         dist_mess = "yard";
      }
      break;
   case TERRAIN_MAP_ONE_MILE / 2..TERRAIN_MAP_ONE_MILE - 1 :
      dist /= TERRAIN_MAP_ONE_MILE / 2;
      if (dist > 1) {
         dist_mess = query_num(dist) + " miles section";
      } else {
         dist_mess = "mile";
      }
      break;
   default:
      dist /= TERRAIN_MAP_ONE_MILE;
      if (dist > 1) {
         dist_mess = query_num(dist) + " miles section";
      } else {
         dist_mess = "mile";
      }
      break;
   }
   switch(num) {
   case 0:
      return dist_mess + " " + dir;
   case 1:
      return query_num(num) + " " + dist_mess + " " +dir;
   default:
      return query_num(num) + " " + dist_mess + "s " + dir;
   }
}
mixed* query_dest_other(string exit, mixed* data) {
   mixed* bing;
   string cur;
   string dir;
   int num;
   string* bits;
   int dist;
   if(!stringp(exit) || !_default_exits) {
     return data;
   }
   if (_default_exits[exit]) {
      if (this_player() &&
          this_player()->query_property(TERRAIN_MAP_LONG_JUMP_PROPERTY) &&
          member_array(query_terrain_map_journey_exit() + exit, _variable_exits) != -1) {
         exit = query_terrain_map_journey_exit() + exit;
      } else {
         data[ROOM_DEST] = _default_exits[exit];
         return data;
      }
   }
   if (member_array(exit, _variable_exits) != -1) {
      bing = query_map_handler()->find_next_room_from(_x_coord, _y_coord, _z_coord, exit[strlen(query_terrain_map_journey_exit())..]);
      if (bing) {
         if (data[ROOM_DEST] != bing[0]) {
            data[ROOM_DEST] = bing[0];
            bits = ({ });
            foreach (dir in bing[1..]) {
               if (dir == cur) {
                  num++;
               } else {
                  if (cur) {
                     bits += ({ query_direction_distance_str(num, cur) });
                  }
                  cur = dir;
                  num = 1;
               }
            }
            dist = query_map_handler()->query_direction_distance(dir);
            bits += ({ query_direction_distance_str(num, dir) });
            if (sizeof(bits) > 1) {
               data[ROOM_MESS] = "You arrive after having journeyed " +
                                 implode(bits[0..<2], ", ") +
                                 " and " + bits[<1] +
                                 ".\n";
            } else {
               data[ROOM_MESS] = "You arrive after having journeyed " +
                                 bits[0] +
                                 ".\n";
            }
            if (!arrayp(data[ROOM_ENTER]) ||
                !data[ROOM_ENTER][0]) {
               data[ROOM_ENTER] = "$N journey$s in from " +
                        ROOM_HANDLER->query_opposite_direction(bing[<1]) + ".\n";
            }
            if (!data[ROOM_EXIT]) {
               data[ROOM_EXIT] = "$N journey$s to the " + bing[1] + ".\n";
            }
         }
      }
   }
   return data;
}
mixed* query_dest_dir(mixed* data) {
   int i;
   int jump;
   mixed* bits;
   if (this_player() &&
       this_player()->query_property(TERRAIN_MAP_LONG_JUMP_PROPERTY)) {
      jump = 1;
   }
   if (sizeof(_variable_exits)) {
      for (i = 0; i < sizeof(data); i += 2) {
         if (_default_exits[data[i]]) {
            if (jump) {
               bits = query_map_handler()->find_next_room_from(_x_coord, _y_coord, _z_coord, data[i]);
               if (bits) {
                  data[i+1] = bits[0];
               }
            } else {
               data[i+1] = _default_exits[data[i]];
            }
         } else if (member_array(data[i], _variable_exits) != -1) {
            bits = query_map_handler()->find_next_room_from(_x_coord, _y_coord, _z_coord, data[i][strlen(query_terrain_map_journey_exit())..]);
            if (bits) {
               data[i+1] = bits[0];
            }
         }
      }
   }
   return data;
}
int do_map() {
   string map;
   map = query_map_handler()->query_debug_map(_x_coord, _y_coord, 13, _x_coord, _y_coord);
   write(map);
   add_succeeded_mess("");
   return 1;
}
int do_map_terrain() {
   string map;
   map = query_map_handler()->query_debug_map(20, 20, 40, _x_coord, _y_coord);
   write(map);
   add_succeeded_mess("");
   return 1;
}
void init()
{
   tell_creator(this_player(), "Coords: (%d, %d, %d)\n", _x_coord, _y_coord, _z_coord);
   if (this_player()->query_creator()) {
      add_command("cremap", "", (: do_map :));
      add_command("cremap", "all", (: do_map_terrain :));
   }
}
mixed stats() {
   return ::stats() +
          ({ ({ "file", query_my_real_file_name() }),
             ({ "blocking", query_terrain_map_block() }) });
}
void dest_me() {
  if(_terrain_chatter) {
    log_file("CHATTER", "%s dested terrain chatter: %O\n",
             file_name(this_object()), _terrain_chatter);
    _terrain_chatter->dest_me();
  }
}