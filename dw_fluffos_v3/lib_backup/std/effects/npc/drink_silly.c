#include <effect.h>
#include <pub.h>
#include <shops/pub_shop.h>
#include "path.h"
mixed normalise(mixed arg, object player) {
   if (stringp(arg)) {
      arg = ({ arg, player });
   } else if (functionp(arg)) {
      arg = ({ arg, player });
   } else if (!pointerp(arg)) {
      arg = ({ });
   }
   return arg;
}
void beginning( object player, mixed arg, int id ) {
   player->submit_ee("buy_something", 5, EE_CONTINUOUS);
   player->do_command("stand at bar");
   return normalise(arg, player);
}
int merge_effect( object player, int time1, int time2, int id ) {
   return normalise(time1, player) + normalise(time2, player);
}
void end(object player, mixed arg, int id) {
   int i;
   for (i = 0; i < sizeof(arg); i += 2) {
      if (functionp(arg[i])) {
         evaluate(arg[i]);
      } else {
         call_other(arg[i], arg[i+1]);
      }
   }
}
string query_classification() { return "npc.drink"; }
void buy_something(object player, mixed arg, int id) {
   mapping items;
   mixed *stuff;
   string *rabbit;
   int i;
   int value;
   mixed ret;
   string place;
   string name;
   class menu_item menu;
   items = environment(player)->query_menu_items();
   rabbit = ({ });
   if (mapp(items)) {
      stuff = keys(items);
      place = environment(player)->query_property( "place" );
      if ( !place || ( place == "" ) ) {
         place = "default";
      }
      value = (int)player->query_value_in( place );
      if ( place != "default" ) {
         value += (int)player->query_value_in( "default" );
      }
      if (environment(player)->query_pub()) {
         foreach (name, menu in items) {
            if (menu->intox > 0 &&
                menu->cost < value) {
               rabbit += ({ name });
            }
         }
      } else {
         foreach (name, stuff in items) {
            if (stuff[DR_INTOX] > 0 &&
                stuff[DR_COST] < value) {
               rabbit += ({ name });
            }
         }
      }
   }
   if (!sizeof(rabbit)) {
      player->delete_effect(player->sid_to_enum(id));
   } else {
      do {
         i = random(sizeof(rabbit));
         ret = player->do_command("buy "+rabbit[i]);
         rabbit = rabbit[0..i-1] + rabbit[i+1..];
      } while (ret <= 0 && sizeof(rabbit));
      if (ret <= 0) {
         player->delete_effect(player->sid_to_enum(id));
      }
   }
}