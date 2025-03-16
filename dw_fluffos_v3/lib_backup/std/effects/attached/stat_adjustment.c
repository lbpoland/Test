#include "path.h"
#include <effect.h>
class stat_class {
   mapping current_adjustments;
   object* obs;
   mapping* adjs;
   object me;
}
private string* _stats;
void create() {
   _stats = ({ "str", "dex", "wis", "int", "con" });
}
string query_classification() { return "mudlib.clothing.stat"; }
void update_adjustments(object player, class stat_class arg) {
   mapping stats;
   mapping bing;
   string stat;
   int i;
   int num;
   if (sizeof(arg) == 4 && arg->me != player) {
      arg->me = player;
      arg->current_adjustments = ([ ]);
   }
if (player == find_player("presto"))  printf("UPDATE: %O\n", arg);
if (player == find_player("presto"))  printf("UPDATE: %O\n", arg->obs);
   for (i = 0; i < sizeof(arg->obs); i++) {
if (player == find_player("presto"))  {
printf("%O, %d\n", arg->obs, i);
printf( "UPDATE: checkpoint 2: %O\n", arg->obs[i]);
}
      if (!arg->obs[i]) {
         arg->obs = arg->obs[0.. i -1] + arg->obs[i+1..];
         arg->adjs = arg->adjs[0.. i -1] + arg->adjs[i+1..];
      }
   }
if (player == find_player("presto"))
tell_creator("presto", "checkpoint 3\n");
   stats = ([ ]);
   foreach (stat in _stats) {
      num = 0;
      for (i = 0; i < sizeof(arg->adjs); i++) {
         bing = arg->adjs[i];
         if (bing[stat] > 0) {
            if (i > 0) {
               num += bing[stat] / (i + 1);
            } else {
               num += bing[stat];
            }
         } else if (bing[stat] < 0) {
            if (i > 1) {
               num += bing[stat] * i;
            } else {
               num += bing[stat];
            }
         } else if (i > 0) {
            num -= i;
         }
      }
      stats[stat] = num;
   }
if (player == find_player("presto"))
tell_creator("presto", "UPDATE: checkpoint 1\n");
   foreach (stat in _stats) {
      if (stats[stat] != arg->current_adjustments[stat]) {
         call_other(player,
                    "adjust_bonus_" + stat,
                    stats[stat] - arg->current_adjustments[stat]);
         arg->current_adjustments[stat] = stats[stat];
      }
   }
}
class stat_class beginning(object player, mixed arg, int id) {
   class stat_class bing;
   bing = new(class stat_class);
   bing->current_adjustments = ([ ]);
   bing->obs = ({ arg[0] });
   bing->adjs = ({ arg[1] });
   bing->me = player;
if (player == find_player("presto"))  printf("BEFORE: %O\n", bing);
   update_adjustments(player, bing);
if (player == find_player("presto"))
tell_creator("presto", "BEGINNING: bing == %O, player == %s\n", bing, player->short());
   return bing;
}
int query_indefinite() { return 1; }
class stat_class merge_effect( object player, class stat_class old_arg, mixed new_arg ) {
   int i;
   if (pointerp(old_arg)) {
      player->submit_ee(0, 0, EE_REMOVE);
      return old_arg;
   }
   i = member_array(new_arg[0], old_arg->obs);
   if (i != -1) {
      old_arg->adjs[i] = new_arg[1];
   } else {
      old_arg->obs += ({ new_arg[0] });
      old_arg->adjs += ({ new_arg[1] });
   }
   update_adjustments(player, old_arg);
   return old_arg;
}
void restart( object player, class stat_class edible ) {
   update_adjustments(player, edible);
}
void quiting( object player, class stat_class womble ) {
   womble->obs = ({ });
   womble->adjs = ({ });
   update_adjustments(player, womble);
}
void end( object player, class stat_class bing ) {
   bing->obs = ({ });
   bing->adjs = ({ });
   update_adjustments(player, bing);
}
void remove_stat_adjustment_ob(object player, object ob) {
   class stat_class fluff;
   int *ids;
   int i;
   ids = player->effects_matching(query_classification());
   if (sizeof(ids)) {
      fluff = player->arg_of(ids[0]);
      for (i = 0; i < sizeof(fluff->obs); i++) {
         if (fluff->obs[i] == ob) {
            fluff->adjs = fluff->adjs[0..i-1] + fluff->adjs[i+1..];
            fluff->obs = fluff->obs[0..i-1] + fluff->obs[i+1..];
         }
      }
      if (!sizeof(fluff->obs)) {
         player->delete_effect(ids[0]);
      } else {
         update_adjustments(player, fluff);
         player->set_arg_of(ids[0], fluff);
      }
   }
}