#include "path.h"
string query_shadow_ob() { return SHADOWS + "controlled_monster"; }
void beginning( object player, string dest, int id ) {
}
int merge_effect( object player, int time1, int time2, int id ) {
   return time2;
}
string query_classification() { return "npc.controlled_monster"; }