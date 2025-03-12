#include <effect.h>
#include <route.h>
#include <wander.h>
#include "path.h"
void beginning( object player, string dest, int id ) {
}
int merge_effect( object player, int time1, int time2, int id ) {
   return time1;
}
string query_classification() { return "npc.eat.edible"; }
string query_shadow_ob() { return SHADOWS + "eat_edible"; }