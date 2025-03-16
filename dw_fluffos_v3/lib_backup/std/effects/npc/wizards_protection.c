#include <effect.h>
#define SHADOWS "/std/shadows/npc/"
#define SHADOW_OB  "uu_staff_protection"
string query_classification(){return "npc.protection.wizards"; }
void beginning(object player, mixed arg){
   player->submit_ee( 0, -1, EE_REMOVE );
}
string query_shadow_ob() {
   return (SHADOWS SHADOW_OB);
}
mixed merge_effect(object player, mixed old_arg, mixed new_arg){
   return new_arg;
}
int query_indefinite() { return 1; }