#ifndef __GOALS_H__
#define __GOALS_H__
#define GOAL_LOWEST_PRIORITY 0
#define GOAL_LOW_PRIORITY 1000
#define GOAL_MEDIUM_PRIORITY 2000
#define GOAL_HIGH_PRIORITY 3000
#define GOAL_VERY_HIGH_PRIORITY 4000
#define GOAL_INVALID_PRIORITY -32768
#define GOAL_DEFAULT_PRIORITY GOAL_LOWEST_PRIORITY
#define GOAL_CONTINUE_PROCESSING 1
#define GOALS_DIR "/std/npc/goals/"
#define GOAL_BASE_INHERIT (GOALS_DIR "base")
class goal_control {
   mapping extra_plans;
   string current_plan;
   int priority;
   mixed data;
   mapping plan_info;
}
#define GOAL_EVENT_NOT_HANDLED 0
#define GOAL_EVENT_HANDLED 1
#endif