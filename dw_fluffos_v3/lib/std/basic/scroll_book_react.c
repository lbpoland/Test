#include <tasks.h>
#define SKILL "magic.items.scroll"
#define CONTROL_SKILL "magic.spells.special"
void destroy_this_scroll() {
}
void check_react(object player) {
   object ob;
   int level;
   int ac;
   string check_spell;
   object paper;
   object *items;
   object env;
   if (!environment(player)) {
      return;
   }
   env = environment(player);
   while (env && !living(env)) {
      env = environment(env);
   }
   if (env && !userp(env) && !env->query_owner()) {
      return ;
   }
   items = filter(deep_inventory(environment(player)),
                  (: $1->query_magic_scroll() ||
                     $1->query_spell_book() :));
   foreach (paper in items) {
      level += paper->query_spell_power_level();
   }
   if (random(sqrt(level)) <= 5 + random(5)) {
      return;
   }
   ob = environment(player);
   while(ob) {
      if(living(ob)) {
         break;
      } else {
         ob = environment(ob);
      }
   }
   if(!ob || !living(ob)) {
      return;
   }
   if(ob) {
      switch(TASKER->perform_task(ob, CONTROL_SKILL, level*2 + random(4),
                                  TM_FREE)) {
      case AWARD:
         tell_object(ob, "Suddenly the spell "+
                      this_object()->query_spell_name()+ " on the "+
                     player->the_short()+" gets out of control and tries to go "
                     "wild.\n");
         tell_room(environment(ob), "Suddenly " + ob->one_short() +
                   " looks very startled as the spell " +
                   this_object()->query_spell_name() +
                   " on "+player->the_short()+" gets out of control and "
                   "tries to go wild.\n", ob);
         write("%^YELLOW%^You feel you have a better grasp of controlling "
               "spells on scrolls.\n.%^RESET%^\n" );
      case SUCCEED:
         return;
      default:
         tell_object(ob, "Suddenly the spell " +
                     this_object()->query_spell_name() + " on the "+
                     player->the_short() +
                     " gets out of control and tries to go wild.\n");
         tell_room(environment(ob), "Suddenly " + ob->one_short() +
                   " looks very startled as the spell " +
                   this_object()->query_spell_name() +
                   " on " + player->the_short() + " gets out of control and "
                   "tries to go wild.\n", ob);
         tell_object(ob, "Unfortunately you cannot get control of it and "
                     "before flying away into nowhere it tears wildly at "
                     "your mind.\n");
         tell_room(environment(ob), "Unfortunately "+ob->one_short()+" cannot "
                   "get control of it and it flies away to freedom.\n", ob);
         ac = (int)ob->query_ac("magic", level * 10);
         level -= ac;
         ob->adjust_hp(-level, this_object());
         ob->adjust_tmp_int(-2 + random(2));
         destroy_this_scroll();
         break;
      }
   }
}
string query_death_reason() {
   return " a spell going wild and getting out of control.";
}