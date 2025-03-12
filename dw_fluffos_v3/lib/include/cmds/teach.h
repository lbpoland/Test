#ifndef __CMDS_TEACH_H__
#define __CMDS_TEACH_H__
class teaching_skill {
   string skill;
   int lvl;
   int num;
   int xp;
   object teacher;
   object taught;
   object room;
}
#define TEACH_SKILL_TYPE "teach skill"
#define TEACH_COMMAND_TYPE "teach command"
#define TEACH_COMMAND_AUTO_PROPERTY "auto teach"
#endif