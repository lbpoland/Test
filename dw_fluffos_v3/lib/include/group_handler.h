#ifndef __GROUP_HANDLER_H__
#define __GROUP_HANDLER_H__
#include <command.h>
#define GROUP           "/obj/handlers/group_handler"
#define GROUP_CMD       ( DIR_PLAYER_CMDS "/group" )
#define GROUP_SUB_CMDS_DIR             (DIR_PLAYER_CMDS "/group_cmds/")
#define GROUP_SUB_CMDS_FILE_WILDCARD   "*.c"
#define GROUP_SUBCOMMAND_INHERITABLE   "/cmds/player/group_cmds/base_group"
#define EFFECT          "/std/effects/other/group"
#define SHADOW_OB       "/std/shadows/other/group"
#define INVITE_TIMEOUT        120
#define INVALID_WORDS         ({ })
#define GROUP_NOTIFY_PREFIX   "$I$+5,+0=[$colour$$channel$%^RESET%^] "
#define MIN_EXPERIENCE        0
#define MAX_GROUP_NAME_SIZE                  30
#define MAX_PEOPLE_PER_PARTY                 6
#define MAX_INVITATIONS_PER_PARTY_AT_ONCE    5
#define MAX_PEOPLE_YOU_CAN_ASSIST            1
#define USE_BASE_STATS                       1
#define PRIMARY_BONUS_MULTIPLIER     0.80
#define FIGHTING_BONUS_MULTIPLIER    0.20
#define CONTEMPLATE ( DIR_GUILD_CMDS "/magic/contemplate" )
#define GROUP_TITLE  "group"
#define GROUP_CHANNEL_MAX_CHARS  15
#define GROUP_COLOUR_EVENT   "group"
#endif