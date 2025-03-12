inherit "/cmds/position_base";
#include <position.h>
void create() {
   ::create();
   if(this_player()->query_position() == "lying")
     setup_position("sit", "up", SITTING);
   else
     setup_position("sit", "down", SITTING);
}