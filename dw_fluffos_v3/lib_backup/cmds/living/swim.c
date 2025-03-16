inherit "/cmds/position_base";
#include <position.h>
void create() {
   ::create();
   setup_position("swim", "around", SWIMMING);
}