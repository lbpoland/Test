#include <effect.h>
inherit "/std/effect_shadow";
#define CLASS "npc.death.me"
int second_life() {
   mixed *bit;
   int ret;
   bit = arg();
   if (functionp(bit)) {
      ret = evaluate(bit, player);
   } else if (pointerp(bit)) {
      ret = call_other(bit[0], bit[1], player);
   }
   if (!pointerp(bit) || sizeof(bit) < 3 || !bit[2]) {
      ret = player->second_life();
   }
   player->submit_ee2( player->effects_matching(CLASS)[0], 0, 0, EE_REMOVE );
   return ret;
}