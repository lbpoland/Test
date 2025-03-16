#include <effect.h>
#include "path.h"
#define LOG_FILE "EFFECTS"
private string standardize(mixed dest);
void call_move_to(object player, string dest)
{
  if (!player) {
#ifdef DEBUG
    log_file(LOG_FILE,
             sprintf("%O %s: player became 0 before call_move_to() called\n",
                     this_object(), ctime(time())));
#endif
    return;
  }
  if(!dest) {
#ifdef DEBUG
    log_file(LOG_FILE,
             sprintf("%O %s: dest became 0 before call_move_to() called\n",
                     this_object(), ctime(time())));
#endif
    return;
  }
  player->move_me_to(dest);
}
void remove_effect(object player, int id)
{
  if (player)
    player->remove_effect(id);
}
void beginning( object player, mixed arg, int id ) {
   mixed dest;
   if (pointerp(arg)) {
      if (sizeof(arg) > 3) {
         arg = arg[0..2];
      } else while (sizeof(arg) < 3) {
         arg += ({ 20 });
      }
   } else {
      arg = ({ arg, 0, 20 });
   }
   arg[0] = standardize(arg[0]);
   if (!dest) {
      while (!arg[0] && sizeof(arg) > 3) {
         arg = arg[3..];
         arg[0] = standardize(arg[0]);
      }
      if (!arg[0]) {
         call_out("remove_effect", 2, player, id);
         return ;
      }
   }
   if (objectp(arg[0])) {
      call_out("call_move_to", 2, player, file_name(environment(arg[0])));
   } else {
      call_out("call_move_to", 2, player, arg[0]);
   }
}
private string standardize(mixed dest) {
   if (objectp(dest)) {
      if (!living(dest)) {
         dest = file_name(dest);
      }
   } else if (stringp(dest)) {
      if (catch(dest->rabbit_well())) {
         dest = 0;
      } else {
         dest = file_name(find_object(dest));
      }
   }
   return dest;
}
mixed merge_effect( object player, mixed arg1, mixed arg2, int id ) {
   if (!pointerp(arg1)) {
      arg1 = ({ arg1, 0, 20 });
   }
   if (sizeof(arg1) > 0) {
      while (sizeof(arg1) < 3) {
         arg1 += ({ 20 });
      }
      arg1[0] = standardize(arg1[0]);
   }
   if (!pointerp(arg2)) {
      arg2 = ({ arg2, 0, 20 });
   }
   if (sizeof(arg2) > 0) {
      while (sizeof(arg2) < 3) {
         arg2 += ({ 20 });
      }
      arg2[0] = standardize(arg2[0]);
   }
   arg1 += arg2;
   while (!arg1[0] && sizeof(arg1) > 3) {
      arg1 = arg1[3..];
      arg1[0] = standardize(arg1[0]);
   }
   if (!arg1[0]) {
      call_out("remove_effect", 2, player, id);
      return ({ });
   }
   return arg1;
}
void effect_womble(object player, mixed *arr) {
  if(!player)
    return;
   player->add_effect(file_name(this_object()), arr);
}
void do_the_sell(object player) {
   object *obs;
   int i;
   obs = all_inventory(player);
   for (i = 0; i < sizeof(obs); i++) {
      if (!obs[i]->query_property("start equipment")) {
         call_out((: $1->do_command("sell "+file_name($2)) :),
                   1, player, obs[i]);
      }
   }
}
void end( object player, mixed room, int id ) {
   int ok;
   if (pointerp(room)) {
      if (sizeof(room) > 3) {
         call_out( "effect_womble", room[2], player, room[3..]);
      }
      if (!room[0]) {
         ok = 0;
      } else if (objectp(room[0])) {
         ok = (environment(room[0]) == environment(player));
      } else {
         ok = file_name(environment(player)) == room[0];
      }
      if (functionp(room[1])) {
         evaluate(room[1], player, room[0], ok, room[1]);
      }
      if (stringp(room[1])) {
         if (ok) {
            switch (room[1]) {
               case "sell" :
                  do_the_sell(player);
                  break;
               default :
                  player->do_command(room[1]);
                  break;
            }
         }
      }
      if (pointerp(room[1])) {
         call_other(room[1][0], room[1][1], player, room[0], ok, room[1]);
      }
   }
}
string query_classification() { return "npc.move"; }
string query_shadow_ob() { return SHADOWS + "goto_destination"; }