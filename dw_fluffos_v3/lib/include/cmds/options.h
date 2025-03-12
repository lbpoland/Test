#ifndef __CMDS_OPTIONS_H
#define __CMDS_OPTIONS_H
#define OPTIONS_TYPE_INTEGER  1
#define OPTIONS_TYPE_STRING   2
#define OPTIONS_TYPE_BOOLEAN  3
#define OPTIONS_TYPE_BRIEF    4
#define OPTIONS_TYPE_COLOUR   5
#define OPTIONS_TYPE_DYNAMIC_GROUP 6
#define OPTIONS_TYPE_PERCENTAGE 7
#define OPTIONS_TYPE_TERMINAL   8
#define OPTIONS_TYPE_GROUP 9
#define OPTION_HANDLER "/obj/handlers/options_handler"
#define OPTION_EXEC_INCLUDE "exec include"
#define TABSTOP_PROP "more tabstop"
#define SHORTHAND_PROP "expand shorthands"
#define SHORTHAND_OUTPUT_PROP "expand output shorthands"
#define MONITOR_OPTIONS ({ "off", "on", "slow", "snails pace" })
#define OPTIONS_TYPE_ALL 0
#define OPTIONS_TYPE_CRE_ONLY 1
#define OPTIONS_TYPE_LORD_ONLY 2
#define OPTIONS_TYPE_PLAYTESTER_ONLY 3
#endif