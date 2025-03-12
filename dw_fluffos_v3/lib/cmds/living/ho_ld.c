inherit "/cmds/base";
#define TP this_player()
int cmd(object * obs,
        string str)
{
   int num_limbs;
   int avail;
   int old_avail;
   int reqd;
   int i;
   int pos;
   int success;
   int *used;
   int *already_used;
   int *limbs_used;
   object ob;
   object weapon;
   object *using;
   object *fails;
   object *unfails;
   object *holds;
   object *unholds;
   object *already;
   object *no_change;
   string *limbs;
   string *hhands;
   string *uhands;
   limbs = TP->query_limbs();
   num_limbs = sizeof(limbs);
   avail = TP->query_free_limbs();
   no_change = ({ });
   already = filter(obs, (: $1->query_holder() :));
   if (sizeof(already) > 0) {
      using = this_player()->query_holding();
      foreach (ob in already)  {
         limbs_used = find_member(ob, using);
         if (str)  {
            if (sizeof(limbs_used) == 1  &&
                member_array(str, limbs) == limbs_used[0])
            {
               no_change += ({ ob });
            }
            else already -= ({ ob });
         }
         else if (sizeof(limbs_used) != ob->query_no_limbs())
            already -= ({ ob });
      }
      if (sizeof(obs) == sizeof(no_change))  {
         add_failed_mess("You are already holding " +
                         query_multiple_short(obs) +
                         " in your " + str + ".\n");
         return -1;
      }
      else if (sizeof(obs) == sizeof(already)) {
         return notify_fail("You are already holding " +
                            query_multiple_short(obs) + ".\n");
      } else {
         obs -= already;
         if (sizeof(already) > 0)
            write(sprintf("You are already holding %s, you instead try to "
                          "hold %s.\n", query_multiple_short(already),
                          query_multiple_short(obs)));
         already_used = map(already, (: $1->query_my_limb() :));
      }
   } else {
      already_used = ({ });
   }
   fails = holds = unholds = hhands = uhands = unfails = ({ });
   if (str && obs[0]) {
      pos = member_array(str, limbs);
      if (pos == -1) {
         if (!sizeof(limbs)) {
            return
               notify_fail("You seem to have a singular lack of limbs.\n");
         }
         return notify_fail("Incorrect limb type, must be one of " +
                            query_multiple_short(limbs) + ".\n");
      }
      using = TP->query_holding();
      if (sizeof(unfails) == 0  &&  using[pos]) {
         used = TP->set_unhold(using[pos]);
         if (sizeof(used) == 0) {
            unfails += ({ using[pos] });
            uhands += ({ limbs[pos] });
         } else {
            for (i = 0; i < sizeof(used) && i < sizeof(limbs); i++) {
               uhands += ({ limbs[used[i]] });
            }
            unholds += ({ using[pos] });
         }
      }
      if ((i = member_array(obs[0], using - unholds)) != -1)  {
         used = TP->set_unhold(obs[0]);
         if (sizeof(used) == 0) {
            unfails += ({ obs[0] });
            uhands += ({ limbs[i] });
         } else {
            for (i = 0; i < sizeof(used) && i < sizeof(limbs); i++) {
               uhands += ({ limbs[used[i]] });
            }
            unholds += ({ obs[0] });
         }
      }
      if (sizeof(unfails) == 0) {
         used = TP->set_hold(obs[0], pos, 1);
         if (sizeof(used) == 0) {
            fails += ({ obs[0] });
         } else {
            for (i = 0; i < sizeof(used) && i < sizeof(limbs); i++) {
               hhands += ({ limbs[used[i]] });
            }
            holds += ({ obs[0] });
            success = 1;
         }
      }
   } else {
      foreach(ob in obs) {
         reqd += ob->query_no_limbs();
      }
      if (reqd > num_limbs) {
         add_failed_mess("You do not have enough limbs to hold $I.\n", obs);
         return 0;
      }
      old_avail = -1;
      while ((avail < reqd) && (avail < num_limbs)) {
         if ((reqd > num_limbs - sizeof(unfails)) || (old_avail == avail)) {
            if (sizeof(unfails)) {
               add_failed_mess
                  ("You do not have enough limbs to hold $I, since " +
                   query_multiple_short(unfails) + " failed " "to unhold.\n",
                   obs);
            } else {
               add_failed_mess
                  ("Not able to free up enough limbs to hold $I.\n", obs);
            }
            return 0;
         }
         old_avail = avail;
         using = TP->query_holding();
         for (i = 0; i < sizeof(using); i++) {
            weapon = using[i];
            if (weapon && member_array(i, already_used) == -1) {
               used = TP->set_unhold(weapon);
               if (sizeof(used)) {
                  for (i = 0; i < sizeof(used) && used[i] < sizeof(limbs);
                       i++) {
                     uhands += ({ limbs[used[i]] });
                  }
                  unholds += ({ weapon });
                  avail = TP->query_free_limbs();
                  break;
               } else {
                  if (member_array(weapon, unfails) == -1) {
                     unfails += ({ weapon });
                  }
                  uhands += ({ limbs[i] });
               }
            }
         }
      }
      if (!sizeof(unfails)) {
         foreach(ob in obs) {
            using = TP->query_holding();
            pos = 0;
            if (!ob->query_no_limbs() || avail < ob->query_no_limbs()) {
               fails += ({ ob });
               break;
            }
            while ((using[pos]) && (pos < num_limbs)) {
               pos++;
            }
            used = TP->set_hold(ob, pos, ob->query_no_limbs());
            if (used == ({ })) {
               fails += ({ ob });
            } else {
               for (i = 0; i < sizeof(used) && i < sizeof(limbs); i++) {
                  hhands += ({ limbs[used[i]] });
               }
               holds += ({ ob });
               success = 1;
               avail = TP->query_free_limbs();
            }
         }
      }
   }
   if (sizeof(unfails)) {
      tell_object(TP,
                  "You fail to put down " + query_multiple_short(unfails) +
                  " from your " + query_multiple_short(uhands) + ".\n");
      say(TP->one_short() + " fails to put down " +
          query_multiple_short(unholds) + " from " + TP->query_possessive() +
          " " + query_multiple_short(uhands) + ".\n");
   }
   if (sizeof(unholds)) {
      tell_object(TP, "You put down " + query_multiple_short(unholds) +
                  " from your " + query_multiple_short(uhands) + ".\n");
      say(TP->one_short() + " puts down " + query_multiple_short(unholds) +
          " from " + TP->query_possessive() + " " +
          query_multiple_short(uhands) + ".\n");
   }
   if (sizeof(holds)) {
      tell_object(TP,
                  "You hold " + query_multiple_short(holds) + " in your " +
                  query_multiple_short(hhands) + ".\n");
      say(TP->one_short() + " holds " + query_multiple_short(holds) + " in " +
          TP->query_possessive() + " " + query_multiple_short(hhands) +
          ".\n");
   }
   if (!success && sizeof(fails)) {
      tell_object(TP,
                  "You fail to hold " + query_multiple_short(fails) + ".\n");
      say(TP->one_short() + " fails to hold " + query_multiple_short(fails) +
          ".\n");
   }
   return 1;
}
mixed *query_patterns()
{
   return ({ "<indirect:object:me>", (: cmd($1, 0) :),
             "<indirect:object:me> in [my] {" +
             implode(this_player()->query_limbs(), "|") + "}",
             (: cmd($1, implode($4[1..], " ")) :) });
}