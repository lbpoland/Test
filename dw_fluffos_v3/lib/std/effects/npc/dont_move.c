#include <effect.h>
#include <route.h>
#include <wander.h>
#include "path.h"
void beginning( object player, int arg, int id ) {
   player->submit_ee(0, arg, EE_REMOVE);
}
int merge_effect( object player, int time1, int time2, int id ) {
   player->submit_ee( 0, time1 + time2 - player->expected_tt(),
          EE_REMOVE );
   return time1 + time2;
}
string query_classification() { return "npc.move.no"; }
string query_shadow_ob() { return SHADOWS + "dont_move"; }