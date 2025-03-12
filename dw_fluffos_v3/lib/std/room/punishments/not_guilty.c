#include <nomic_system.h>
inherit "/std/room/inherit/punishment_inherit";
void setup() {
   set_short("not guilty");
   set_description_file(NOMIC_PUNISHMENT_DOCS_DIR + "not_guilty");
}