#ifndef __SYS__PLAYER
#define __SYS__PLAYER
#include <playtesters.h>
#define NO_POWER "Insufficient Social Points.\n"
#define NOT_ALLOWED "You do not have that ability yet.\n"
#define SHOUT_COST 10
#define TELL_COST 1
#define EMOTE_COST 1
#define REMOTE_COST 5
#define ECHO_COST 1
#define ECHOTO_COST 40
#define EMOTEALL_COST 8
#define SOUL_COST 3
#define SET_POSITION_COST 100
#define NO_LINE_PROP "no new line"
#define RACE_STD "/std/races/human"
#define MAX_IDLE 900
#define FULL_IDLE 300
#define MATURITY 18
#define DEATH "/d/underworld/death/chars/death"
#define DEAD_BOOK "/obj/misc/dead_book"
#define DEATH_SHADOW "/std/shadows/misc/death_shadow"
#define OFFLER "/obj/shut"
#define OFFLER_SHADOW "/std/shadows/misc/offler_shadow"
#define TIME_BETWEEN_SAVES 450
#define PASSED_OUT_PROP "passed out"
#define MAX_TELL_HIS 20
#define ROUND_TIME 40
#define DEFAULT_TIME 20
#define COMBAT_SPEED 2
#define COMBAT_DAMAGE 2
#define TELL_WARN_TIME 120
#define MAX_DESC 2048
#define START_PLAYER "/global/newbie_junk"
#define PKER "player_killer"
#define PKER_MISSPELL "player killer"
#define PKER_MINIMUM_AGE (60 * 60 * 24 * 2)
#define PKER_NOT_ALLOWED "not to be pk"
#define RPMODE "role_playing"
#define MIN_SAVE_REPEAT 900
#define PLAYER_OB "/global/player"
#define CREATOR_OB "/global/creator"
#define LORD_OB "/global/lord"
#define AUTO_LOAD_OB "/global/auto_load"
#define PLAYER_RECEIPT "/obj/misc/al_receipt"
#define UNKNOWN_BIRTHDAY "Unknown"
#define PLAYER_MORGUE "/room/morgue"
#define PLAYER_ALLOW_COLOURED_SOULS "coloured souls"
#define PLAYER_PLAIN_MAPS "plain maps"
#define PLAYER_TITLE_HANDLER "/obj/handlers/title_handler"
#define PLAYER_MULTIPLAYER_HANDLER "/obj/handlers/multiplayer"
#define PLAYER_MAX_FRIEND_TAG_LEN 50
#define PLAYER_EARMUFF_PROP "earmuffs"
#define PLAYER_ALLOW_FRIENDS_EARMUFF 2
#define PLAYER_EARMUFF_ON 1
#define PLAYER_EARMUFF_OFF 0
#define PLAYER_KILLER_FLAG 1
#define DEFAULT_NATIONALITY "/std/nationality/morpork"
#define DEFAULT_REGION "Ankh-Morpork"
#define PLAYER_SHOW_ERRORS_PROP "show errors"
#define PLAYER_OPTIONS_CONTROL_PROP "follow control"
#ifdef PLAYER_OPTIONS_CLASS
class player_options_control {
   int follow_friends;
   int follow_groups;
   int follow_everyone;
   int lead_behind;
   int mxp_disable;
   mapping extra;
}
#endif
#define PLAYER_DRUNK_EFFECT "/std/effects/ingested/drunk"
#endif