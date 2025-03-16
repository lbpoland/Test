inherit "/std/room/furniture/commercial";
#include <room.h>
#define SIZE_OF_FURNITURE 5
#define TAG "dividor"
#define TEMPLATE_DIVIDOR_ROOM "/mudlib/data/dividor_template.c"
private int _size;
private string _exit_direction;
private string _our_room;
int query_furniture_size() {
   return _size + SIZE_OF_FURNITURE;
}
int query_commercial_id() {
   if (!::query_commercial_id()) {
      setup_new_commercial_id();
   }
   return ::query_commercial_id();
}
string query_exit_direction() {
   return _exit_direction;
}
string query_exit_destination() {
   return _our_room;
}
int create_room() {
   string path;
   string *bits;
   string room_path;
   string stuff;
   path = environment()->query_save_dir();
   path += "/division" + query_commercial_id();
   if (file_size(path) == -2) {
      mkdir(path);
   }
   bits = explode(base_name(environment()), "/");
   room_path = implode(bits[0..<2], "/");
   room_path += "/" + bits[<1] + "_dividor";
   if (file_size(room_path) == -2) {
      mkdir(room_path);
   }
   room_path += "/" + query_commercial_id();
   if (file_size(room_path + ".c") > 0) {
      return 0;
   }
   _our_room = room_path;
   stuff = "inherit \"/std/room/furniture/dividor_room\";\n\n"
           "void setup() {\n"
           "   set_base_desc(\"" + environment()->query_base_desc() + "\");\n"
           "   set_main_room(\"" + base_name(environment()) + "\");\n"
           "   set_save_dir(\"" + path + "\");\n"
           "   set_theft_handler(\"" + environment()->query_theft_handler() + "\");\n"
           "   add_exit(\"" + ROOM_HANDLER->query_opposite_direction(query_exit_direction()) + "\", \"" + base_name(environment() + "\", \"door\");\n"
           "   set_property_size(" + _size + ");\n"
           "   add_property(\"place\", \"" + environment()->query_property("place") + "\");\n"
           "}";
   write_file(room_path + ".c", stuff, 1);
   return 1;
}
void add_exit_to_room() {
   environment()->add_exit(query_exit_direction(), query_exit_destination(), "door");
}
mapping query_dynamic_auto_load() {
   mapping map;
   map = ::query_dynamic_auto_load();
   add_auto_load_value(map, TAG, "exit", _exit_direction);
   add_auto_load_value(map, TAG, "room", _our_room);
   add_auto_load_value(map, TAG, "size", _size);
   return map;
}
void init_dynamic_arg(mapping map) {
   _exit_direction = query_auto_load_value(map, TAG, "exit");
   _our_room = query_auto_load_value(map, TAG, "room");
   _size = query_auto_load_value(map, TAG, "size");
   ::init_dynamic_arg(map);
}