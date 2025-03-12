#include <goals.h>
inherit BASE_GOAL;
void create() {
   ::create();
   set_default_priority(GOAL_HIGH_PRIORITY);
   add_default_plan(EVENT_HP_LOST,
                    GOAL_PLAN_DIR + "basic/run_away");
   add_default_plan(EVENT_PLAN_FINISHED,
                    GOAL_PLAN_DIR + "basic/lose_attackers");
}