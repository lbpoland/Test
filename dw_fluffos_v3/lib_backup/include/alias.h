#ifndef __SYS__ALIAS
#define __SYS__ALIAS
#define ALIAS_MASK 255
#define NEW_LINE 256
#define ALL_ARGS 512
#define ALL_ARG 1024
#define ARG_THING 2048
#define IFARG_THING 4096
#define ALL_IFARG 8192
#define ONE_ARG 16384
#define TO_ARG 32768
#define FROM_ARG 65536
#define ELSE_THING 131072
#define CURR_LOC (ELSE_THING+256)
#define END_IF (ELSE_THING+512)
#define ALIAS_CMD "/cmds/player/al_ias"
#define EDIT_ALIAS_CMD "/cmds/player/ea_lias"
#define UNALIAS_CMD "/cmds/player/un_alias"
#endif