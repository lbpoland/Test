#include <effect.h>
#include <route.h>
#include <wander.h>
#include "path.h"
void beginning( object player, string dest, int id ) {
   player->do_command("lose everyone");
}
int merge_effect( object player, int time1, int time2, int id ) {
   return time1;
}
string query_classification() { return "npc.follow.no"; }
string query_shadow_ob() { return SHADOWS + "no_follow"; }