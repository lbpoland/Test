#include <terrain_map.h>
inherit TERRAIN_MAP_OUTSIDE_BASE;
string query_handler_path() { return __DIR__ + "field_handler"; }
void setup()
{
  set_short("grassy field");
  set_long("This is a large grassy field.\n");
  add_item("field", "Large and grassy.");
  add_item("grass", "It's green, which should come as no surprise at all.");
}