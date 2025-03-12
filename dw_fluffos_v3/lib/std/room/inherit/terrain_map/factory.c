#include <terrain_map.h>
inherit TERRAIN_MAP_FACTORY_BASE;
void create() {
   ::create();
   this_object()->setup();
}