#include <clothing.h>
#include <tasks.h>
#define SKILL "covert.manipulation.sleight-of-hand"
#ifdef DEBUG
#define TELL_ME "presto"
#endif
inherit "cmds/base";
int cmd(object *things)  {
   object  *removed = ({ });
   object  *blocking = ({ });
   object  *blocked;
   object  *total_blocking = ({ });
   object  *succeeded;
   object  *failed;
   object  *failed_rewear;
   object   ob;
   object   blocker;
   mapping  is_blocking = ([ ]);
   mapping  hide_invis;
   string   tmp1;
   string   tmp2;
   int      last_blocking;
   int      limit;
   int      i;
   int      hiding;
   int      sneaking;
   int      difficulty;
   int      light;
   int      my_light;
   succeeded = this_player()->query_wearing();
   failed = filter(things, (: member_array($1, $(succeeded)) == -1 :));
   things -= failed;
   if (sizeof(things) == 0)  {
      write("You are not wearing " + query_multiple_short(failed, "the") +
            ".\n");
      return 1;
   }
   succeeded = things;
   for (i = 0; i < sizeof(succeeded); i++)  {
      ob = succeeded[i];
      blocking = CLOTHING_HANDLER->query_items_blocking(ob, this_player()) -
                 ({ ob });
      if (sizeof(blocking))  {
         foreach (blocker in blocking)  {
            if (undefinedp(is_blocking[blocker]))
               is_blocking[blocker] = ({ ob });
            else
               is_blocking[blocker] |= ({ ob });
         }
         total_blocking |= blocking;
         succeeded = ({ things..., total_blocking... });
      }
   }
   total_blocking = ({ });
   foreach (ob, blocked in is_blocking)  {
#ifdef DEBUG
      if (this_player() == find_player(TELL_ME))
      tell_creator(TELL_ME, "ob == %s, blocked == %O\n",
                   ob->short(), blocked->short());
#endif
      last_blocking = -1;
      for (i = sizeof(total_blocking) - 1; i >= 0; i--)  {
         if (member_array(ob, is_blocking[total_blocking[i]]) > -1)  {
            last_blocking = i;
            break;
         }
      }
      if (last_blocking == -1)  {
         total_blocking = ({ ob, total_blocking... });
#ifdef DEBUG
         if (this_player() == find_player(TELL_ME))
            tell_creator(TELL_ME, "Nothing is blocking ob, adding it to "
                         "the beginning\n%O\n", total_blocking->short());
#endif
         continue;
      }
      total_blocking = ({ total_blocking[0 .. last_blocking]...,
                          ob,
                          total_blocking[(last_blocking + 1) .. ]... });
#ifdef DEBUG
      if (this_player() == find_player(TELL_ME))
         tell_creator(TELL_ME, "Adding ob after last_blocking position "
                      "(%d)\n%O\n",
                      last_blocking, total_blocking->short());
#endif
      limit = last_blocking;
      blocking = copy(blocked);
      for (i = 0; i < limit; i++)  {
         if (member_array(total_blocking[i], blocking) > -1)  {
            blocking += is_blocking[total_blocking[i]];
            if (i == 0)
               total_blocking =
                  ({ total_blocking[1 .. (last_blocking + 1)]...,
                     total_blocking[0],
                     total_blocking[(last_blocking + 2) .. ]... });
            else
               total_blocking =
                  ({ total_blocking[0 .. (i - 1)]...,
                     total_blocking[(i + 1) .. (last_blocking + 1)]...,
                     total_blocking[i],
                     total_blocking[(last_blocking + 2) .. ]... });
            --limit;
            --i;
#ifdef DEBUG
            if (this_player() == find_player(TELL_ME))
               tell_creator(TELL_ME, "Reordered list:\n%O\n",
                            total_blocking->short());
#endif
         }
      }
   }
   foreach (blocker in total_blocking)  {
      tmp1 = CLOTHING_HANDLER->can_wear_or_remove(blocker, this_player());
      if (tmp1)  {
         write("You cannot remove " +
               query_multiple_short(is_blocking[blocker], "the") +
               " " + tmp1 + ".\n");
         things -= is_blocking[blocker];
         break;
      }
      else if (this_player()->remove_armour(blocker))  {
         write("You cannot remove " +
               query_multiple_short(is_blocking[blocker], "the") +
               " because you cannot remove " + blocker->one_short() + ".\n");
         things -= is_blocking[blocker];
         break;
      }
      else removed += ({ blocker });
   }
   succeeded = things & removed;
   failed = ({ });
   foreach (ob in things - removed)  {
      if (this_player()->remove_armour(ob))
         failed += ({ ob });
      else
         succeeded += ({ ob });
   }
   if (sizeof(succeeded) > 0)  {
      removed -= things;
      tmp2 = query_multiple_short(succeeded, "the") ;
      if (sizeof(removed) > 0)  {
         tmp1 = query_multiple_short(removed, "the");
         write("You remove " + tmp1 + " so you can remove " + tmp2 + ".\n");
         say(this_player()->the_short() + " removes " + tmp1 + " so " +
             this_player()->query_pronoun() + " can remove " + tmp2 + ".\n");
      }
      else  {
        hide_invis = ( mapping )this_player()->query_hide_invis();
        hiding = hide_invis[ "hiding" ] ? 1 : 0;
        sneaking = this_player()->query_sneak_level() ? 1 : 0;
        if( hiding || sneaking ) {
          my_light = this_player()->query_light();
          light = environment( this_player() )->query_light();
          difficulty = light + ( 4 * my_light ) / ( light + 1 );
          difficulty += succeeded[0]->query_complete_weight();
          debug_printf( "Difficulty = %d.\n Skill = %s\n Bonus = %d\n",
                        difficulty, SKILL, this_player()->
                        query_skill_bonus( SKILL ) );
          switch( TASKER->perform_task( this_player(), SKILL, difficulty,
            TM_FREE ) ) {
            case AWARD :
              write( "%^YELLOW%^" + ({
                "You discover something that lets your fingers move more "
                  "nimbly.",
                "You find yourself capable of deceiving the eye with greater "
                  "ease than before.",
                "You realise how to deceive the eye more effectively."
              })[ random(3) ] + "%^RESET%^\n" );
            case SUCCEED :
              add_succeeded_mess( ({ "$N $V " + tmp2 + ", managing to stay "
                "unnoticed.\n",
                "" }) );
              break;
            default :
              this_player()->add_succeeded_mess( this_object(), "$N "
                "unsuccessfully tr$y to " + query_verb() + " " + tmp2 +
                " while staying unnoticed.\n", ({ }) );
              break;
          }
        } else {
          this_player()->add_succeeded_mess( this_object(), "$N $V " + tmp2 +
            ".\n", ({ }) );
        }
      }
   }
   succeeded = ({ });
   failed_rewear = ({ });
   foreach (ob in removed)  {
      if (this_player()->wear_armour(ob))
         failed_rewear += ({ ob });
      else
         succeeded += ({ ob });
   }
   if (sizeof(succeeded) > 0)  {
      this_player()->force_burden_recalculate();
      tmp1 = query_multiple_short(succeeded, "the");
      write("You wear " + tmp1 + ".\n");
      say(this_player()->the_short() + " wears " + tmp1 + ".\n");
   }
   if (sizeof(failed_rewear) > 0)  {
      write("You cannot put " +
            query_multiple_short(failed_rewear, "the") + " back on.\n");
   }
   if (sizeof(failed) > 0)  {
      write("You cannot remove " + query_multiple_short(failed, "the") +
            ".\n");
   }
   return 1;
}
mixed *query_patterns() {
   return ({ "<indirect:object:me>", (: cmd($1) :) });
}