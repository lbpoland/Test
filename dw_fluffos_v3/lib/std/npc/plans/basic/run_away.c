#include <npc/plan.h>
#include <npc/events.h>
inherit PLAN_BASE_INHERIT;
int moved_event(object npc,
                mixed plan_data,
                string event,
                mixed *data);
void setup() {
   set_sutability(PLAN_MEDIUM_SUTABILITY);
   add_hooked_event(EVENT_MOVED, (: moved_event :));
}
protected int being_attacked(object npc) {
   object *attackers;
   attackers = filter(npc->query_attacker_list(), (: environment($1) ==
                                                 environment($2) :), npc);
   return sizeof(attackers);
}
void activate_plan(object npc,
                   mixed data) {
   npc->run_away();
}
int pre_condition(object npc,
                  string goal,
                  mixed plan_info,
                  string event,
                  mixed *data) {
   int wimpy_level;
   int percent;
tell_creator("pinkfish", "Precondition!\n");
   if (!plan_info) {
      wimpy_level = 50;
   } else {
      wimpy_level = plan_info;
   }
tell_creator("pinkfish", sprintf("%O: %O, %O\n", event, goal, plan_info));
   percent = (npc->query_hp() * 100) / npc->query_max_hp();
   if (percent < wimpy_level) {
      if (being_attacked(npc) ||
          event == EVENT_LOSE_HPS) {
         return 1;
      }
   }
   return 0;
}
int finished(object npc) {
   return !being_attacked(npc);
}
int moved_event(object npc,
                mixed plan_data,
                string event,
                mixed *data) {
   if (finished(npc)) {
      return 1;
   } else {
      npc->run_away();
   }
   return 0;
}