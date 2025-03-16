#include <terrain_map.h>
inherit TERRAIN_MAP_SIMPLE_FEATURE_BASE;
inherit "/std/basic/setup";
private string* _items;
private string* _night_descs;
private string* _day_descs;
void create() {
   _items = ({ });
   _night_descs = ({ });
   _day_descs = ({ });
   do_setup();
   do_reset();
}
void add_item(string item, string day, string night) {
   _items += ({ item });
   _night_descs += ({ night });
   _day_descs += ({ day });
}
string* query_items() {
   return _items;
}
string* query_day_items() {
   return _day_descs;
}
string* query_night_items() {
   return _night_descs;
}