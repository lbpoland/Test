inherit "/cmds/position_base";
#include <position.h>
void create() {
   ::create();
   setup_position("crouch", "down", CROUCHING);
}