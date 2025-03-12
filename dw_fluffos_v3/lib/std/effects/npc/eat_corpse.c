#include <effect.h>
#include "path.h"
void beginning( object player, string dest, int id ) {
}
int merge_effect( object player, int time1, int time2, int id ) {
   return time1;
}
string query_classification() { return "npc.eat.corpse"; }
string query_shadow_ob() { return SHADOWS + "eat_corpse"; }
int query_indefinate() { return 1; }