#include <npc/goals.h>
#include <npc/events.h>
#include <npc/plan.h>
inherit GOAL_BASE_INHERIT;
void setup() {
   set_default_priority(GOAL_HIGH_PRIORITY);
   add_default_plan(EVENT_LOSE_HPS,
                    PLAN_DIR + "basic/run_away");
}
int invarient(object npc) {
   return 1;
}
mixed initialise_plans(object npc,
                       string goal_name,
                       int wimpy) {
tell_creator("pinkfish", "Initialise_plans(%O, %O, %O)\n", npc, goal_name, wimpy);
   npc->set_goal_plan_data(goal_name,
                           PLAN_DIR + "basic/run_away",
                           wimpy);
   return wimpy;
}