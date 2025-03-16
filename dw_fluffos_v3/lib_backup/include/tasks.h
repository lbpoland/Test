#ifndef __TASKS_H
#define __TASKS_H
#define TASKER "/obj/handlers/taskmaster"
#define BARF      -1
#define FAIL      0
#define SUCCEED   1
#define AWARD     2
#define OFFAWARD  -2
#define OFFWIN    -1
#define DRAW      0
#define DEFWIN    1
#define DEFAWARD  2
#define TASKER_BARF      -1
#define TASKER_FAIL      0
#define TASKER_SUCCEED   1
#define TASKER_AWARD     2
#define TASKER_OFFAWARD  -2
#define TASKER_OFFWIN    -1
#define TASKER_DRAW      0
#define TASKER_DEFWIN    1
#define TASKER_DEFAWARD  2
#define TASKER_MARGINAL     1
#define TASKER_NORMAL       2
#define TASKER_EXCEPTIONAL  3
#define TASKER_CRITICAL     4
#define TASKER_MARGINAL_UPPER        10
#define TASKER_NORMAL_UPPER          80
#define TASKER_EXCEPTIONAL_UPPER     95
#define TASKER_CRITICAL_PERCENTAGE   5
#define BASE 100.0
#define DECAY 300.0
#define MODIFIER 10
#define E_MODIFIER 5
#define COVERT_TM 100, ({0, 5})
#define CONTINUOUS_COVERT_TM 100, ({0, 3})
#define PERCEPTION_TM 50
#define FAITH_TM 75
#define FAITH_TM_HALF 30
#define MAGIC_TM 75
#define MAGIC_TM_HALF 30
#define OTHER_TM 100
#define TM_FIXED 1
#define TM_FREE 2
#define TM_CONTINUOUS 3
#define TM_COMMAND 4
#define TM_RITUAL 5
#define TM_SPELL 6
#define TM_NONE 7
class tasker_result {
   int result;
   int degree;
   int raw;
}
#endif