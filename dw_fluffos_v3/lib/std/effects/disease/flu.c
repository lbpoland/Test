#include <effect.h>
#include "path.h"
int query_secs_between_hb() { return 1; }
string query_classification() { return "disease.infection.general.flu"; }
int beginning(object player, mixed arg) {
   tell_object(player, "You shiver.\n");
   return arg;
}
int effect_heart_beat(object player, int hbnum, mixed arg, int id){
   if (hbnum == arg) return REMOVE_THIS_EFFECT;
   return arg;
}
void end(object player) {
   tell_object(player, "You feel altogether healthy again.\n");
}
string query_shadow_ob(){ return SHADOWS+"flu_shadow"; }