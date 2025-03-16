#include <money.h>
#include <cmds/offer.h>
inherit "/cmds/base";
int withdraw_offer(object *sell_to) {
   object *removed;
   object ob;
   removed = ({ });
   foreach (ob in sell_to) {
      if (ob->query_respond_command("sell", this_player())) {
         ob->remove_respond_command("sell", this_player());
         removed += ({ ob });
      }
   }
   if (sizeof(removed)) {
      add_succeeded_mess("$N withdraw$s $p offer of sale to $I.\n", removed);
      return 1;
   }
   add_failed_mess("You cannot withdraw your offer of sale to $I since "
                   "you have not offered to sell them anything in the "
                   "first place.\n", sell_to);
   return 0;
}
mixed *query_patterns() {
   return ({ "offer {from|to} <indirect:living>",
             (: withdraw_offer($1) :) });
}