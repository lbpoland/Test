
==================================================
FILE: ac_callback.h
==================================================

#ifndef __SYS__AC_CALLBACK
#define __SYS__AC_CALLBACK
class ac_callback_data {
    object ob;
    int id;
    function func;
    int priority;
    mixed extra;
}
#endif

==================================================
FILE: access.h
==================================================

#ifndef __SYS__ACCESS
#define __SYS__ACCESS
#define ERROR     0
#define ACCESS    1
#define NO_NEW    2
#define NO_ACCESS 3
#define AUTH_NEW  4
#define DEFAULT ACCESS
#define ACCESS_LEVEL   0
#define ACCESS_REASON  1
#define ACCESS_TIMEOUT 2
#define MULTI_LEVEL 0
#define MULTI_TIMEOUT 1
#define SUSPEND_TIME   0
#define SUSPEND_REASON 1
#define PERM_NAMES ({ "error", "normal access", "no new characters", \
                      "no access", "new requires authorisation" })
#endif

==================================================
FILE: alias.h
==================================================

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

==================================================
FILE: all_inc.h
==================================================

#ifndef __ALL_INC_H
#define __ALL_INC_H
#define NEW_DRIVER
#define DISTRIBUTION_LIB
#pragma strict_types
#pragma warnings
#pragma no_save_types
#pragma no_optimize
#pragma show_error_context
#define slice_array(a,b,c) (a[b..c])
#define m_indices(map) (keys(map))
#define m_sizeof(map) (sizeof(map))
#define m_values(map) (values(map))
#ifndef __SENSIBLE_MODIFIERS__
#define nosave static
#define protected static
#endif
#endif

==================================================
FILE: am_time.h
==================================================

#ifndef __AM_TIME_H
#define __AM_TIME_H
#define AM_TIME_HANDLER "/obj/handlers/am_time_handler"
#define AM_TIME_MONTH 0
#define AM_TIME_DAY_OF_MONTH 1
#define AM_TIME_DAY_OF_WEEK 2
#define AM_TIME_HOUR 3
#define AM_TIME_MINUTE 4
#define AM_TIME_YEAR 5
#define AM_TIME_PRIMUS 6
#define AM_TIME_OFFLE 1
#define AM_TIME_FEBURARY 2
#define AM_TIME_MARCH 3
#define AM_TIME_APRIL 4
#define AM_TIME_MAY 5
#define AM_TIME_JUNE 6
#define AM_TIME_GRUNE 7
#define AM_TIME_AUGUST 8
#define AM_TIME_SPUNE 9
#define AM_TIME_SEKTOBER 10
#define AM_TIME_EMBER 11
#define AM_TIME_DECEMBER 12
#define AM_TIME_ICK 13
#define AM_TIME_MONDAY 1
#define AM_TIME_TUESDAY 2
#define AM_TIME_WEDNESSDAY 3
#define AM_TIME_THURSDAY 4
#define AM_TIME_FRIDAY 5
#define AM_TIME_SATURDAY 6
#define AM_TIME_SUNDAY 7
#define AM_TIME_OCTEDAY 8
#define AM_DAYS_PER_HALF_YEAR 400
#define AM_SECONDS_PER_MINUTE 18
#define AM_MINUTES_PER_HOUR 60
#define AM_HOURS_PER_DAY 24
#define AM_DAYS_PER_WEEK 8
#define AM_MINUTES_PER_DAY (AM_MINUTES_PER_HOUR * AM_HOURS_PER_DAY)
#define AM_SECONDS_PER_DAY (AM_MINUTES_PER_DAY * AM_SECONDS_PER_MINUTE)
#define AM_SECONDS_PER_WEEK (AM_DAYS_PER_WEEK * AM_MINUTES_PER_DAY * AM_SECONDS_PER_MINUTE)
#define AM_SECONDS_PER_HALF_YEAR (AM_SECONDS_PER_DAY * AM_DAYS_PER_HALF_YEAR)
#define AM_SECONDS_PER_HOUR (AM_SECONDS_PER_MINUTE*AM_MINUTES_PER_HOUR)
#define AM_START_YEAR_DATE 1966
#define AM_TIME_FORMAT_NO_TIME 1
class am_time {
   int year;
   int primus;
   int minute;
   int hour;
   int month;
   int day_of_week;
   int day_of_month;
   int day_of_year;
}
#endif

==================================================
FILE: applications.h
==================================================

#ifndef __APPLICATIONS_H
#define __APPLICATIONS_H
#define APPLICATIONS_HANDLER "/obj/handlers/applications_handler"
#define APPLY_COMMAND "/cmds/player/apply"
#define APPLY_SAVE_FILE "/save/applications"
#define MINUTE 60
#define HOUR (60 * MINUTE)
#define DAY (24 * HOUR)
class application {
  string type;
  string name;
  string text;
  mapping vouches;
  int time;
  string domain;
}
class application_type {
  string type;
  string board;
  string *questions;
  int vouches_required;
  int gl_requirement;
  int qp_requirement;
  int age_requirement;
  int timeout;
  string intro_text;
  string responsibility;
}
#endif

==================================================
FILE: armour.h
==================================================

#ifndef __SYS__ARMOUR
#define __SYS__ARMOUR
#define ARM_INNER 0
#define ARM_OUTER 1
class armour_callback {
  int id;
  mixed callback;
  mixed data;
}
#endif

==================================================
FILE: armoury.h
==================================================

#ifndef __SYS__ARMOURY
#define __SYS__ARMOURY
#define ARMOURY "/obj/handlers/armoury"
#define ARMOURY_NO_RECYCLING_PROP "no recycling"
#define ARMOURY_RECYCLING_AREA_PROP "recycling area"
#ifdef UNUSED
#define ARM_A_SIZE 15
#define A_OBJ 0
#define A_ANAME 1
#define A_ALIAS 2
#define A_PLURALS 3
#define A_ADJ 4
#define A_SHORT 5
#define A_LONG 6
#define A_WEIGHT 7
#define A_VALUE 8
#define A_COND 9
#define A_CHANCE 10
#define A_ATYPE 11
#define A_DEX_MINUS 12
#define A_ARMOURS 13
#define A_IMMUNE 14
#define WEAP_A_SIZE 14
#define W_OBJ 0
#define W_NAME 1
#define W_ALIAS 2
#define W_PLURALS 3
#define W_ADJ 4
#define W_SHORT 5
#define W_LONG 6
#define W_WEIGHT 7
#define W_VALUE 8
#define W_COND 9
#define W_DAM_CHANCE 10
#define W_SKILL 11
#define W_ATTACKS 12
#define W_UNDAMAGE 13
#endif
#endif

==================================================
FILE: artifacts.h
==================================================

#define ARTIFACT_HAND "/obj/handlers/artifact_handler"
#define RING_SKILL "magic.items.worn.ring"
#define STAFF_SKILL "magic.items.held.staff"
#define WAND_SKILL "magic.items.held.wand"
#define RING_OBJECT "/obj/ring"
#define STAFF_OBJECT "/obj/staff"
#define WAND_OBJECT "/obj/wand"

==================================================
FILE: assassin.h
==================================================

#include <guilds.h>
#ifndef __ASSASSIN_H
#define __ASSASSIN_H
#define ASSASSIN              "/std/guilds/assassin"
#define ASSASSINS             ( GUILDS + "assassins/" )
#define ASSASSIN_INHERIT      ( ASSASSINS + "inherit/" )
#define ASSASSIN_HANDLERS     "/obj/handlers/guild_things/"
#define ASSASSIN_AM           ( ASSASSINS + "Ankh-Morpork/" )
#define ASSASSIN_GENUA        ( ASSASSINS + "Genua_dev/" )
#define ASSASSIN_OC           ( ASSASSINS + "Ohulan-Cutash/" )
#define ASSASSIN_KLK          ( ASSASSINS + "Khot-lip-khin/" )
#define ASSASSIN_SHEEPRIDGE   ( ASSASSINS + "Sheepridge/" )
#define ASSASSINCHARS         ( ASSASSINS + "chars/" )
#define ASSASSINITEMS         ( ASSASSINS + "items/" )
#define ASSASSIN_SAVE         ( GUILDSAVE + "assassins/" )
#define ASSASSIN_WARDROBES    ( ASSASSIN_SAVE + "wardrobes/" )
#define ASSASSIN_VOTES        ( ASSASSIN_SAVE + "votes/" )
#define ASSASSIN_AM_SAVE      ( ASSASSIN_SAVE + "Ankh-Morpork/" )
#define ASSASSIN_OC_SAVE      ( ASSASSIN_SAVE + "Ohulan-Cutash/" )
#define RUN_HANDLER           ( ASSASSIN_HANDLERS + "run" )
#define ROOM_TRACKER          ( ASSASSIN_HANDLERS + "assassins_gm_room_tracker" )
#define GUILDROOM             ( ASSASSIN_INHERIT + "guildroom" )
#define RUNROOM               ( ASSASSIN_INHERIT + "runroom" )
#define INSIDERUN             ( ASSASSIN_INHERIT + "insiderun" )
#define OUTSIDERUN            ( ASSASSIN_INHERIT + "outsiderun" )
#define ASSASSINS_SHOP        ( ASSASSIN_INHERIT + "assassins_shop" )
#define INHUMATION_OFFICE     ( ASSASSIN_INHERIT + "inhumation_office" )
#define DISAVOWED             "/std/guilds/disavowed"
#endif

==================================================
FILE: assert.h
==================================================

#define assert(x) if(!(x)) error("assertion failed: " +#x)

==================================================
FILE: attack_messages.h
==================================================

#ifndef __ATTACK_MESSAGE_H
#define __ATTACK_MESSAGE_H
#define ATTACK_MESSAGE "/obj/handlers/attack_messages"
#endif

==================================================
FILE: autodoc.h
==================================================

#ifndef __AUTODOC_H
#define __AUTODOC_H
#define AUTO_TYPE 0
#define AUTO_ARGS 1
#define AUTO_DOCS 2
#define AUTO_CLASS_DOCS 2
#define AUTO_CLASS_MEMBERS 1
#define AUTO_CLASS_TYPE 1
#define AUTO_CLASS_NAME 0
#define AUTO_ARGS_TYPE 0
#define AUTO_ARGS_NAME 1
#define AUTO_INDEX_NAME      0
#define AUTO_INDEX_FILE_NAME 1
#define AUTO_INDEX_ARGS      2
#define AUTO_INDEX_SUMMARY   3
#define AUTODOC_FILE "/obj/handlers/autodoc/autodoc_file"
#define AUTODOC_NROFF "/obj/handlers/autodoc/autodoc_nroff"
#define AUTODOC_HTML "/obj/handlers/autodoc/autodoc_html"
#define AUTODOC_HANDLER "/obj/handlers/autodoc/autodoc_handler"
#define NROFF_DOC_DIR "/doc/autodoc/"
#define NROFF_DOC_SINGLE "/doc/creator/autodoc/"
#define HTML_DOC_DIR "/www/external/autodoc/"
#define MASTER_OB "/secure/master.c"
#define SAVE_DIR "/save/autodoc/"
#define SAVE_INDEX_DELAY (60 * 60 * 24)
#endif

==================================================
FILE: bit.h
==================================================

#ifndef __SYS__BIT
#define __SYS__BIT
#define BIT_SIZE 3
#define BIT_NAME 0
#define BIT_ALIAS 1
#define BIT_EXTRA 2
#define EXTRA_PARENT 0
#define EXTRA_WEIGHT 1
#define EXTRA_VALUE 2
#define EXTRA_SUBBIT 3
#define BIT_CONTROLLER "/obj/handlers/bits_controller"
#endif

==================================================
FILE: bits_controller.h
==================================================

#define TIME_OUT 30
#define BITS_CONTROLLER "/obj/handlers/bits_controller"

==================================================
FILE: board.h
==================================================

#ifndef __SYS__BOARD
#define __SYS__BOARD
#define MASTER_OB "/secure/master"
#define NEWS_RC "news rc"
#define BOARD_ORDER "board order"
#define BOARD_FILE "/save/boards.o"
#define BOARD_DIR "/save/boards/"
#define BOARD_RAM_DIR "/save/ramdisk/boards/"
#define BOARD_HAND "/obj/handlers/board_handler"
#define BOARD_WEB "/www/boards"
#define B_SUBJECT 0
#define B_NAME 1
#define B_NUM 2
#define B_TIME 3
#define B_REPLY_TYPE 4
#define B_REPLY_NUM 5
class reply_type {
   int type;
   mixed data;
}
#define B_REPLY_POSTER 1
#define B_REPLY_NAMED 2
#define B_ACCESS_READ 1
#define B_ACCESS_WRITE 2
#define B_ACCESS_DELETE 3
#define B_ACCESS_APPROVE 4
#define B_ACCESS_INFORM 5
#define B_PRIV_NORMAL                 0
#define B_PRIV_READ_ONLY              1
#define B_PRIV_ACCESS_RESTRICTED      2
#define B_PRIV_ACCESS_RESTRICTED_FILE 3
#define B_PRIV_NO_INFORM              256
#define B_PRIV_TYPE_MASK              255
#define B_PRIV_ACCESS_RESTRICTED_METHOD 4
#define BOARD_SOCIAL_POINT_COST 50
#endif

==================================================
FILE: board_master.h
==================================================

#define MAX_PAGE ((int)this_player()->query_rows()-3)
#define TP_NAME this_player()->query_name()
#define SAVE_FILE "/w/pinkfish/save/board_master"
#define BOARD_THING "/w/pinkfish/getter_master"
#define REV_BOARD "/w/pinkfish/reversi_rules"
#define REVERSI_OB "/w/pinkfish/board_master"
#define BOARD_PATH "/w/pinkfish/save/master/"
#define MIN_TIME (60*60*24*14)
#undef DEBUG
#undef DEBUG2
#define MAX_GAMES 10
#define R_PLAYER1 0
#define R_PLAYER2 1
#define R_BOARD 2
#define R_MOVE_NO 3
#define R_LAST 4
#define R_LASTX 5
#define R_LASTY 6
#define R_TYPE 7
#define BOARD_COL "%^B_GREEN%^%^WHITE%^"
#define BLACK_COL "%^B_BLACK%^"
#define WHITE_COL "%^B_WHITE%^"
#define END_TILE  "%^B_GREEN%^"
#define RESET     "%^RESET%^"
#define SETUP_COL "%^B_CYAN%^"
#define P1_WON 1
#define P2_WON 2
#define DRAW 3

==================================================
FILE: book_handler.h
==================================================

#ifndef __BOOK_HANDLER_H
#define __BOOK_HANDLER_H
#define BH_IGNORE_PAGE "generated page"
#define BOOK_HANDLER "/obj/handlers/book_handler"
#define BH_COPYRIGHT "copyright"
#define COLLECT_TIME 0
#define COLLECT_NUM  1
#define COLLECT_OB_NAME 2
#define COLLECT_LANGUAGE 3
#define COLLECT_AUTO_LOAD_NUM 4
#define COLLECT_ARR_SIZE 5
#endif

==================================================
FILE: bounty.h
==================================================

#ifndef __SYS__BOUNTY
#define __SYS__BOUNTY
#define BOUNTY "/obj/handlers/bounty"
#endif

==================================================
FILE: broadcaster.h
==================================================

#ifndef BROADCAST_H
#define BROADCAST_H
#define BROADCASTER "/obj/handlers/broadcaster"
#define HIST_HANDLER "/obj/handlers/hist_handler"
#endif

==================================================
FILE: chime.h
==================================================

#ifndef __CHIME_H
#define __CHIME_H
#define CHIME_HANDLER "/obj/handlers/chime_handler"
#define CHIME_HOUR 1
#define CHIME_HALF_HOUR 2
#define CHIME_QUARTER_HOUR 4
#endif

==================================================
FILE: client.h
==================================================

#ifndef __CLIENT_H__
#define __CLIENT_H__
class client {
    int Descriptor;
    int Blocking;
    mixed *Buffer;
    int Closed;
}
int eventCreateSocket(string host, int port);
protected void eventAbortCallback(int fd);
protected void eventReadCallback(int fd, mixed val);
protected void eventRead(int fd, mixed val);
protected void eventWriteCallback(int fd);
void eventWrite(int fd, mixed val);
protected void eventClose(class client sock);
protected void eventSocketClose(int fd);
int eventDestruct();
protected void eventSocketError(string str, int x);
function SetRead(function f);
int SetSocketType(int x);
int SetDestructOnClose(int x);
#endif

==================================================
FILE: climate.h
==================================================

#ifndef __SYS__CLIMATE
#define __SYS__CLIMATE
#define TEMP 0
#define CLOUD 1
#define WINDSP 2
#define RAIN 3
#define NOTIFY_TEMPERATURE 1
#define NOTIFY_CLOUD       2
#define NOTIFY_RAIN        4
#define NOTIFY_DAY         8
#endif

==================================================
FILE: clothing.h
==================================================

#ifndef __CLOTHING_H
#define __CLOTHING_H
#define CLOTHING_HANDLER "/obj/handlers/clothing_handler"
class clothing_type {
   string *_not_remove;
   string *_hiding;
   int _depth;
}
#endif

==================================================
FILE: clubs.h
==================================================

#ifndef __CLUBS_H
#define __CLUBS_H
#include <am_time.h>
#define CLUB_PERSONAL  0
#define CLUB_ELECTED   1
#define CLUB_FAMILY    2
#define CLUB_ARRAY ({"Personal", "Elected", "Family"})
#define CLUB_DEFAULT_ACCOUNT_NAME "default"
#define CLUB_TYPE_MASK (15)
#define CLUB_FLAGS_MASK (~CLUB_TYPE_MASK)
#define CLUB_SECRET_FLAG 16
#define CLUB_COST_PER_YEAR (400 * 50)
#define CLUB_STARTUP_COST (400 * 100)
#define FAMILY_STARTUP_COST (400 * 300)
#define FAMILY_COST_PER_YEAR (400 * 300)
#define CLUB_COST_PER_MEMBER_PER_YEAR 100
#define FAMILY_COST_PER_MEMBER_PER_YEAR 200
#define CLUB_COST_INSIGNIA (400)
#define CLUB_MINIMUM_ELECTED_MEMBERS 10
#define CLUB_MAXIMUM_ELECTED_MEMBERS 30
#define CLUB_HANDLER "/obj/handlers/club_handler"
#define CLUB_BADGE "/obj/misc/club_badge"
#define CLUB_INVALID_TIME 0
#define CLUB_TIMEOUT (8 * 7 * 24 * 60 * 60)
#define CLUB_PAY_PERIOD (AM_SECONDS_PER_HALF_YEAR / 4)
#define CLUB_ELECTION_PERIOD (AM_SECONDS_PER_HALF_YEAR * 2)
#define CLUB_MINIMUM_ELECTION_PERIOD (AM_SECONDS_PER_HALF_YEAR / 2)
#define CLUB_NOMINATION_TIME (7 * 24 * 60 * 60)
#define CLUB_ELECTION_TIME (7 * 24 * 60 * 60)
#define CLUB_RESPOND_TYPE "club"
#define CLUB_FAMILY_RESPOND_TYPE "family"
#ifndef __CLUBS_H_NO_CLASSES
class family_response_data {
   string family;
   string relationship;
}
class relationship_data {
   string related_to;
   string relationship;
}
#endif
#define CLUB_TRANSACTION_INSIGNIA 1
#define CLUB_TRANSACTION_DEPOSIT 2
#define CLUB_TRANSACTION_UPKEEP 3
#define CLUB_TRANSACTION_START_BALANCE 4
#define CLUB_TRANSACTION_WITHDRAWL 5
#define CLUB_TRANSACTION_TRANSFER 6
#ifndef __CLUBS_H_NO_CLASSES
class club_transaction {
   string who;
   int amount;
   int transaction_type;
   int date;
   string information;
}
class club_archive {
   int archive_date;
   string subject;
   string matter;
}
#endif
#define CLUB_MESSAGE_EMOTE_INDEX 1
#define CLUB_MESSAGE_MESSAGE_INDEX 0
#define CLUB_MAX_NAME_LEN 40
#define MAX_FAMILY_NAME_LEN 15
#define CLUB_ROOM_CLUB_OR_FAMILY 0
#define CLUB_ROOM_CLUB_ONLY   1
#define CLUB_ROOM_FAMILY_ONLY 2
#ifndef __CLUBS_H_NO_CLASSES
class discussion_idea {
   int id;
   int time_added;
   int time_finish;
   int discuss_type;
   string added_by;
   string name;
   string information;
   mapping choices;
   string *voted;
   mixed optional_data;
}
#endif
#define CLUB_DISCUSS_OPEN 0x800000
#define CLUB_DISCUSS_NO_QUORUM 0x400000
#define CLUB_DISCUSS_TYPE_MASK 0xff
#define CLUB_DISCUSS_ELECTION      1
#define CLUB_DISCUSS_DESCRIPTION   2
#define CLUB_DISCUSS_MEMO          3
#define CLUB_DISCUSS_NO_CONFIDENCE 4
#define CLUB_DISCUSS_NEW_POSITION 5
#define CLUB_DISCUSS_POSITION_NAME 6
#define CLUB_DISCUSS_SECRET_TYPE 7
#define CLUB_DISCUSS_MEMBER_REMOVE 8
#define CLUB_DISCUSS_POSITION_REMOVE 9
#define CLUB_DISCUSS_NOMINATION 10
#define CLUB_DISCUSS_FUNCTION 11
#define CLUB_DISCUSS_CREATE_ACCOUNT 12
#define CLUB_DISCUSS_REMOVE_ACCOUNT 13
#define CLUB_DISCUSS_YES_CHOICE "yes"
#define CLUB_DISCUSS_NO_CHOICE "no"
#define CLUB_DISCUSS_ABSTAIN_CHOICE "abstain"
#define CLUB_DISCUSS_MESSAGE_VERIFY            1
#define CLUB_DISCUSS_MESSAGE_COMPLETE          2
#define CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION 3
#define CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION  4
#define CLUB_DISCUSS_MESSAGE_NOMINATION        5
#define CLUB_DISCUSS_MESSAGE_TYPE              6
#define CLUB_DISCUSS_MESSAGE_REMOVE_MEMBER     7
#define CLUB_DISCUSS_MESSAGE_CHANGE_POSITION   8
#define CLUB_DISCUSS_MESSAGE_NOMINATION_QUERY  9
#define CLUB_DISCUSS_MESSAGE_REMOVE_POSITION   10
#define CLUB_DISCUSS_MESSAGE_WITHDRAW          11
#define CLUB_DISCUSS_MESSAGE_TYPE_VOTE         0
#define CLUB_DISCUSS_MESSAGE_TYPE_NOMINATE     1
#define CLUB_DISCUSS_FUNCTION_OBJECT     0
#define CLUB_DISCUSS_FUNCTION_FUNCTION   1
#define CLUB_MAX_POSITION_NAME 30
#define CLUB_UNKNOWN_MEMBER "unknown"
#define CLUB_CONTROLLER_MEMBER "Club Controller"
#endif

==================================================
FILE: cmr.h
==================================================

#ifndef __SYS__CMR
#define __SYS__CMR
#define MINERALS 0
#define GEMS 1
#define METALS 2
#define WOODS 3
#define MATERIALS ({ "mineral", "gem", "metal", "wood" })
#define MATERIAL_ADJECTIVES ({ "mineral", "gem", "metallic", "wooden" })
#define KNOWN 0
#define MAGIC 1
#define OS 2
#define OW 3
#define OVG 4
#define OVJ 5
#define LEARNT 99
#define SKILLS ({ \
      "none", \
      "magic", \
      "crafts.smithing", \
      "crafts.carpentry", \
      "other.valueing.gems", \
      "other.valueing.jewellery", \
   })
#define CMR_HANDLER "/obj/handlers/cmr_handler"
#define CMR_LIBRARY "/obj/handlers/cmr_library"
#endif

==================================================
FILE: colour.h
==================================================

#ifndef __SYS__COLOUR
#define __SYS__COLOUR
#define COL_RED 0
#define COL_PINK 1
#define COL_ORANGE 2
#define COL_YELLOW 3
#define COL_GREEN 4
#define COL_BLUE 5
#define COL_PURPLE 6
#define COL_WHITE 7
#define COL_GREY 8
#define COL_BROWN 9
#define COL_BLACK 10
#define COL_GOLD 11
#define COL_SILVER 12
#define COL_COPPER 13
#define COL_MULTI 14
#define COLOURS ({ "red", "pink", "orange", "yellow", "green", "blue", "purple", "white", "grey", "brown", "black", "gold", "silver", "copper", "multicoloured" })
#define ANSI_COLOURS ({ "%^RED%^", "%^MAGENTA%^", "%^ORANGE%^", "%^YELLOW%^", "%^GREEN%^", "%^BOLD%^%^BLUE%^", "%^MAGENTA%^", "%^BOLD%^%^WHITE%^", "%^CYAN%^", "%^ORANGE%^", "%^BOLD%^%^BLUE%^"  })
#define REDDISH 0
#define PINKISH 1
#define YELLOWISH 3
#define GREENISH 4
#define BLUISH 5
#define PURPLISH 6
#define PALE 7
#define GREYISH 8
#define BROWNISH 9
#define BLACKISH 10
#define OFF 11
#define MUDDY 12
#define WHITISH 13
#define GOLDEN 14
#define LIGHT 15
#define DARK 16
#define VARIEGATED 17
#define SILVERY 18
#define METALLIC 19
#define MODIFIERS ({ "reddish ", "pinkish ", "orange-", "yellowish ", "greenish ", "bluish ", "purplish ", "pale ", "greyish ", "brownish ", "blackish ", "off-", "muddy ", "whitish ", "golden ", "light ", "dark ", "variegated ", "silvery ", "metallic " })
#define USER_COLOUR_LIST ({"newbie", "shout", "tell", "say", "whisper", \
                            "soul", "emote", "remote", "exits", "inventory", \
                           "weather", "group", "shopchat", "emoteall", \
                           "combat"})
#endif

==================================================
FILE: combat.h
==================================================

#ifndef __SYS_COMBAT
#define __SYS_COMBAT
#include <player.h>
class surrender_information {
   object *refusers;
   object *to;
   object *from;
}
class combat_special {
  int id;
  int type;
  int events;
  mixed callback;
  mixed data;
}
class combat_information {
  int hbc;
  int mbc;
  int in_combat;
  int special_id;
  object *protectors;
  object *defenders;
  mapping attacker_list;
  mapping hunting_list;
  object concentrating;
  object last_opponent;
  object last_weapon;
  string last_action;
  int last_result;
  int action_defecit;
  class combat_special *specials;
}
class tactics {
  string attitude;
  string response;
  string parry;
  string attack;
  int parry_unarmed;
  string mercy;
  string focus_zone;
  string ideal_distance;
}
class attack {
  object attacker;
  class tactics attacker_tactics;
  class combat_special *attacker_specials;
  object attacker_concentrating;
  object attack_weapon;
  string attack_action;
  string attack_skill;
  mixed *attack_data;
  int attacker_defecit;
  int attack_cost;
  int attack_modifier;
  object attacker_last_opponent;
  object attacker_last_weapon;
  string attacker_last_action;
  int attacker_last_result;
  object opponent;
  class combat_special *defender_specials;
  object person_hit;
  object defender;
  int distance;
  class tactics defender_tactics;
  object defender_concentrating;
  object defense_weapon;
  string defense_limb;
  string defense_action;
  string defense_skill;
  int defender_defecit;
  int defense_cost;
  int defender_cost;
  int protector_cost;
  int defense_modifier;
  object defender_last_opponent;
  object defender_last_weapon;
  string defender_last_action;
  int defender_last_result;
  int damage;
  int armour_stopped;
  mixed stopped_by;
  string target_zone;
  int result;
  int degree;
  object corpse;
  string *attack_messages;
  string *defense_messages;
  int verbose;
  int repeat_count;
  int repeat;
}
#define WEAPON_PARRY "fighting.combat.parry.melee"
#define UNARMED_PARRY "fighting.combat.parry.melee"
#define DODGE "fighting.combat.dodging.melee"
#define ATTACK_SKILL "fighting.combat.melee."
#define MOVE_SKILL "fighting.combat.special.tactics"
#define TACTICAL_SKILL "fighting.combat.special.tactics"
#define SPECIAL_WEAPON "fighting.combat.special.weapon"
#define SPECIAL_UNARMED "fighting.combat.special.unarmed"
#undef COMBAT_SPEED
#define COMBAT_SPEED 1
#define COMBAT_ACTION_TIME (environment() ? environment()->attack_speed() : 15)
#define ACTIONS_PER_HB DEFAULT_TIME
#define ATTACK_COST (COMBAT_ACTION_TIME * 4) / 3
#define DEFENSE_COST (COMBAT_ACTION_TIME * 2) / 3
#define MOVE_COST (COMBAT_ACTION_TIME / 4)
#define ATTACK_GP ([ "insane" : 1, \
                     "offensive" : 0, \
                     "neutral" : 0,\
                     "defensive" : 1, \
                     "wimp" : 2 ])
#define DEFENSE_GP ([ "insane" : 2, \
                     "offensive" : 1, \
                     "neutral" : 0,\
                     "defensive" : 0, \
                     "wimp" : 1 ])
#define DEFENDER_GP ([ "insane" : 4, \
                       "offensive" : 2, \
                       "neutral" : 1,\
                       "defensive" : 2, \
                       "wimp" : 3 ])
#define BALANCE_MOD (random(random(75)) - 25)
#define HUNTING_TIME 300
#define INITIAL_DISTANCE 45
#define DISTANCE_STEP 9
#define REACH 18
#define DISTANCES ([ "ranged" : 45, "long" : 36, "medium" : 27, "close" : 18,\
                     "hand-to-hand" : 9 ])
#define T_OFFENSIVE 1
#define T_DEFENSIVE 2
#define T_CONTINUOUS 4
#define E_OPPONENT_SELECTION 1
#define E_DEFENDER_SELECTION 2
#define E_ATTACK_SELECTION 4
#define E_DEFENSE_SELECTION 8
#define E_ATTACK_MODIFIER 16
#define E_DEFENSE_MODIFIER 32
#define E_DAMAGE_CALCULATION 64
#define E_ARMOUR_CALCULATION 128
#define E_WEAPON_DAMAGE 256
#define E_WRITE_MESSAGES 512
#define E_AFTER_ATTACK 1024
#define R_PASSTHRU 1
#define R_CONTINUE 2
#define R_DONE 4
#define R_ABORT 8
#define R_REMOVE_ME 16
#define MAX_ACTION_DEFECIT 100
#define MIN_ACTION_DEFECIT 0
#define M_ATTACKER 0
#define M_OPPONENT 1
#define M_SPECTATORS 2
#define M_DEFENDER 3
#define M_PERSON_HIT 4
#define OFFENSIVE_DEFECITS ([ "insane" : (COMBAT_ACTION_TIME * 2), \
                              "offensive" : (COMBAT_ACTION_TIME), \
                              "neutral" : (COMBAT_ACTION_TIME * 2 / 3),\
                              "defensive" : (COMBAT_ACTION_TIME / 2), \
                              "wimp" : (COMBAT_ACTION_TIME / 4) ])
#define DEFENSIVE_DEFECITS (["insane" : (COMBAT_ACTION_TIME / 2), \
                             "offensive" : (COMBAT_ACTION_TIME), \
                             "neutral" : (COMBAT_ACTION_TIME * 3 / 2), \
                             "defensive" : (COMBAT_ACTION_TIME * 2), \
                             "wimp" : (COMBAT_ACTION_TIME * 3) ])
#define MOVE_DISTANCE ([ "insane" : 36, "offensive" : 27, "neutral" : 9,\
                         "defensive" : 0, "wimp" : 0 ])
#endif

==================================================
FILE: command.h
==================================================

#ifndef _COMMAND_H
#define _COMMAND_H
#define CMD_D "/secure/command"
#define DIR_PLAYER_CMDS "/cmds/player"
#define DIR_SECURE_PLAYER_CMDS "/secure/cmds/player"
#define DIR_LIVING_CMDS "/cmds/living"
#define DIR_CREATOR_CMDS "/cmds/creator"
#define DIR_SECURE_CREATOR_CMDS "/secure/cmds/creator"
#define DIR_LORD_CMDS "/cmds/lord"
#define DIR_SECURE_LORD_CMDS "/secure/cmds/lord"
#define DIR_GUILD_CMDS "/cmds/guild-race"
#define DIR_PLAYTESTER_CMDS "/cmds/playtester"
#define DIR_SENIOR_PLAYTESTER_CMDS "/cmds/playtester/senior"
#define DIR_EXEC_PLAYTESTER_CMDS "/cmds/playtester/exec"
class command {
  string verb;
  string file;
  string args;
  string filepart;
}
class command_class {
    mapping patterns;
    string* order;
}
class command_data {
    int weight;
    mixed* calls;
}
#endif

==================================================
FILE: comms.h
==================================================

#ifndef __SYS__COMMS
#define __SYS__COMMS
#define COMM_ROOM "/d/guilds/wizards/Ankh-Morpork/old/comm_room"
#endif

==================================================
FILE: complaints_handler.h
==================================================

#ifndef __COMPLAINTS_HANDLER_H
#define __COMPLAINTS_HANDLER_H
#define COMPLAINTS_HANDLER "/obj/handlers/complaints_handler"
#endif

==================================================
FILE: config.h
==================================================

#ifndef __SYS__CONFIG
#define __SYS__CONFIG
#define __DISCWORLD__
#define __DISTRIBUTION_LIB__
#define CONFIG_START_LOCATION "/d/dist/pumpkin/squash/squash5"
#define CONFIG_NEWBIE_START_LOCATION "/d/liaison/NEWBIE/foyer"
#define CONFIG_DEFAULT_RACE "/std/races/human"
#define CONFIG_DEFAULT_GUILD "/std/guilds/standard"
#define CONFIG_DB_USER "ddt"
#define CONFIG_WEB_ADDRESS "http:
#define CONFIG_EXTERNAL_WEB_ADDRESS "http:
#endif

==================================================
FILE: corpse.h
==================================================

#ifndef __SYS__CORPSE
#define __SYS__CORPSE
#define STD_CORPSE_WEIGHT 1600
#define CORPSE_OBJECT "/obj/corpse"
#define CORPSE_HANDLER "/obj/handlers/corpse_handler"
#define CORPSE_IN_PLAYER "corpse in player"
#endif

==================================================
FILE: cpi.h
==================================================

#define PRICE_INDEX "/obj/handlers/cpi_handler"
#define DEFAULT_MARKET "Ankh-Morpork"

==================================================
FILE: crafts.h
==================================================

#ifndef __CRAFTS
#define __CRAFTS
#define CRAFT_ERROR 0
#define CRAFT_INHERIT "/obj/crafts/base"
#define CRAFT_HANDLER "/obj/crafts/craft_handler"
#define CRAFT_MATERIAL_REQUIRED 1
#define CRAFT_MATERIAL_ONE_OF 2
#define CRAFT_MATERIAL_OPTIONAL 3
#define CRAFT_MATERIAL_DENIED 4
#define CRAFT_MATERIAL_TYPE_MASK 127
#define CRAFT_MATERIAL_ALL    128
#define CRAFT_QUALITY_WORTHLESS -4
#define CRAFT_QUALITY_AWFUL -3
#define CRAFT_QUALITY_BAD -2
#define CRAFT_QUALITY_POOR -1
#define CRAFT_QUALITY_NORMAL 0
#define CRAFT_QUALITY_FINE 1
#define CRAFT_QUALITY_GOOD 2
#define CRAFT_QUALITY_EXCELLENT 3
#define CRAFT_QUALITY_PERFECT 4
class crafts_bonus {
   mapping result;
   mapping skill_bonus;
   int quality;
   int bonus;
}
#endif

==================================================
FILE: creator.h
==================================================

#ifndef _CREATOR_H
#define _CREATOR_H
#define WIZ_PRESENT "/global/wiz_present"
#define PEOPLER "/obj/handlers/peopler"
#define RCS_HANDLER "/secure/rcs_handler"
#define NO_CHANNELS ({ "admin", "fluffy", "liaison", "playtesters" })
#define ADDITIONAL_CHANNELS ({ "code", "cre", "liaison" })
#define INTERMUD_MAP ([ "dwchat" : "discworld-chat", "dwcre" : "discworld-cre", "intergossip" : "imud_gossip", "intercre" : "imud_code"])
#endif

==================================================
FILE: cwc.h
==================================================

#ifndef __CWC_H
#define __CWC_H
#define CWC "/d/cwc/"
#define INHERIT CWC "inherit/"
#define CITY_INHERIT INHERIT "city_inherit"
#define HOSPITAL_INHERIT INHERIT "hospital"
#define HOSPITAL_PATH CWC "hospital/"
#define CWC_HANDLERS CWC "handlers/"
#define CWC_TELEPORT_INHERIT "/d/cwc/inherit/teleport_inherit"
#define BES_PELARGIC CWC "Bes_Pelargic/"
#define HUNGHUNG CWC "Hunghung/"
#define CWC_CHARS CWC "chars/"
#define CWC_ITEMS CWC "items/"
#define CWC_SAVE "/save/cwc/"
#define SAVE "/save/cwc/"
#define SECURE CWC "secure/"
#define ORIGAMI_HANDLER CWC_HANDLERS + "origami_handler"
#define CWC_START_LOCATION "/d/cwc/Bes_Pelargic/Bad_Poo-Ning/roads/piers/pier303"
#define SHOO_LI BES_PELARGIC "Shoo_Li/"
#define CUSTOM_NPCS 0
#endif

==================================================
FILE: data.h
==================================================

#ifndef __DATA_HANDLER_H
#define __DATA_HANDLER_H
#define DATA_HANDLER "/obj/handlers/data"
class data_dice {
   int die;
   int number;
   int modifier;
}
#endif

==================================================
FILE: dates.h
==================================================

#define OFFLE -1
#define FEBRUARY 30
#define MARCH 60
#define APRIL 91
#define MAY 122
#define JUNE 153
#define GRUNE 183
#define AUGUST 214
#define SPUNE 245
#define SEKTOBER 276
#define EMBER 306
#define DECEMBER 337
#define ICK 368
#define HOGSWATCH 0
#define SMALLGODS 200
#define SOULCAKE 237
#define SEKTOBERFOOL 277

==================================================
FILE: db.h
==================================================

#ifndef DB_H
#define DB_H
#define db_escape(query) replace_string((query), "'", "''")
#define DB_HANDLER "/net/daemon/mysql"
#define DB_SUCCESS 0
#define DB_ERROR_BAD_SOCKET -1
#endif

==================================================
FILE: decay_handler.h
==================================================

#define DECAY_TIME 15
#define DECAY_HANDLER "/obj/handlers/decay_handler"

==================================================
FILE: dirs.h
==================================================

#ifndef __SYS__DIRS
#define __SYS__DIRS
#define STD_ORDERS ({ \
  "north", ({ -1, 0, 0 }), "south", ({ 1, 0, 0 }), \
  "east", ({ 0, -1, 0 }), "west", ({ 0, 1, 0 }), \
  "northeast", ({ -1, -1, 0 }), "southwest", ({ 1, 1, 0 }), \
  "southeast", ({ 1, -1, 0 }), "northwest", ({ -1, 1, 0 }), \
  "up", ({ 0, 0, -1 }), "down", ({ 0, 0, 1 }) })
#define REL_DIRS ({ \
   "forward", "up ahead", "in front of you", \
   "forward-right", "ahead and to the right", "in front and to your right", \
   "right", "the right", "to your right", \
   "backward-right", "behind you and to the right", "behind you and to your right", \
   "backward", "behind you", "behind you", \
   "backward-left", "behind you and to the left", "behind you and to your left", \
   "left", "the left", "to your left", \
   "forward-left", "ahead and to the left", "in front and to your left" })
#define ABS_FACING ([ \
  "north":8, "northeast":1, \
  "east":2, "southeast":3, \
  "south":4, "southwest":5, \
  "west":6, "northwest":7 ])
#define SHORTEN ([ \
  "north":"n", "south":"s", \
  "east":"e", "west":"w", \
  "northeast":"ne", "southwest":"sw", \
  "southeast":"se", "northwest":"nw", \
  "up":"u", "down":"d", \
  "hubward":"hw", "rimward":"rw", \
  "widdershins":"ws", "turnwise":"tw", \
  "forward":"fw", "forward-right":"fr", \
  "right":"rt", "backward-right":"br", \
  "backward":"bw", "backward-left":"bl", \
  "left":"lt", "forward-left":"fl" ])
#define LENGTHEN ([ \
  "n":"north", "s":"south", \
  "e":"east", "w":"west", \
  "ne":"northeast", "sw":"southwest", \
  "se":"southeast", "nw":"northwest", \
  "u":"up", "d":"down", \
  "hw":"hubward", "rw":"rimward", \
  "ws":"widdershins", "tw":"turnwise", \
  "fw":"forward", "fr":"forward-right", \
  "rt":"right", "br":"backward-right", \
  "bw":"backward", "bl":"backward-left", \
  "lt":"left", "fl":"forward-left" ])
#define EXPAND_EXIT(x) LENGTHEN[x]?LENGTHEN[x]:x
#endif

==================================================
FILE: disease.h
==================================================

#define EFFECTS "/std/effects/"
#define SHADOWS "/std/shadows/"
#define BASIC_DISEASE EFFECTS "disease/basic_disease"
#define SIMPLE_DISEASE EFFECTS "disease/simple_disease"
#define BASIC_CURE EFFECTS "healing/basic_cure"
#define SIMPLE_CURE EFFECTS "healing/simple_cure"
#define DISEASE_HANDLER "/obj/handlers/disease"
#define CURE_SCALE ({ 2, 3, 3, 3 })
#define DISEASE_SCALE ({ 2, 3, 3, 3 })

==================================================
FILE: door.h
==================================================

#ifndef __SYS__NEW_DOOR
#define __SYS__NEW_DOOR
#define D_CLOSED 0
#define D_LOCKED 1
#define D_KEY 2
#define D_DIFFICULTY 3
#define D_SECRET 4
#define D_TRANSPARENT 5
#define D_NAME 6
#endif

==================================================
FILE: drinks.h
==================================================

#ifndef __SYS__DRINKS
#define __SYS__DRINKS
#define D_SIZEOF 3
#define D_ALCOHOL 0
#define D_FOOD 1
#define D_DRINK 2
#endif

==================================================
FILE: dst.h
==================================================

#ifndef __SYS__DST
#define __SYS_DST
#define AUS_DST -1
#define UK_DST 0
#define US_DST 0
#define CA_DST 0
#endif

==================================================
FILE: ed.h
==================================================

#ifndef __SYS__ED
#define __SYS__ED
#define LOG_FILE "/save/board/LOG"
#define TEMP_DIR "/tmp/"
#define TMP_FILE TEMP_DIR+"board."+(string)this_player()->query_name()+".tmp"
#define ED_HELP_FILE "/doc/concepts/edit_help"
#define PRESTOS_ED "/global/magic"
#endif

==================================================
FILE: effect.h
==================================================

#ifndef __SYS__EFFECT
#define __SYS__EFFECT
#define REMOVE_THIS_EFFECT 2000000000
#define REMOVE_THIS_EFFECT_NEXT_HB 2000000001
#define CANCEL_THIS_EE 2000000002
#define EE_REMOVE 1
#define EE_CONTINUOUS 2
#define EE_OLD 4
#define EE_CANCELLED 8
#define EE_ONCE 0
#define BOGUS_OLD_ARG 20495621
class effect {
  string ob_name;
  mixed arg;
}
#endif

==================================================
FILE: error_handler.h
==================================================

#ifndef __ERROR_HANDLER_H
#define __ERROR_HANDLER_H
#define ERROR_BAD_QUERY -1000
#define ERROR_HANDLER "/obj/handlers/error_handler"
#define ERROR_CATEGORIES ({ "ROOM", "OBJECT", "HELP", "RITUAL", "SPELL", "COMMAND", "GENERAL" })
#define ERROR_STATUS_OPEN "OPEN"
#define ERROR_STATUS_FIXING "FIXING"
#define ERROR_STATUS_CONSIDERING "CONSIDERING"
#define ERROR_STATUS_FIXED "FIXED"
#define ERROR_STATUS_DENIED "DENIED"
#define ERROR_STATUS ({ ERROR_STATUS_FIXED, ERROR_STATUS_DENIED, \
                        ERROR_STATUS_FIXING, ERROR_STATUS_CONSIDERING, \
                        ERROR_STATUS_OPEN })
#define ERROR_TYPE ({ "BUG", "TYPO", "IDEA", "COMMENT" })
#define ERROR_ORDER_BY_FILENAME "filename"
#define ERROR_ORDER_BY_DIRECTORY "directory"
#define ERROR_ORDER_BY_DATE "date"
#define ERROR_ORDER_BY_REPORTER "reporter"
#define ERROR_ASSIGNED_NO_ONE "nobody"
class error_summary {
   int id;
   int entry_date;
   string filename;
   string category;
   string assigned_to;
   string reporter;
   string type;
   string status;
   string directory;
}
class error_details {
   class error_summary summary;
   int fix_date;
   string fixer;
   string report;
   string runtime;
}
class error_comment {
   int date;
   string commenter;
   string comment;
}
class error_forward {
   int date;
   string forwarder;
   string old_directory;
}
class error_replies {
   int id;
   int bug_id;
   string sender;
   string recipient;
   string status;
   int senddate;
   string subject;
   string message;
}
class error_complete {
   class error_details details;
   class error_comment* comments;
   class error_forward* forwards;
   class error_replies* replies;
}
class error_query {
   int no_extra_details;
   int recursive;
   int id;
   int bug_offset;
   int* id_list;
   string dir;
   string assigned_to;
   string file_name;
   string reporter;
   string fixer;
   string* status;
   string* category;
   string* type;
   string order_by;
}
#endif

==================================================
FILE: esc.h
==================================================

#ifndef __SYS__ESC
#define __SYS__ESC
#define esc ""
#endif

==================================================
FILE: expressions.h
==================================================

#ifndef __EXPRESSIONS_H
#define __EXPRESSIONS_H
#define EXPRESSION_TYPE_INTEGER  1
#define EXPRESSION_TYPE_STRING   2
#define EXPRESSION_TYPE_ARRAY    3
#define EXPRESSION_TYPE_MAPPING  4
#define EXPRESSION_TYPE_FLOAT    5
#define EXPRESSION_TYPE_OPERATOR 6
#define EXPRESSION_TYPE_BOOLEAN  7
#define EXPRESSION_TYPE_VARIABLE 8
#define EXPRESSION_TYPE_MONEY    9
#define EXPRESSION_TYPE_FUNCTION 10
#define EXPRESSION_TYPE_SPECIAL  11
#define EXPRESSION_TYPE_FUNCTION_VARIABLE 12
#define EXPRESSION_TYPE_USER_FUNCTION 13
#define EXPRESSION_TYPE_OBJECT   14
#define EXPRESSION_TYPE_ARRAY_NULL   15
#define EXPRESSION_TYPE_ARRAY_OFFSET  20
#define EXPRESSION_TYPE_ERROR    -1
#ifndef EXPRESSION_NO_CLASSES
class parse_node {
   int type;
   mixed value;
   mixed* tree;
}
#endif
#endif

==================================================
FILE: fighter.h
==================================================

#define GUILD_OB "/std/guilds/fighter"
#define FIGHTER "/d/guilds/fighters/"
#define FIGHTERCHARS FIGHTER+"chars/"
#define FIGHTERITEMS FIGHTER+"items/"

==================================================
FILE: finger.h
==================================================

#ifndef __SYS__FINGER
#define __SYS__FINGER
#define CREATE (name != "domos" && name != "shru")
#endif

==================================================
FILE: fixed_random.h
==================================================

#ifndef __FIXED_RANDOM_H
#define __FIXED_RANDOM_H
#define RANDOM_OBJ "/obj/handlers/random_num"
#endif

==================================================
FILE: forms.h
==================================================

#ifndef __SYS__FORMS
#define __SYS__FORMS
#define FLG_NEW_LINE 1
#define FLG_TEXT_ONLY 2
#define FLG_TEXT_INVIS 4
#define FLG_TEXT_CENTER 10
#endif

==================================================
FILE: forn.h
==================================================

#ifndef __FORN_H
#define __FORN_H
#define FORN                   "/d/forn/"
#define CHARS                  FORN + "chars/"
#define DOCS                   FORN + "docs/"
#define FORN_INCLUDE           FORN + "include/"
#define HANDLERS               FORN + "handlers/"
#define INHERITS               FORN + "inherits/"
#define HOSPITAL_DIR           FORN + "hospital/"
#define IDEAS                  FORN + "ideas/"
#define ITEMS                  FORN + "items/"
#define LOG                    FORN + "log/"
#define SECURE                 FORN + "secure/"
#define UTILS                  FORN + "utils/"
#define WEB                    FORN + "public_html/"
#define EFFECTS                FORN + "effects/"
#define SAVE_DIR               "/save/"
#define SAVE                   SAVE_DIR + "forn/"
#define GENUA                  FORN + "genua/"
#define POLICY                 DOCS + "policy/"
#define HELP                   DOCS + "help_files/"
#define SCRIPTS                DOCS + "scripts/"
#define WARGAME_MAPS           DOCS + "wargame_maps/"
#define GENUA_CHARS            GENUA + "chars/"
#define GENUA_CITY             GENUA + "genua_city_dev/"
#define GENUA_EFFECTS          GENUA + "effects/"
#define GENUA_HANDLERS         GENUA + "handlers/"
#define GENUA_HOUSING          GENUA + "player_housing/"
#define GENUA_INHERITS         GENUA + "inherits/"
#define GENUA_ITEMS            GENUA + "items/"
#define GENUA_PLAYER_HOUSING   GENUA + "player_housing/"
#define GENUA_PLAYER_HOUSING   GENUA + "player_housing/"
#define GENUA_ROGUE_ENCAMPMENT GENUA + "rogue_encampment/"
#define GENUA_SHADOWS          GENUA + "shadows/"
#define GENUA_SLEEPING_CASTLE  GENUA + "sleeping_castle/"
#define GENUA_SWAMP            GENUA + "swamp/"
#define GENUA_VILLAGES         GENUA + "villages/"
#define GENUA_YELLOW_ROAD      GENUA + "yellow_brick_road/"
#define GENUA_BANKER           GENUA_INHERITS + "coffee_nostra_banker"
#define GENUA_BASE             GENUA_INHERITS + "genua_base"
#define GENUA_CITIZEN          GENUA_INHERITS + "protected_npc"
#define GENUA_CAPO             GENUA_INHERITS + "capo_inherit"
#define GENUA_CITYROOM         GENUA_INHERITS + "cityroom"
#define GENUA_CITY_GUARD       GENUA_INHERITS + "city_guard"
#define GENUA_COMMERCE         GENUA_INHERITS + "genua_commerce"
#define GENUA_CONSIGLIERE      GENUA_INHERITS + "consigliere"
#define GENUA_GENERAL_SHOP     GENUA_INHERITS + "genua_general_shop"
#define GENUA_HOTEL_INSIDE     GENUA_INHERITS + "genua_hotel_inside"
#define GENUA_HOTEL_OUTSIDE    GENUA_INHERITS + "genua_hotel_outside"
#define GENUA_INNER_RING       GENUA_INHERITS + "genua_inner_ring"
#define GENUA_INSIDE_ROOM      GENUA_INHERITS + "genua_inside_room"
#define GENUA_ITEM_SHOP        GENUA_INHERITS + "genua_item_shop"
#define GENUA_MAFIA_HOOD       GENUA_INHERITS + "coffee_nostra_hood"
#define GENUA_MAFIA_INHERIT    GENUA_INHERITS + "mafia_inherit"
#define GENUA_MARKET_INHERIT   GENUA_INHERITS + "genua_market_inherit"
#define GENUA_MONEYCHANGER     GENUA_INHERITS + "genua_bureau_de_change"
#define GENUA_MONSTER          GENUA_INHERITS + "genua_monster"
#define GENUA_OUTER_RING       GENUA_INHERITS + "genua_outer_ring"
#define GENUA_OUTSIDE_ROOM     GENUA_INHERITS + "genua_outside_room"
#define GENUA_PLAYER_HOUSE     GENUA_INHERITS + "genua_player_house"
#define GENUA_PLAYER_HOUSE_OUTSIDE GENUA_INHERITS + "genua_player_house_outside"
#define GENUA_PUB              GENUA_INHERITS + "genua_pub"
#define GENUA_PUB_OUTSIDE      GENUA_INHERITS + "genua_pub_outside"
#define GENUA_SOLDIER          GENUA_INHERITS + "genua_soldier"
#define GENUA_WATCH_INHERIT    GENUA_INHERITS + "watch_house"
#define GRAVEYARD_INHERIT      GENUA_INHERITS + "graveyard_inherit"
#define MURDER_SUSPECT         GENUA_INHERITS + "murder_suspect"
#define CRIME_HANDLER_DIR      GENUA_HANDLERS + "ledger/"
#define PUNISHMENT_HANDLER_DIR GENUA_HANDLERS + "punishment/"
#define SERVICE_HANDLER_DIR    PUNISHMENT_HANDLER_DIR + "service/"
#define BOIS                   GENUA_VILLAGES + "bois/"
#define BOIS_BEARS_HOUSE       BOIS + "bears_house/"
#define BOIS_GRANDMA           BOIS + "grandma/"
#define BOIS_LAKE              BOIS + "lake/"
#define BOIS_MAIN_ROAD         BOIS + "main_road/"
#define BOIS_THREE_PIGS        BOIS + "three_pigs/"
#define BOIS_VILLAGE           BOIS + "village/"
#define BOIS_CHARS             GENUA_CHARS + "bois/"
#define BLACK_MARKET           GENUA_CITY + "black_market/"
#define CALYPSO_STREET         GENUA_CITY + "calypso_street/"
#define CARREFOUR_CRESCENT     GENUA_CITY + "carrefour_crescent/"
#define CITY_LIBRARY           GENUA_CITY + "city_library/"
#define COFFEE_NOSTRA_ROOM     GENUA_CITY + "coffee_nostra/"
#define DARLING_ROAD           GENUA_CITY + "darling_road/"
#define DAUPHIN_STREET         GENUA_CITY + "dauphin_street/"
#define DEAD_MANS_WALK         GENUA_CITY + "dead_mans_walk/"
#define DIAMOND_CRESCENT       GENUA_CITY + "diamond_crescent/"
#define DOLMEN_WALK            GENUA_CITY + "dolmen_walk/"
#define FELICITY_AVENUE        GENUA_CITY + "felicity_avenue/"
#define FLORIN_AVENUE          GENUA_CITY + "florin_avenue/"
#define GENUA_AVENUE           GENUA_CITY + "genua_avenue/"
#define GENUA_BARRACKS         GENUA_CITY + "barracks/"
#define GENUA_CASINO           GENUA_CITY + "genua_casino/"
#define GENUA_CITY_PARK        GENUA_CITY + "genua_city_park/"
#define GENUA_DOCKS            GENUA_CITY + "genua_docks/"
#define GENUA_GRAVEYARD        GENUA_CITY + "graveyard/"
#define GENUA_HAUNTED_HOUSE    GENUA_CITY + "haunted_house/"
#define GENUA_HOTEL            GENUA_CITY + "genua_hotel/"
#define GENUA_KICK_CONSORTIUM  GENUA_CITY + "kick_consortium/"
#define GENUA_MAIN_GATE        GENUA_CITY + "main_gate/"
#define GENUA_MARKET           GENUA_CITY + "genua_market/"
#define GENUA_PALACE           GENUA_CITY + "genua_palace/"
#define GENUA_RACETRACK        GENUA_CITY + "genua_racetrack/"
#define GENUA_SMUGGLERS_COVE   GENUA_CITY + "smugglers_cove/"
#define GENUA_WEDDING_CHAPEL   GENUA_CITY + "wedding_chapel/"
#define GOLDEN_KEY_CRESCENT    GENUA_CITY + "golden_key_crescent/"
#define GRIM_STREET            GENUA_CITY + "grim_street/"
#define HOUSE_OF_MUSIC         GENUA_CITY + "house_of_music/"
#define LACHAISE_ROAD          GENUA_CITY + "lachaise_road/"
#define LADY_BROOK_STREET      GENUA_CITY + "lady_brook_street/"
#define LIQUOR_ALLEY           GENUA_CITY + "liquor_alley/"
#define LOVERS_WALK            GENUA_CITY + "lovers_walk/"
#define MARKET_STREET          GENUA_CITY + "market_street/"
#define MINARET_STREET         GENUA_CITY + "minaret_street/"
#define NAWLINS_ROAD           GENUA_CITY + "nawlins_road/"
#define OKRA_AVENUE            GENUA_CITY + "okra_avenue/"
#define PARADISE_CRESCENT      GENUA_CITY + "paradise_crescent/"
#define PIRATE_AVENUE          GENUA_CITY + "pirate_avenue/"
#define QUEENS_DRAG            GENUA_CITY + "queens_drag/"
#define ROYAL_AVENUE           GENUA_CITY + "royal_avenue/"
#define RUE_EPHEBE             GENUA_CITY + "rue_ephebe/"
#define SAMEDI_CRESCENT        GENUA_CITY + "samedi_crescent/"
#define SAPPHIRE_STREET        GENUA_CITY + "sapphire_street/"
#define SAVANNAH_ROAD          GENUA_CITY + "savannah_road/"
#define SEWERS                 GENUA_CITY + "sewers/"
#define TACTICUS_ACADEMY       GENUA_CITY + "tacticus_academy/"
#define TACTICUS_ROAD          GENUA_CITY + "tacticus_road/"
#define TCHUTTIFRUITTI_STREET  GENUA_CITY + "tchuttifruitti_street/"
#define TRADE_STREET           GENUA_CITY + "trade_street/"
#define YAGA_CRESCENT          GENUA_CITY + "yaga_crescent/"
#define VIEUX_PROMENADE        GENUA_CITY + "vieux_promenade/"
#define VOODOO_LANE            GENUA_CITY + "voodoo_lane/"
#define WATCH_HOUSE            GENUA_CITY + "watch_house/"
#define ZOMBIE_WALK            GENUA_CITY + "zombie_walk/"
#define ABSINTHE_HOUSE         LIQUOR_ALLEY + "absinthe_house/"
#define BAYOU_BOURBON          LIQUOR_ALLEY + "bayou_bourbon/"
#define DAIQUIRY_DELIGHTS      LIQUOR_ALLEY + "daiquiry_delights/"
#define LA_MAISON_LIQUOR       LIQUOR_ALLEY + "la_maison_liquor/"
#define LADY_BROOK_LIQUOR      LIQUOR_ALLEY + "lady_brook_liquor/"
#define MADAME_DELIGHT         LIQUOR_ALLEY + "madame_delight/"
#define SALUT                  LIQUOR_ALLEY + "salut/"
#define BROCHURE               IDEAS + "brochure_text/"
#define CALYPSO_FLOWER_HANDLER (GENUA_HANDLERS + "calypso_blooms")
#define CASTLE_HANDLER         (GENUA_HANDLERS + "sleeping_castle_handler")
#define CHIVALRY_HANDLER       (GENUA_HANDLERS + "chivalry")
#define COMMON_ROOM            (FORN + "common")
#define GENUA_DOCKS_HANDLER    (GENUA_HANDLERS + "genua_docks_handler")
#define GENUA_EMBASSY          UTILS + "embassy/"
#define COFFEE_RUN             (GENUA_EMBASSY + "coffee_run/")
#define GENUA_HANDLER          (GENUA_HANDLERS + "general_genua_handler")
#define GENUA_LEDGER           (CRIME_HANDLER_DIR + "genua_ledger")
#define HAUNTING_HANDLER       (GENUA_HANDLERS + "haunting_handler")
#define COFFEE_NOSTRA          (GENUA_HANDLERS + "coffee_nostra")
#define INVENTORY              (GENUA_HANDLERS + "inventory_handler")
#define HOSPITAL               (HOSPITAL_DIR + "hospital")
#define INTERVIEW_ROOM         (UTILS + "interview")
#define ODD_JOBS               (GENUA_HANDLERS + "odd_jobs")
#define PACKAGE                (INHERITS + "package_inherit")
#define PEER_REVIEW            (HANDLERS + "peer_review")
#define PLAYTESTING_ROOM       (UTILS + "playtesting")
#define RUMOUR_MILL            (HANDLERS + "rumour_mill")
#define MURDER_MYSTERY         (GENUA_HANDLERS + "murder_mystery")
#define PRISON_CELL            (WATCH_HOUSE + "cell")
#define SCRIPT_INHERIT         (INHERITS + "scripting")
#define SPECIAL_INTEREST       (HANDLERS + "special_interest")
#define TRAINABLE_PET          (INHERITS + "trainable_pet")
#define WEB_HANDLER            (WEB + "misc/web_handler")
#define WHITEBOARD             (INHERITS + "whiteboard")
#define GENUA_DOLLAR 300
#define GENUA_CENT (GENUA_DOLLAR / 100)
#define GENUA_FORIN (GENUA_DOLLAR * 10)
#endif

==================================================
FILE: ftmoney.h
==================================================

#ifndef __SYS__FTMONEY
#define __SYS__FTMONEY
#define MONEY_OBJECT "/obj/money"
#define MONEY_HAND "/obj/handlers/money_handler"
#define MONEY_ALIAS "SomeMoneyForMe"
#endif

==================================================
FILE: ftp.h
==================================================

#ifndef __SYS__FTP
#define __SYS__FTP
#define FTP_PORT 4444
class dataconn {
  mixed data;
  string path;
  int pos;
  int parent_fd;
  int type;
  int len;
  int append;
}
class session {
  int fd;
  string user_name;
  int logged_in;
  string cwd;
  string data_addr;
  int last_data;
  int data_port;
  int data_fd;
  int type;
  int idle;
  string rnfr;
  int offset;
  int use_default;
  int pasv_fd;
  int pasv_cb;
}
#define STRING 1
#define FILE 2
#define DOWNLOAD 3
#define BINARY 4
#define MASK_L  1
#define MASK_C  2
#define MASK_F  4
#define MASK_A  8
#define MASK_R 16
#define MASK_D 32
#define TP_CRE "turrican"
#undef DEBUG
#ifdef DEBUG
#define TP(STR) if (find_player(TP_CRE)) \
                    tell_object(find_player(TP_CRE), STR)
#define DEBUG_SEND
#define DEBUG_RECEIVE
#else
#define TP(STR)
#undef DEBUG_SEND
#undef DEBUG_RECEIVE
#endif
#define LOGGING
#ifdef LOGGING
#define LOG_CONNECT
#define LOG_FILE
#define LOG_CD_SIZE
#define LOG_DEBUG
#define LOG_FILENAME "/d/admin/log/FTPD.log"
#else
#undef LOG_CONNECT
#undef LOG_FILE
#undef LOG_CD_SIZE
#undef LOG_DEBUG
#endif
#define BLOCK_SIZE 65536
#define NEWDRIVER
#ifdef __VERSION__
#define VERSION __VERSION__
#else
#ifndef VERSION
#define VERSION version()
#endif
#endif
#define CHECK_LOGIN() if (!sess->logged_in) \
                      { \
                        eventWrite(fd, "530 Please login with USER and PASS.\r\n"); \
                        break; \
                      }
#define CHECK_CMD(INT) if (sizeof(bits) != INT+1) \
                       { \
                         eventWrite(fd, sprintf("500 '%s': command not understood.\r\n", \
                            str)); \
                         break; \
                       }
#define CHECK_CMD2(INT,INT2) if (sizeof(bits) < INT+1 ||\
                                 sizeof(bits) > INT2+1) \
                       { \
                         eventWrite(fd, sprintf("500 '%s': command not understood.\r\n", \
                            str)); \
                         break; \
                       }
#define CHECK_PLAYER() if (sess->logged_in == 2) \
                       { \
                         eventWrite(fd, "553 Permission denied (you are not a creator)\r\n"); \
                         break; \
                       }
#define CHECK_STRING sess->type == STRING
#define UNAME sess->user_name
#define HOME_DIR(NAME) "/w/"+NAME
protected void setup_ftp();
protected string get_path(int fd, string str);
protected void do_update(string name, int fd);
protected void data_write_callback(int fd);
mapping cmdtab = ([
    "user" : ({ "USER", 1, "<sp> username" }),
    "pass" : ({ "PASS", 1, "<sp> password" }),
    "acct" : ({ "ACCT", 0, "(specify account)" }),
    "smnt" : ({ "SMNT", 0, "(structure mount)" }),
    "rein" : ({ "REIN", 0, "(reinitialize server state)" }),
    "quit" : ({ "QUIT", 1, "(terminate service)", }),
    "port" : ({ "PORT", 1, "<sp> b0, b1, b2, b3, b4" }),
    "pasv" : ({ "PASV", 0, "(set server in passive mode)" }),
    "type" : ({ "TYPE", 1, "<sp> [ A | E | I | L ]" }),
    "stru" : ({ "STRU", 0, "(specify file structure)" }),
    "mode" : ({ "MODE", 0, "(specify transfer mode)" }),
    "retr" : ({ "RETR", 1, "<sp> file-name" }),
    "stor" : ({ "STOR", 1, "<sp> file-name" }),
    "appe" : ({ "APPE", 1, "<sp> file-name" }),
    "mlfl" : ({ "MLFL", 0, "(mail file)" }),
    "mail" : ({ "MAIL", 0, "(mail to user)" }),
    "msnd" : ({ "MSND", 0, "(mail send to terminal)" }),
    "msom" : ({ "MSOM", 0, "(mail send to terminal or mailbox)" }),
    "msam" : ({ "MSAM", 0, "(mail send to terminal and mailbox)" }),
    "mrsq" : ({ "MRSQ", 0, "(mail recipient scheme question)" }),
    "mrcp" : ({ "MRCP", 0, "(mail recipient)" }),
    "allo" : ({ "ALLO", 1, "allocate storage (vacuously)" }),
    "rest" : ({ "REST", 1, "(restart command)" }),
    "rnfr" : ({ "RNFR", 1, "<sp> file-name" }),
    "rnto" : ({ "RNTO", 1, "<sp> file-name" }),
    "abor" : ({ "ABOR", 1, "(abort operation)" }),
    "dele" : ({ "DELE", 1, "<sp> file-name" }),
    "cwd"  : ({ "CWD" , 1, "[ <sp> directory-name ]" }),
    "xcwd" : ({ "XCWD", 1, "[ <sp> directory-name ]" }),
    "list" : ({ "LIST", 1, "[ <sp> path-name ]" }),
    "nlst" : ({ "NLST", 1, "[ <sp> path-name ]" }),
    "site" : ({ "SITE", 1, "site-cmd [ <sp> arguments ]" }),
    "syst" : ({ "SYST", 1, "(get type of operating system)" }),
    "stat" : ({ "STAT", 1, "[ <sp> path-name ]" }),
    "help" : ({ "HELP", 1, "[ <sp> <string> ]" }),
    "noop" : ({ "NOOP", 1, "" }),
    "mkd"  : ({ "MKD" , 1, "<sp> path-name" }),
    "xmkd" : ({ "XMKD", 1, "<sp> path-name" }),
    "rmd"  : ({ "RMD" , 1, "<sp> path-name" }),
    "xrmd" : ({ "XRMD", 1, "<sp> path-name" }),
    "pwd"  : ({ "PWD" , 1, "(return current directory)" }),
    "xpwd" : ({ "XPWD", 1, "(return current directory)" }),
    "cdup" : ({ "CDUP", 1, "(change to parent directory)" }),
    "xcup" : ({ "XCUP", 1, "(change to parent directory)" }),
    "stou" : ({ "STOU", 0, "<sp> file-name" }),
    "size" : ({ "SIZE", 1, "<sp> path-name" }),
    "mdtm" : ({ "MDTM", 1, "<sp> path-name" })
]);
mapping sitecmdtab = ([
    "idle"  : ({ "IDLE",  1, "[ <sp> timeout ]" }),
    "help"  : ({ "HELP",  1, "[ <sp> <string> ]" }),
    "newer" : ({ "NEWER", 0, "<sp> YYYYMMDDHHMMSS [ <sp> path-name ]" }),
    "minfo" : ({ "MINFO", 0, "<sp> YYYYMMDDHHMMSS [ <sp> path-name ]" }),
    "time"  : ({ "TIME",  1, "(prints local time)" }),
    "upd"   : ({ "UPD",   1, "<sp> path-name" })
]);
#define FTP_VERSION "Version 13.2"
#define LOGIN_OB "/secure/login"
#endif

==================================================
FILE: fuel_handler.h
==================================================

#define FUEL_TIME 15
#define FUEL_HANDLER "/obj/handlers/fuel_handler"

==================================================
FILE: function.h
==================================================

#define FP_LOCAL              2
#define FP_EFUN               3
#define FP_SIMUL              4
#define FP_FUNCTIONAL         5
#define FP_G_VAR              6
#define FP_L_VAR              7
#define FP_ANONYMOUS          8
#define FP_THIS_OBJECT      0x10
#define FP_MASK             0x0f
#define FP_HAS_ARGUMENTS    0x10
#define FP_OWNER_DESTED     0x20
#define FP_NOT_BINDABLE     0x40

==================================================
FILE: gag.h
==================================================

#define PATH "/obj/misc/"

==================================================
FILE: goal.h
==================================================

#ifndef __SYS__GOAL
#define __SYS__GOAL
#define EVENT_HANDLED 5
#define EVENT_NOT_HANDLED 6
#define EVENT_PARTIALLY_HANDLED 7
#define EVENT_USED 8
#define SET_GOAL_ARG 9
#define GOAL_ACHIEVED 10
#endif

==================================================
FILE: good_fighter.h
==================================================

#define GOOD_FIGHTER "/std/effects/npc/good_fighter"
#define USE_UNARMED 16
#define USE_BLUNT 12
#define USE_SHARP 8
#define USE_PIERCE 4
#define USE_BALANCED 0
#define USE_mask 28
#define DEFEND_DODGE 2
#define DEFEND_PARRY 1
#define DEFEND_BALANCED 0
#define DEFEND_mask 3

==================================================
FILE: gossip.h
==================================================

#ifndef __GOSSIP_H
#define __GOSSIP_H
#define GOSSIP_HANDLER "/obj/handlers/gossip_handler"
#define GOSSIP_KEEP_LEVEL 50
#define RUMOUR_KEEP_LEVEL 20
#define GOSSIP_SAVE_FILE "/save/gossip"
#endif

==================================================
FILE: group_handler.h
==================================================

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

==================================================
FILE: guide_places.h
==================================================

string *guilds = ({
  "fish",
    "/d/am/cockbill/cockbill8",
      "the Temple of Fish",
  "small gods",
    "/d/guilds/priests/Ankh-Morpork/small-gods/entrance",
      "the Temple of the Small Gods",
  "warrior",
    "/d/am/hero/lobby",
      "the Warriors' Guild",
  "wizard",
    "/d/am/square/ss13",
      "the Unseen University",
  "university",
    "/d/am/square/ss13",
      "the Unseen University",
  "assassin",
    "/d/guilds/assassins/Ankh-Morpork/admin/foyer",
      "the Assassins' Guild",
  "thief",
    "/d/guilds/thieves/Ankh-Morpork/rooms/ground/entrance",
      "the Thieves' Guild",
  "thieves",
    "/d/guilds/thieves/Ankh-Morpork/rooms/ground/entrance",
      "the Thieves' Guild",
  "gennie",
    "/d/guilds/witches/Ankh-Morpork/gennies_cottage",
      "Gennie's place"});
string *services = ({
  "drum",
    "/d/am/am/mendeddrum",
      "the Mended Drum",
  "bank",
    "/d/am/broad_way/bing_bank",
      "the Bank of Bing",
  "post",
    "/d/am/ampost/foyer",
      "the Post Office",
   "sator stall",
     "/d/guilds/merchants/stalls/am/sator",
     "the Sator Square player stall",
   "cockbill stall",
     "/d/guilds/merchants/stalls/am/cockbill",
      "the Cockbill Street player stall",
  "patrician",
    "/d/am/patrician/foyer",
      "the Patrician's Palace"});
string *places = ({
  "sator square",
    "/d/am/square/ss33",
      "Sator Square",
  "least gate",
    "/d/am/gates/least",
      "the Least Gate",
  "brass bridge",
    "/d/am/river/bridge",
      "the Brass Bridge",
  "widdershins gate",
    "/d/am/gates/widdershins",
      "the Widdenshins Gate",
  "cockbill",
    "/d/am/cockbill/cockbill1",
      "Cockbill Street",
  "plaza",
    "/d/am/plaza/plaza_33",
      "the Plaza of Broken Moons",
  "hubward",
    "/d/am/gates/hubwards",
      "the Hubwards Gate",
  "pillory",
    "/d/am/pillory/pillory2",
      "Pillory Place",
  "ninth yard",
    "/d/am/ninth/ninth1",
      "Ninth Yard"});

==================================================
FILE: guilds.h
==================================================

#ifndef INCLUDE_GUILDS
#define INCLUDE_GUILDS
#define GUILDS "/d/guilds/"
#define GUILDSAVE "/save/guilds/"
#define PLAYER_GUILDS ({ "assassins", "priests", "thieves", "warriors", "witches", "wizards" })
#define POSITION_OK 0
#define POSITION_FAIL 1
#define POSITION_TOO_MANY 2
#define POSITION_ALREADY_APPOINTED 3
#endif

==================================================
FILE: hospital.h
==================================================

#ifndef __STD_HOSPITAL_H
#define __STD_HOSPITAL_H
#define HOSPITAL_ALIGNMENT_INHERIT "/std/hospital/alignment"
#define REGEN_TIME (1 * 60 * 60)
#define DEFAULT_MAX_CACHE 10
#define DEFAULT_LOG_DIRECTORY "/log"
#define DEFAULT_POPULATION 3
#define MINIMUM_DEATH_REGEN 3
#define POPULATION_UPDATE_TIME 15 * 60
class regenerated_npc {
    string type;
    string load_position;
}
class zone_info {
   int wealth;
   int busy;
   int npc_chance;
   mapping npcs;
   int group_chance;
   mapping groups;
   int zone_chance;
   mapping zones;
}
class unique_npc {
   int next_regen_time;
}
class npc_info {
   string path;
   int unique;
   int delay;
   int transient;
   int nocturnal;
   int diurnal;
   string* seasonal;
   int max_population;
   string* move_zones;
   string* commands;
   object* population;
   int no_deaths;
   int no_created;
   int no_reused;
   int next_update;
}
class group_info {
   string* move_zones;
   mapping npcs;
   mapping npc_commands;
   int protect;
   int defend;
   int transient;
   int max_population;
   mixed* storage;
   int no_creates;
   int next_update;
}
#define MONSTER "/obj/monster"
#define MAX_NAMED_LIVING 600
#define MAX_AM_LIVING 450
#define MAX_DJEL_LIVING 100
#endif

==================================================
FILE: housing.h
==================================================

#ifndef __SYS__HOUSING
#define __SYS__HOUSING
#define HOUSING "/obj/handlers/housing"
#define AGREEMENT "/obj/misc/agreement"
#define BOOK "/obj/misc/home_owners_guide"
#define SALE 0
#define RENT 1
#define LEASE 2
#define OWNER_TIMEOUT 11520000
#define RENTER_TIMEOUT  5760000
#define DEFAULT_LEASE 23040000
#define GET_COMMANDS ({"get", "take", "drag", "palm", "gather", "order", "grab", "ask"})
#endif

==================================================
FILE: http.h
==================================================

#ifndef __HTTP_H
#define __HTTP_H
#include <mime.h>
#define HTTPD "/net/daemon/http"
#define HTTP_PROTOCOL "HTTP/1.1"
#define HTTP_VERSION "Discworld/0.10.3"
#define HTTP_ACCEPT_ENCODING "accept-encoding"
#define HTTP_CODING_TYPE "Content-Encoding"
#define REQ_REQUEST 0
#define REQ_HEADERS 1
#define REQ_BODY 2
#define BODY_START 0
#define BODY_READ 1
#define BODY_CHUNK_FOOTER 2
#define BODY_CHUNK_END 3
#define DIR_WWW "/www"
#define CONTINUE 100
#define HTTP_OK 200
#define NO_CONTENT 204
#define PARTIAL_CONTENT 206
#define MOVED_PERMANENTLY 301
#define MOVED_TEMP 302
#define NOT_MODIFIED 304
#define BAD_CMD 400
#define AUTH_REQUIRED 401
#define ACCESS_DENIED 403
#define NOT_FOUND 404
#define NOT_ALLOWED 405
#define TIME_OUT 408
#define LENGTH_REQUIRED 411
#define PRECONDITION_FAILED 412
#define INTERNAL_ERROR 500
#define NOT_IMPLEMENTED 501
nosave private mapping status_lines = ([
   100 : "100 Continue",
   101 : "101 Switching Protocols",
   200 : "200 OK",
   201 : "201 Created",
   202 : "202 Accepted",
   203 : "203 Non-Authoritative Information",
   204 : "204 No Content",
   205 : "205 Reset Content",
   206 : "206 Partial Content",
   300 : "300 Multiple Choices",
   301 : "301 Moved Permanently",
   302 : "302 Moved Temporarily",
   303 : "303 See Other",
   304 : "304 Not Modified",
   305 : "305 Use Proxy",
   400 : "400 Bad Request",
   401 : "401 Authorization Required",
   402 : "402 Payment Required",
   403 : "403 Forbidden",
   404 : "404 File Not Found",
   405 : "405 Method Not Allowed",
   406 : "406 Not Acceptable",
   407 : "407 Proxy Authentication Required",
   408 : "408 Request Time-out",
   409 : "409 Conflict",
   410 : "410 Gone",
   411 : "411 Length Required",
   412 : "412 Precondition Failed",
   413 : "413 Request Entity Too Large",
   414 : "414 Request-URI Too Large",
   415 : "415 Unsupported Media Type",
   500 : "500 Internal Server Error",
   501 : "501 Method Not Implemented",
   502 : "502 Bad Gateway",
   503 : "503 Service Temporarily Unavailable",
   504 : "504 Gateway Time-out",
   505 : "505 HTTP Version Not Supported",
   506 : "506 Variant Also Varies"
]);
#define SAVE_FILE "/net/save/http"
#define status_drops_connection(x) (((x) == BAD_CMD)          || \
                                    ((x) == TIME_OUT)         || \
                                    ((x) == INTERNAL_ERROR)   || \
                                    ((x) == LENGTH_REQUIRED))
#undef DEBUG
#ifdef DEBUG
#define TP(STR) if (find_player("ceres")) tell_object(find_player("ceres"), STR)
#else
#define TP(STR)
#endif
#define RES_DIR    0
#define RES_FILE   1
#define RES_NORMAL 2
#define DAYS ({"Sun", "Mon", "Tue", "Wed", "Thu", \
         "Fri", "Sat"})
#define MONTHS ({"Jan", "Feb", "Mar", "Apr", "May", "Jun", \
     "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"})
class http_session {
  int fd;
  int time;
  string address;
  string name;
}
class http_body {
  int state;
  int remaining;
  int read_chunked;
  int read_length;
  string buff;
  mapping data;
}
class http_request_header {
  int noheaders;
  class mime_header headers_in;
  class mime_header headers_out;
  class mime_header err_headers_out;
  int header_only;
}
class http_body_info {
  string content_type;
  int chunked;
  int clength;
  int byterange;
  string boundary;
  string range;
}
class http_request {
  class http_session sess;
  string hostname;
  int time;
  string request;
  string status_line;
  int status;
  int proto_num;
  string method;
  string uri;
  string args;
  string filename;
  string dir;
  string user;
  class http_request_header rh;
  string location;
  int id;
  string the_request;
  int state;
  int persistent;
  string compression;
  int proxyreq;
  int numredirect;
  int cgi_request;
  class http_body body;
  class http_body_info bi;
  class http_request prev;
  int delayed;
}
#endif

==================================================
FILE: image.h
==================================================

class IMAGE_INFO {
  mixed image;
  int rle;
  int *size;
  int *nw_coord;
}
#define IMAGE_HANDLER "/d/sur/beta/topography/image"

==================================================
FILE: imap4.h
==================================================

#ifndef __IMAP4_H
#define __IMAP4_H
#define PORT_IMAP4 1143
#define IMAP4_VERSION "0.1"
#define IMAP_CONNECTED   0
#define IMAP_AUTHENTICATED   1
#define IMAP_SELECTED 2
#define LOGIN_OB "/secure/login"
#define FOLDER_H "/obj/handlers/folder_handler"
#define DEBUG
#ifdef DEBUG
#define TP(_x) tell_object(find_player("ceres"), (_x))
#else
#define TP(_x)
#endif
#define CHECK_STATE(_state) if ((_state) != sess->state) \
{ \
    eventWrite(fd, sprintf("* BAD Unknown command in %s state\r\n", \
                           imap_states[sess->state])); \
    break; \
}
#define CHECK_CMD(_num, _str) if (sizeof(bits) < (_num)+2) \
                       { \
                         eventWrite(fd, _str); \
                         break; \
                       }
class imap_session {
  int fd;
  int state;
  int time;
  string user_name;
	string selected;
	string command;
  int *deleted;
  int num_messages;
  class mail_header *headers;
  string *messages;
  int *sizes;
  int last;
}
#endif

==================================================
FILE: inet.h
==================================================

#ifndef __SYS__INET
#define __SYS__INET
#define INETD "/net/inetd"
#define NAMESERVER "/net/nameserver"
#include "comms.h"
#define CLONE_DEMON
#define INTERCREATORD "/net/daemon/out_intercreator"
#endif

==================================================
FILE: inhume.h
==================================================

#ifndef __SYS__INHUME
#define __SYS__INHUME
#ifdef LOG
#undef LOG
#endif
#undef DEBUG
#define INHUME "/obj/handlers/secure_handlers/inhume"
#define NO_INHUME_PROP  "cannot inhume"
#define NO_CONTRACT_PROP "cannot place contracts"
#define LOGDIR          "/log/secure/assassins/"
#define LOG             ( LOGDIR + "INHUME" )
#define INHUMED         ( LOGDIR + "INHUMED" )
#define RECEIPTS        ( LOGDIR + "INHUME_RECEIPTS" )
#define LOGFILE         ( LOGDIR + "inhume_debug" )
#define PLAY_LOG        ( LOGDIR + "play_inhume_debug" )
#define TM_LOG          ( LOGDIR + "INHUME_TMS" )
#define NPC_LOG         ( LOGDIR + "NPC_CONTRACTS" )
#define CONTRACT_NO_LOCATION 10
class contract {
   int status;
   string bastard;
   int value;
   int time;
   int reveal;
   string message;
   string name;
   string place;
   int nodeath;
   string originator;
   string location;
}
#define EXP_TIME   2419200
#define TAXES      40
#define SURCHARGE  10
#define NOTME_MULT 1.1
#define MIN_LEVEL  50
#define PK_MULT    0
#define COST_MULT  ( 5 * 400 )
#define COST_GUILD ( 6 * 400 )
#define MAXTIMES 4
#define NO_DEATH_MULT 0.5
#define LOW          -1
#define NON_KILLER   -2
#define CRE          -3
#define TOO_SOON     -4
#define REQUESTED 0
#define VALIDATED 1
#define INFORMED 2
#define ACTIVE 3
#define SPECIAL 4
#define INHUME_COLLECT_NONE   0
#define INHUME_COLLECT_REFUND 1
#define INHUME_COLLECT_WAGES  2
#define INHUME_COLLECT_MIXED  3
#define INHUME_PK_THRESH_GUILD_LEVEL   175
#define INHUME_PK_THRESH_NUM_CONTRACTS 4
#define INHUME_PK_THRESH_AGE_DAYS      10
#define REPEAT_RATE ( 60 * 60 * 24 * 7 * 2 )
#define NPC_TIME ( 60 * 60 * 24 * 7 * 2 )
#define INHUME_ON_SIGHT_THRESH 10
#define INHUME_CRIME_EXPIRY_TIME ( 60 * 60 * 24 * 3 )
#define INHUME_NPC_WAIT_TIME ( 60 * 60 * 12 )
#endif

==================================================
FILE: language.h
==================================================

#ifndef __SYS__LANGUAGE
#define __SYS__LANGUAGE
#define LANGUAGES "/obj/handlers/languages"
#define LANGUAGE_HAND "/obj/handlers/languages"
#define LANGUAGE_INHERIT "/std/languages/language_inherit"
#define L_SPOKEN 1
#define L_WRITTEN 2
#define L_DISTANCE 4
#define L_MAGIC 8
#define L_SIZED 16
#define L_ALWAYS_SPEAK 32
#define READ_MESS 0
#define READ_STR 0
#define READ_TYPE 1
#define READ_LANG 2
#define READ_SIZE 3
#define SAY_TYPE "say"
#define WHISPER_TYPE "whisper"
#define SHOUT_TYPE "shout"
#define TELL_TYPE "tell"
#define LANGUAGE_SKILL_START "other.language."
#define SPOKEN_SKILL "spoken"
#define WRITTEN_SKILL "written"
#define NO_MESSAGE 0
#define NOT_SPOKEN 1
#define NOT_KNOWN 2
#define NOT_DISTANCE 3
#define MESSAGE_OK 4
#endif

==================================================
FILE: learning.h
==================================================

#define CURRENT_LORD "Wodan"
#define DOM_TITLE "the domain of learning"
#define DOMAIN "learning"
#define LEARNING "/d/learning/"
#define HELP LEARNING +"help_topics/"
#define FUNCTIONS LEARNING +"functions/"
#define SAVEPATH LEARNING +"save/"
#define CHARS LEARNING + "chars/"
#define ENTRANCE (LEARNING +"main")
#define SEARCH_ROOM (LEARNING +"search_room")
#define FUNCTION_ROOM (LEARNING +"function_room")
#define SEARCH (LEARNING +"handlers/search")
#define QUIT_HANDLER (LEARNING +"handlers/quit")
#define TTOWN (LEARNING +"TinyTown/")
#define TTOWNBUILDINGS (TTOWN +"buildings/")
#define TTOWNITEMS (TTOWN +"items/")
#define TTOWNCHARS (TTOWN +"chars/")
#define TTOWNROADS (TTOWN +"roads/")
#define TTOWNHOSPITAL (TTOWN +"hospital")

==================================================
FILE: liaison.h
==================================================

#ifndef __LIAISON_H
#define __LIAISON_H
#define LIAISON                "/d/liaison/"
#define LIAISON_MASTER         LIAISON + "master"
#define HANDLERS               LIAISON + "handlers/"
#define HELPERS                LIAISON + "helpers/"
#define IDEAS                  LIAISON + "ideas/"
#define ITEMS                  LIAISON + "items/"
#define NEWBIE                 LIAISON + "NEWBIE/"
#define SECURE                 LIAISON + "secure/"
#define TOYS                   LIAISON + "TOYS/"
#define UTILS                  LIAISON + "utils/"
#define WEB                    LIAISON + "public_html/"
#define SAVE_DIR               "/save/"
#define SAVE                   SAVE_DIR + "liaison/"
#define LIAISON_DOMAIN_INFO    SECURE + "domain_info.txt"
#define DOC_DIR                "/doc/creator/liaison/"
#define POLICY                 DOC_DIR + "policy/"
#define NEWBIE_CREATOR         NEWBIE + "CREATOR/"
#define NEWBIE_CHARS           NEWBIE + "chars/"
#define NEWBIE_DOC             NEWBIE + "doc/"
#define NEWBIE_ITEMS           ITEMS + "NEWBIE/"
#define NEWBIE_SAVE            NEWBIE + "save/"
#define TOYS_IDEAS             TOYS + "ideas/"
#endif

==================================================
FILE: library.h
==================================================

#ifndef __SYS__LIBRARY
#define __SYS__LIBRARY
#define LIBRARY "/obj/handlers/library"
#endif

==================================================
FILE: living.h
==================================================

#ifndef __SYS__LIVING
#define __SYS__LIVING
#define PASSED_OUT "passed out"
#define TRANCE "trance"
#define UNKNOWN_MOVE "unknown move"
#define RUNNING_MOVE "running move"
#define MAX_INVEN 10
#define MAX_CREATOR_INVEN 25
#define WILL_POWER 338
#define MIN_TIMES 20
#define GP_ADVANCE_MOD 5
#define OUT_COLD 1
#define ASLEEP 2
class living_nationality {
   string nationality;
   string region;
   mixed data;
}
#endif

==================================================
FILE: localtime.h
==================================================

#define LT_SEC          0
#define LT_MIN          1
#define LT_HOUR         2
#define LT_MDAY         3
#define LT_MON          4
#define LT_YEAR         5
#define LT_WDAY         6
#define LT_YDAY         7
#define LT_GMTOFF       8
#define LT_ZONE         9

==================================================
FILE: log.h
==================================================

#ifndef __SYS__LOG
#define __SYS__LOG
#define ERROR_LOG "ERROR_REPORTS"
#define PLAYER_ERROR_LOG "BUGS"
#define LOG_FILE "/log/ERRORS"
#define TEMP_MAIL_LIST ("/w/" + this_player()->query_name() + "/TEMP_MAIL_LIST")
#define TEMP_FORWARD_LIST ("/w/" + this_player()->query_name() + "/TEMP_FORWARD_LIST")
#define SMART_LOG "/std/smart_log"
#define WWW_TEMP_MAIL_LIST "/w/" + user + "/TEMP_MAIL_LIST"
#define WWW_TEMP_FORWARD_LIST "/w/" + user + "/TEMP_FORWARD_LIST"
#endif

==================================================
FILE: login.h
==================================================

#include <login_handler.h>
#define LOGIN_OB "/secure/login"

==================================================
FILE: login_handler.h
==================================================

#ifndef __SYS__LOGIN_HANDLER
#define __SYS__LOGIN_HANDLER
#include <player_handler.h>
#define LOGIN_HANDLER "/obj/handlers/login_handler"
#define LOGIN "login"
#define LOGOUT "logout"
#define NETDEATH "netdeath"
#define RECONNECT "reconnect"
#define MAX_COMPRESSED_PLAYERS 200
#define MAX_UNCOMPRESSED_PLAYERS 100
#define MAX_PLAYERS (MAX_COMPRESSED_PLAYERS + MAX_UNCOMPRESSED_PLAYERS)
#define WITHOUT_LOGINS_NOT_IN_QUEUE 3
#define WITHOUT_ANY_LOGINS 2
#define WITHOUT_LOGIN_QUEUE 1
#define WITH_LOGIN_QUEUE    0
#define DISCWORLD_IS_EMPTY 0
#define COMPRESSED_FULL 1
#define UNCOMPRESSED_FULL 2
#define DISCWORLD_IS_FULL (COMPRESSED_FULL | TELNET_FULL)
#endif

==================================================
FILE: ls.h
==================================================

#ifndef __LS_H
#define __LS_H
#define MASK_L 1
#define MASK_C 2
#define MASK_F 4
#define MASK_A 8
#define MASK_D 16
#define MASK_O 32
#define MASK_T 64
#define LS_COMMAND_NICKNAME_PROPERTY "expand ls nicknames"
#endif

==================================================
FILE: mail.h
==================================================

#ifndef __SYS__MAIL
#define __SYS__MAIL
#ifndef __MAIL_H_NO_CLASSES
class mail_header {
  int number;
  string status;
  string subject;
  string from;
}
class mail_message {
  string *to;
  string *cc;
  string body;
  string from;
  string subject;
}
#endif
#define DAYS ({"Sun", "Mon", "Tue", "Wed", "Thu", \
               "Fri", "Sat"})
#define MONTHS ({"Jan", "Feb", "Mar", "Apr", "May", "Jun", \
     "Jul", "Aug", "Sep", "Oct", "Nov", \
     "Dec"})
#define MAIL_TRACK "/obj/handlers/mail_track"
#define MAILER "/obj/handlers/mailer"
#define AUTO_MAILER "/global/auto_mailer"
#define OUT_MAIL "/net/daemon/out_mail"
#define POST_FROG "/obj/monster/post_frog"
#define FROG_HOME "/d/am/buildings/post/mailing"
#define SMTP "/net/obj/smtp"
#define EXTERNAL_MAIL_PATH "/secure/mail/incoming/"
#define MAIL_PARCEL_HANDLER "/obj/handlers/parcel"
#define MAX_FOLDER_SIZE 250
#define WARN_FOLDER_SIZE 100
#endif

==================================================
FILE: mail_track.h
==================================================

#ifndef __SYS__MAIL_TRACK
#define __SYS__MAIL_TRACK
class mailing_list {
  string *members;
  string *controllers;
  string creator;
}
#define MAIL_ROOM "/d/admin/room/mail_room"
#endif

==================================================
FILE: map.h
==================================================

#define MAP "/obj/handlers/map"
#define MAP_HANDLER "/obj/handlers/map"

==================================================
FILE: map_handler.h
==================================================

#define MH "/obj/handlers/map_helper"
#define MAP_HANDLER "/obj/handlers/map"
#define SIZE 0
#define TIME 1
#define LOAD 2
#define DESTINATION 0
#define EXIT_SIZE 1
#define EXIT_TYPE 2
#define OFFSET    3
#define CACHESIZE 60
#define SKEWTIME 4
#undef LOGTO "olorin"
#undef HELPLOGTO "ceres"
#define COORDS 1
#undef PARANOID
#define LOG_EXITS 1
#define LOG_SHORTS 1
#ifdef LOGTO
#define LOG(X) \
if ( find_living( LOGTO ) ) \
  tell_object( find_living( LOGTO ), X )
#else
#define LOG(X)
#endif

==================================================
FILE: merchant.h
==================================================

#define MERCHANT "/d/guilds/merchants"
#define STALL MERCHANT+"/stalls/"
#define SHOPS MERCHANT+"/shops/"
#define MERCHANT_GUILD MERCHANT+"/guild/"
#define MERCHANT_CHARS MERCHANT+"/chars/"
#define MERCHANT_ITEMS MERCHANT+"/items/"
#define MERCHANT_SAVE MERCHANT+"/save/"
#define MERCHANT_STD MERCHANT+"/std/"

==================================================
FILE: mime.h
==================================================

#ifndef __MIME_H
#define __MIME_H
#define MIME "/obj/handlers/mime"
#define isspace(c) (((c) == ' ') || ((c) == '\t') || ((c) == '\n') || \
                    ((c) == 12) || ((c) == '\r') || ((c) == 11))
#define iscntrl(c) (((c) == 127) || (((c) >= 0) && ((c) <= 31)))
#define isxdigit(c) ((((c) >= 'A') && ((c) <= 'F')) || \
                     (((c) >= 'a') && ((c) <= 'f')) || \
                     (((c) >= '0') && ((c) <= '9')))
#define isalnum(c) ((((c) >= '0') && ((c) <= '9')) || \
                    (((c) >= 'A') && ((c) <= 'Z')) || \
                    (((c) >= 'a') && ((c) <= 'z')))
#define isdigit(c) (((c) >= '0') && ((c) <= '9'))
class mime_header {
  mapping header_m;
  string *header_k;
}
#endif

==================================================
FILE: mineral.h
==================================================

#ifndef __SYS__MINERAL
#define __SYS__MINERAL
#define PEBBLE 5
#define STONE 20
#define ROCK 1000
#define MINERAL "/obj/mineral"
#endif

==================================================
FILE: mission.h
==================================================

#ifndef __SYS__MISSION
#define __SYS__MISSION
#define NOT_SUITABLE 4
#define TOO_HIGH 3
#define JUST_RIGHT 2
#define TOO_LOW 1
#endif

==================================================
FILE: money.h
==================================================

#ifndef __SYS__MONEY
#define __SYS__MONEY
#include <shops/bank.h>
#define MONEY_OBJECT "/obj/money"
#define MONEY_HAND "/obj/handlers/money_handler"
#define MONEY_ALIAS "Some Money For Me"
#define NO_MATCH -1
#define NO_MONEY -2
#define NO_LEGAL -3
#define MONEY_VAULT "/room/vault"
#define MONEY_PAY_CHANGE 1
#define MONEY_PAY_RETURN 0
#define MONEY_PAY_DEPLETED 2
#define MONEY_DETAILS_HEADS 0
#define MONEY_DETAILS_TAILS 1
#define MONEY_DETAILS_REVERSE 2
#define MONEY_DETAILS_OBVERSE 3
#define MONEY_DETAILS_COMPOSITION 4
#define MONEY_DETAILS_PLURAL 5
#endif

==================================================
FILE: monster.h
==================================================

#ifndef __SYS__MONSTER
#define __SYS__MONSTER
#define RACE_OB "/std/race"
#define MONSTER_HAND "/obj/handlers/monster_handler"
#endif

==================================================
FILE: move_failures.h
==================================================

#ifndef __SYS__MOVE_FAILURES
#define __SYS__MOVE_FAILURES
#define MOVE_OK 0
#define MOVE_EMPTY_DEST 1
#define MOVE_NO_GET 2
#define MOVE_NO_DROP 3
#define MOVE_TOO_HEAVY 4
#define MOVE_INVALID_DEST 5
#define MOVE_NO_UNHOLD 6
#endif

==================================================
FILE: mudwho.h
==================================================

#ifndef __SYS__MUDWHO
#define __SYS__MUDWHO
#define CMWHOD "/net/daemon/cmwhod"
#endif

==================================================
FILE: nameserver.h
==================================================

#ifndef __SYS__NAMESERVER
#define __SYS__NAMESERVER
#define NAME_D "/net/nameserver"
#define INET_D "/net/inetd"
#endif

==================================================
FILE: network.h
==================================================

#ifndef __NETWORK_H
#define __NETWORK_H
#include <socket_errors.h>
#define MUD                       0
#define STREAM                    1
#define DATAGRAM                  2
#define STREAM_BINARY             3
#define DATAGRAM_BINARY           4
#define PORT_MUD (mud_name() == "Discworld") ? 23 : 6677
#define PORT_FTP (mud_name() == "Discworld") ? 21 : 4444
#define PORT_HTTP                 80
#define PORT_INTERNAL_HTTP                  5678
#define PORT_OOB                  8765
#define PORT_FTPAUTH              2227
#undef  PORT_RCP
#undef  PORT_UDP
#define CLIENT                    "/net/inherit/client"
#define SERVER                    "/net/inherit/server"
#define INTERMUD_D                "/net/intermud3/intermud"
#define SERVICES_D                "/net/intermud3/services"
#define OOB_D                     "/net/intermud3/oob_server"
#define NETWORK_DICTIONARY_HANDLER "/net/daemon/dictionary"
#define NETWORK_SUCCESS 0
#define MUDLIB_VERSION "Discworld 17.0a"
#define ADMIN_ADDRESS (mud_name() == "Discworld") ? "trustees@discworld.imaginary.com" : "none"
#define STATUS (mud_name() == "Discworld") ? "open for players" : "Development"
#endif

==================================================
FILE: newbiehelpers.h
==================================================

#ifndef __NEWBIEHELPERS_H
#define __NEWBIEHELPERS_H
#define NEWBIEHELPERS_HANDLER            "/obj/handlers/newbiehelpers"
#endif

==================================================
FILE: newudp.h
==================================================

#ifndef __SYS__NEWUDP
#define __SYS__NEWUDP
#ifndef __NEWUDP_H
#define __NEWUDP_H
#ifdef __UDP_H
#define NEW_INETD "/net/intermud/inetd"
#else
#define INETD		"/net/intermud/inetd"
#endif
#define UDP_CMD_DIR	"/net/intermud/udp/"
#define HOST_FILE	"/net/intermud/adm/INETD_HOSTS"
#define INETD_LOG_FILE	"INETD"
#define REPLY_TIME_OUT	12
#define RETRIES		2
#define LOCAL_NAME	MUD_NAME
#define LOCAL_UDP_PORT 5756
#define INETD_DIAGNOSTICS
#define INETD_VERSION	"0.61"
#define RECIPIENT	"RCPNT"
#define REQUEST		"REQ"
#define SENDER		"SND"
#define DATA		"DATA"
#define HOST		"HST"
#define ID		"ID"
#define NAME		"NAME"
#define PACKET		"PKT"
#define UDP_PORT	"UDP"
#define SYSTEM		"SYS"
#define PACKET_LOSS	"PKT_LOSS"
#define RESPONSE_TIME	"TIME"
#define PING		"ping"
#define QUERY		"query"
#define REPLY		"reply"
#define TIME_OUT	"TO"
#define HOST_NAME	0
#define HOST_IP		1
#define HOST_UDP_PORT	2
#define LOCAL_COMMANDS	3
#define HOST_COMMANDS	4
#define HOST_STATUS	5
#endif
#endif

==================================================
FILE: nomic_system.h
==================================================

#ifndef __NOMIC_SYSTEM__
#define __NOMIC_SYSTEM__
#define NOMIC_HANDLER "/obj/handlers/player_council"
#ifndef NOMIC_SYSTEM_NO_CLASSES
class nomic_amendment {
   string amender;
   string text;
   int date_amended;
}
class nomic_rule {
   int id;
   int type;
   int date_created;
   string creator;
   string text;
   class nomic_amendment* amendments;
}
class nomic_area {
   int* new_type_num;
   class nomic_rule* rules;
}
class nomic_comment {
   string text;
   string commenter;
   int date_commented;
}
class nomic_motion {
   int identifier;
   int motion_type;
   class nomic_rule rule;
   int new_rule_type;
   class nomic_comment* comments;
   int yes_votes;
   int no_votes;
   int abstain_votes;
   string* voted;
   int state;
   int date_added;
   int date_event;
   string added_by;
}
#endif
#ifdef NOMIC_SYSTEM_CASE_CLASSES
class nomic_case_note {
   int id;
   string person;
   string text;
   int time_created;
}
class nomic_case_event {
   int type;
   string mess;
   string person;
   int event_time;
   mixed data;
}
class nomic_case {
   int id;
   string opener;
   string short;
   string* people;
   int* notes;
   class nomic_case_event* events;
   int time_opened;
}
#endif
#define NOMIC_DEFAULT_TYPE_NUMS ({ 100, 300, 2000 })
#define NOMIC_TYPE_IMMUTABLE 0
#define NOMIC_TYPE_GENERAL   1
#define NOMIC_TYPE_CITIZEN   2
#define NOMIC_ERROR -1
#define NOMIC_MOTION_TYPE_RULE_ADD     1
#define NOMIC_MOTION_TYPE_RULE_AMEND   2
#define NOMIC_MOTION_TYPE_RULE_MOVE    3
#define NOMIC_MOTION_TYPE_RULE_REMOVE  3
#define NOMIC_STATE_COUNCIL_REVIEW 1
#define NOMIC_STATE_COUNCIL_VOTE   2
#define NOMIC_STATE_CITIZEN_VOTE   3
#define NOMIC_VOTE_YES 1
#define NOMIC_VOTE_NO  2
#define NOMIC_VOTE_ABSTAIN  3
#define NOMIC_CASE_EVENT_CLOSE  1
#define NOMIC_CASE_EVENT_APPEAL 2
#define NOMIC_CASE_EVENT_ADD_PERSON 3
#define NOMIC_CASE_EVENT_REMOVE_PERSON 4
#define NOMIC_RULE_DEFAULT_DIR "/save/nomic/default/"
#define NOMIC_PUNISHMENT_DIR "/std/room/punishments/"
#define NOMIC_PUNISHMENT_DOCS_DIR "/doc/punishments/"
#define NOMIC_SYSTEM_SAVE_FILE "/save/nomic/main.o"
#define NOMIC_CASE_SAVE "/save/nomic/"
#define NOMIC_CASE_APPEAL_TIME (14 * 60 * 60 * 24)
#define NOMIC_SYSTEM_ADMINISTRATOR_NAME "Administration"
#endif

==================================================
FILE: nroff.h
==================================================

#ifndef __SYS__NROFF
#define __SYS__NROFF
#define V_CENTER 1
#define V_ALL 2
#define V_PARA 3
#define V_LEFT 4
#define V_TABLE 5
#define V_COLUMN 6
#define V_INDENT 7
#define V_HEADER 8
#define NROFF_HAND "/obj/handlers/nroff"
#define NROFF_DIR "/doc/helpnr/"
#define CNROFF_DIR "/doc/creatornr/"
#define MNROFF_DIR "/doc/mannr/"
#endif

==================================================
FILE: obj_parser.h
==================================================

#ifndef ___OBJ_PARSER_H
#define ___OBJ_PARSER_H
#ifndef OBJ_PARSER_NO_CLASSES
class obj_match
{
   int result;
   object *objects;
   string text;
}
class obj_match_context
{
   int ordinal;
   int number_included;
   int* fraction;
   int ignore_rest;
   int no_ambiguous;
   object him;
   object her;
   object it;
   object* plural;
}
#endif
#define OBJ_PARSER_SUCCESS         100
#define OBJ_PARSER_NO_MATCH        315
#define OBJ_PARSER_TOO_DARK        316
#define OBJ_PARSER_FRACTION        317
#define OBJ_PARSER_BAD_FRACTION    318
#define OBJ_PARSER_BAD_ENVIRONMENT 319
#define OBJ_PARSER_NOT_LIVING      320
#define OBJ_PARSER_AMBIGUOUS       322
#define OBJ_PARSER_NOT_ENOUGH      323
#define OBJ_PARSER_MATCH_SINGULAR 4
#define OBJ_PARSER_MATCH_PLURAL   16
#define OBJ_PARSER_TYPE_EXISTENCE 1
#define OBJ_PARSER_TYPE_PLAYER    2
#define OBJ_PARSER_TYPE_SLOPPY_MATCHING 4
#define OBJ_PARSER_TYPE_NO_NESTED 8
#define OBJ_PARSER_TYPE_LIVING 16
#define OBJ_PARSER_TYPE_OBJECT 0
#define OBJ_PARSER_MATCH_TYPE     0
#define OBJ_PARSER_OBJECTS        1
#define OBJ_PARSER_AMBIGUOUS_PROP "no ambiguous"
#define OBJ_PARSER_USE_AND_AS_BREAK_PROP "use and"
#endif

==================================================
FILE: origin.h
==================================================

#define ORIGIN_BACKEND       "driver"
#define ORIGIN_DRIVER        "driver"
#define ORIGIN_LOCAL         "local"
#define ORIGIN_CALL_OTHER    "call_other"
#define ORIGIN_SIMUL_EFUN    "simul"
#define ORIGIN_CALL_OUT      "call_out"
#define ORIGIN_EFUN          "efun"
#define ORIGIN_FUNCTION_POINTER   "function_pointer"
#define ORIGIN_FUNCTIONAL         "functional"

==================================================
FILE: panic.h
==================================================

#ifndef __PANIC_H
#define __PANIC_H
#define NUM_GODMOTHERS 2
#define GODMOTHER_DIR "/obj/monster/godmother/"
#define FIRST_WAIT_TIME 120
#define FINISH_WAIT_TIME 240
#define PANIC_HANDLER "/obj/handlers/fairy_godmothers"
#define PANIC_NOT_OK 0
#define PANIC_OK 1
#endif

==================================================
FILE: parse_command.h
==================================================

#ifndef __SYS__PARSE_COMMAND
#define __SYS__PARSE_COMMAND
#define P_THING 0
#define P_STR 1
#define P_CUR_NUM 2
#define P_MAX_NUM 3
#define P_TOP 4
#define P_BOT 5
#endif

==================================================
FILE: parser.h
==================================================

#ifndef _PARSER_H
#define _PARSER_H
#include <tokenise.h>
#define PARSER "/global/parser"
#define TOKENISER "/obj/handlers/tokeniser"
#endif

==================================================
FILE: parser_error.h
==================================================

#ifndef PARSER_ERROR_H
#define PARSER_ERROR_H
#define ERR_IS_NOT		1
#define ERR_NOT_LIVING		2
#define ERR_NOT_ACCESSIBLE	3
#define ERR_AMBIG		4
#define ERR_ORDINAL		5
#define ERR_ALLOCATED		6
#define ERR_THERE_IS_NO		7
#define ERR_BAD_MULTIPLE	8
#endif

==================================================
FILE: peopler.h
==================================================

#ifndef __PEOPLE_H
#define __PEOPLE_H
#define NAME 0
#define C_NAME 1
#define STRING 2
#define GENDER 3
#define IP_NUMBER 4
#define IP_NAME 5
#define TYPE 6
#define AGE 7
#define GUILD 8
#define RACE 9
#define LEVEL 10
#define TERMINAL 11
#define ROWS 12
#define COLS 13
#define ROOM 14
#define EUID 15
#define UID 16
#define CFILE 17
#define CUR_DIR 18
#define ND_ALLOWED 19
#define CENTER 128
#define RIGHT 64
#define MASK (RIGHT+CENTER)
#define ABBREV ({ \
          "n", \
          "N", \
          "",  \
          "G", \
          "#", \
          "I", \
          "T", \
          "A", \
          "g", \
          "R", \
          "L", \
          "t", \
          "r", \
          "c", \
          "O", \
          "E", \
          "U", \
          "F", \
          "/", \
          "a"  \
        })
#define DE_NAMES ({ \
          "Name", \
          "Capitalized Name", \
          "", \
          "Gender", \
          "IP Number", \
          "IP Name", \
          "Type", \
          "Age", \
          "Guild", \
          "Race", \
          "Level", \
          "Terminal type", \
          "Rows", \
          "Cols", \
          "Room", \
          "Euid", \
          "Uid", \
          "Creator file", \
          "Current dir", \
          "Not allowed with" \
        })
#define P_DEFAULT ({ \
          NAME, 15, \
          TYPE|CENTER, 3, \
          GENDER|CENTER, 6, \
          STRING, " ", \
          GUILD|CENTER, 10, \
          STRING, " ", \
          LEVEL|RIGHT, 4, \
          STRING, " ", \
          AGE, 5, \
          ROOM, 30 \
        })
#define QP_DEFAULT ({ \
          AGE|RIGHT, 4, \
          STRING, " ", \
          NAME, 30, \
        })
#define T_DEFAULT ({ \
          NAME, 12, \
          ROWS|CENTER, 5, \
          STRING, " ", \
          COLS|CENTER, 4, \
          STRING, " ", \
          TERMINAL, 30, \
        })
#define N_DEFAULT ({ \
          NAME, 12, \
          STRING, " ", \
          IP_NUMBER, 16, \
          STRING, " ", \
          IP_NAME, 30, \
        })
#define SN_DEFAULT ({ \
          IP_NAME, 30, \
          STRING, " ", \
          IP_NUMBER, 16, \
          STRING, " ", \
          NAME, 12, \
        })
#define D_DEFAULT ({ \
          NAME, 12, \
          STRING, " ", \
          CUR_DIR, 25, \
          STRING, " ", \
          ROOM, 40, \
        })
#define ND_DEFAULT ({ \
          NAME, 12, \
          STRING, " ", \
          IP_NUMBER, 16, \
          STRING, " ", \
          IP_NAME, 20, \
          STRING, " ", \
          ND_ALLOWED, 100, \
        })
#endif

==================================================
FILE: permissions.h
==================================================

#define READ_MASK 1
#define WRITE_MASK 2
#define GRANT_MASK 4
#define LOCK_MASK 8

==================================================
FILE: philosophies.h
==================================================

#ifndef __PHILOSOPHIES_H__
#define __PHILOSOPHIES_H__
#define PHILOSOPHY_HANDLER "/obj/handlers/philosophies"
#endif

==================================================
FILE: player.h
==================================================

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

==================================================
FILE: player_handler.h
==================================================

#ifndef __PLAYER_HANDLER_H
#define __PLAYER_HANDLER_H
#define PLAYER_HANDLER "/obj/handlers/player_handler"
#define DELETE_DIR "delete"
#define APPEAL_DIR "appeal"
#define PLAYER_SAVE_DIR "/save/players/"
#define PLAYER_RAM_DIR "/save/ramdisk/players/"
#define BANISH_DIR "/banish/"
#endif

==================================================
FILE: player_shop.h
==================================================

#define CREATOR "calroth"
#define UNSET_STR "__RINGO_WOZ_ERE__"
#define PSOBJDIR "/obj/misc/player_shop/"
#define CABINET (PSOBJDIR + "shop_cabinet")
#define BADGE (PSOBJDIR + "shop_badge")
#define STAFF_BOOK (PSOBJDIR + "staff_book")
#define MGR_BOOK (PSOBJDIR + "mgr_book")
#define SHOP_BAG (PSOBJDIR + "shopping_bag")
#define SHOP_CHART (PSOBJDIR + "shop_chart")
#define SHOP_NOTICE (PSOBJDIR + "shop_notice")
#define TRUE 1
#define FALSE 0
#define PAID 1
#define UNPAID 0
#define EMP_POINTS 0
#define EMP_BANK 1
#define EMP_PAY 2
#define EMP_INACTIVE 3
#define EMP_NOBONUS 4
#define EMP_NOPROMOTE 5
#define EMP_EOM 6
#define EMPLOYEE 1
#define NPC 2
#define SUPERVISOR 4
#define MANAGER 8
#define CLOCKED_IN 16
#define EMP_MAP ({EMPLOYEE,0,0,0,1,0,0,})
#define MANAGER_POINTS 1000
#define SUPER_POINTS 500
#define BAD_REASON 0
#define BAD_BANNER 1
#define BAD_TIME 2
#define BAD_MAP ({"","",0,})
#define APP_TYPE 0
#define APP_TIME 1
#define APP_FOR 2
#define APP_AGAINST 3
#define APP_ABSTAIN 4
#define APP_MESSAGE 5
#define APPLIED 1
#define HIRED 2
#define AWAITING 3
#define VFOR      1
#define VAGAINST  0
#define VABSTAIN -1
#define APP_MAP ({APPLIED,0,({}),({}),({}),"",})
#define MIN_CABINETS 5
#define MAX_CABINETS 20
#define STOCK_PER_CABINET 50
#define MAX_STOCK (MAX_CABINETS * STOCK_PER_CABINET)
#define CABINET_COST 400000
#define LOG_ENTRY 1
#define PURCHASE 2
#define SALE 3
#define PERSONNEL 4
#define ACCOUNTS 5
#define GENERAL 6
#define CHARTLOG 7
#define CHART_MAX 0
#define CHART_AVE 1
#define CHART_BUY 2
#define CHART_SELL 3
#define CHART_CAB 4
#define CHART_AVESALE 5
#define CHART_SOLD 6
#define CHART_BOUGHT 7
#define POLICY_TIME 0
#define POLICY_MGR 1
#define POLICY_TEXT 2
#define POLICY_FOR 3
#define POLICY_AGAINST 4
#define POLICY_TYPE 5
#define POLICY_MAP ({0,"","",({}),({}),0,})
#define PLAYER_SHOP "/obj/handlers/player_shop"
#define HISTORY_HANDLER "/obj/handlers/hist_handler"
#define BANK_HANDLER "/obj/handlers/bank_handler"
#define PLAYER_HANDLER "/obj/handlers/player_handler"
#define BANKS ({ ({ "Bing's First National", "Bing's First", }), \
                 ({ "Lancrastian Farmers' Co-operative", "LFC", }), \
                 ({ "Klatchian Continental", "Klatchian Continental", }), \
              })
#define BELL_TIMEOUT 120
#define MIN_EMP 10
#define MAX_EMP 40
#define PERCENT_M 10
#define PERCENT_S 20
#define START_PAY 20
#define MAX_LEAVE 14
#define BAN_LENGTH 28
#define DECLINE_LENGTH 14
#define MGR_DEMOTE 14
#define MGR_WARN 7
#define SPR_DEMOTE 28
#define SPR_WARN 14
#define EMP_FIRE 62
#define EMP_WARN 14
#define MAX_BAG_ITEMS 10
#define MAX_BAG_WEIGHT 50
#define LOG_DAYS 14
#define HIRE_TIMEOUT (86400*14)
#define HIST_TIMEOUT (86400*91)
#define VOTE_TIMEOUT (86400*14)
#define NPC_DELAY (2 + random(3))
#define NPC_RELOAD 3600
#define SAVE_DELAY 1
#define PERS_DELAY 5
#define CLEAR_DELAY 300
#define COMPLAINT_TEXT "Please fully state your complaint below.  " \
                       "Include as much detail as you can and any " \
                       "evidence/witnesses to support your complaint."
#define SUGGEST_TEXT "Please detail your suggestion below."
#define APP_QUESTIONS ({ "Why do you want to work for "+ \
                     _office->query_shop_name()+ "?", \
                     "What is your (DW) age?", \
                     "What Guild do you belong to?", \
                     "What relevant experience do you have of collecting " \
                      " and/or recognising our stock?", \
                     "How much time (hours/week) do you think you can " \
                     "commit to the shop?  Please also tell us at what " \
                     "time you will usually be on.", \
                     "Do you already know anyone who is an employee " \
                     "here, who could recommend you?  If so, who?", \
                     "Have you previously held a position at this shop?  " \
                     "If so, why did you leave?", \
                     "Do you currently work at any other shop?", \
                     "Have you applied for employment here before?  " \
                     "If so, what was the outcome?", \
                     "Do you have anything else you'd like to tell us in " \
                     "support of your application?  Please expand on above " \
                     "points if necessary.  What you say here will influence " \
                     "whether or not you are hired." \
                })
#define LOG_ERROR(A,B) log_file( "/log/PLAYER_SHOP", "%s: %s : %s called by %s\n",\
                       ctime(time()), A, B, previous_object()->query_name() )
#define last_login(N) (PLAYER_HANDLER)->test_last(N)
#define test_cre(N) (PLAYER_HANDLER)->test_creator(N)
#define test_player(N) (PLAYER_HANDLER)->test_user(N)
#define test_prop(N,P) (PLAYER_HANDLER)->test_property(N,P)

==================================================
FILE: playerinfo.h
==================================================

#ifndef __PLAYERINFO_H
#define __PLAYERINFO_H
class dbentry {
    int     time;
    string  creator;
    string  event;
    string  comment;
    mixed   *extra;
}
class playerinfo {
    string          name;
    int             last_check;
    string          *alts;
    class dbentry   *data;
    string          main_alt;
    string          *old_alts;
    mapping         access_log;
}
#define PLAYERINFO_HANDLER "/obj/handlers/playerinfo"
#define VERBOSE_PI "verbose playerinfo"
#endif

==================================================
FILE: playtesters.h
==================================================

#ifndef __SYS__PLAYTESTER
#define __SYS__PLAYTESTER
#define PLAYTESTERS               "/d/playtesters/"
#define PT_LOGS                   "/log/secure/playtesters"
#define PT_SAVE                   "/save/playtesters"
#define PLAYTESTER_HAND           "/obj/handlers/playtesters"
#define PLAYTESTER_CHARS          PLAYTESTERS + "chars/"
#define PLAYTESTER_DOCS           PLAYTESTERS + "doc/"
#define PLAYTESTER_ITEMS          PLAYTESTERS + "items/"
#define PLAYTESTER_PALACE         PLAYTESTERS + "palace_rooms/"
#define PLAYTESTER_INHERITS       PLAYTESTERS + "inherits/"
#define PLAYTESTER_SECURE         PLAYTESTERS + "secure/"
#define PLAYTESTER_HANDLERS       PLAYTESTERS + "handlers/"
#define PLAYTESTER_HELP           PLAYTESTER_DOCS + "help_dir/"
#define PLAYTESTER_ARMOURY        (PLAYTESTER_PALACE + "armoury")
#define PLAYTESTER_ARENA          PLAYTESTER_PALACE + "arena/"
#define PLAYTESTER_COURSE         PLAYTESTER_PALACE + "course/"
#define PT_OBSTACLE_COURSE        (PLAYTESTER_INHERITS + "obstacle_course")
#define PLAYTESTER_INTERVIEW      (PLAYTESTER_PALACE + "interview")
#define PT_APPLICATION_HANDLER    (PLAYTESTER_HANDLERS + "applications")
#endif

==================================================
FILE: pop3.h
==================================================

#ifndef __POP3_H
#define __POP3_H
#define PORT_POP3 4110
#define POP3_VERSION "0.1"
#define POP_AUTH_USER   0
#define POP_AUTH_PASS   1
#define POP_TRANSACTION 2
#define POP_UPDATE      3
#define LOGIN_OB "/secure/login"
#define FOLDER_H "/obj/handlers/folder_handler"
#define DEBUG
#ifdef DEBUG
#define TP(_x) tell_object(find_player("turrican"), (_x))
#else
#define TP(_x)
#endif
#define CHECK_STATE(_state) if ((_state) != sess->state) \
{ \
    eventWrite(fd, sprintf("-ERR Unknown command in %s state\r\n", \
                           pop_states[sess->state])); \
    break; \
}
#define CHECK_CMD(_num, _str) if (sizeof(bits) < (_num)+1) \
                       { \
                         eventWrite(fd, _str); \
                         break; \
                       }
class pop_session {
  int fd;
  int state;
  int time;
  string command;
  string user_name;
  int *deleted;
  int num_messages;
  class mail_header *headers;
  string *messages;
  int *sizes;
  int last;
}
#endif

==================================================
FILE: position.h
==================================================

#ifndef __POSITION_H
#define __POSITION_H
#define SWIMMING "swimming"
#define STANDING "standing"
#define SITTING "sitting"
#define KNEELING "kneeling"
#define LYING "lying"
#define MEDITATING "meditating"
#define CROUCHING "crouching"
#define CAN_POSITION_PROPERTY "position on"
#define MULTIPLE_POSITION_PROPERTY "position multiple"
#define DEFAULT_POSITION_PROPERTY "default position"
#define POSITION_DEFAULT STANDING
#define STANDING_CMD "/cmds/living/stand"
#define LYING_CMD "/cmds/living/lie"
#define SITTING_CMD "/cmds/living/sit"
#define POS_ON_OBJECT 0
#define POS_TYPE      1
#define POS_MULTIPLE  2
#define POSITION_ARRAY_SIZE 3
#define ON_TYPE "on"
#define AT_TYPE "at"
#define BESIDE_TYPE "beside"
#define POSITION_ONLY_TYPE_SIZE 1
#define POSITION_MESS_SIZE 3
#define POSITION_TYPE_INDEX 0
#define POSITION_ME_MESS_INDEX 1
#define POSITION_REST_MESS 2
#endif

==================================================
FILE: potion_attrs.h
==================================================

#ifndef __SYS__POTION_ATTRS
#define __SYS__POTION_ATTRS
#define POTION_SPACE_HANDLER "/obj/handlers/potion_space"
#define POTION_ATTRS_SIZE 6
#define POTION_CONSISTENCY 0
#define POTION_TRANSPARENCY 1
#define POTION_NAMES 2
#define POTION_COLOURS 3
#define POTION_SMELLS 4
#define POTION_FLAVOURS 5
#define VERY_SMALL_AMOUNT 5
#define SMALL_AMOUNT 10
#define MODERATE_AMOUNT 25
#define OC_VOL 0
#define OC_MVOL 1
#define OC_WVOL 2
#define OC_MAXVOL 3
#define OC_LEAKRATE 4
#define OC_PSQUANT 5
#define OC_MISCATTRS 6
#define OC_PSCOORD 7
#endif

==================================================
FILE: priest.h
==================================================

#undef CLASSROOMS
#undef PRIESTCHARS
#define PRIESTTSG    "/d/am/small_gods/temple"
#define PRIESTAM     "/d/guilds/priests/Ankh-Morpork/"
#define PRIESTKLK     "/d/guilds/priests/Khot-lip-khin/"
#define PRIESTDJEL   "/d/guilds/priests/Djelibeybi/"
#define PRIESTOC    "/d/guilds/priests/Ohulan-Cutash/"
#define CLASSROOMS   "/d/guilds/priests/Ankh-Morpork/classrooms/"
#define TSG          "/d/am/priest/templeofsg/"
#define PRIESTCHARS  "/d/guilds/priests/chars/"
#define PRIESTINHERITS "/d/guilds/priests/inherits/"
#define PRIESTITEMS  "/d/guilds/priests/items/"
#define PRIESTUTILS  "/d/guilds/priests/utils/"
#define PRIESTSAVE   "/d/guilds/priests/save/"
#define PRAYERS     "/obj/rituals/"
#define BASIC       "/obj/rituals/basic"
#define HEALING     "/obj/rituals/basic_healing"

==================================================
FILE: priests_dev.h
==================================================

#define EFFECTS "/d/playtesters/effects/faith"
#define SHADOWS "/d/playtesters/shadows/faith"
#define ITEMS "/d/playtesters/items/faith"
#define RITUALS "/d/playtesters/rituals"
#define ROOMS "/d/playtesters/rooms"
#define INHERITS RITUALS "/inherits"

==================================================
FILE: project_management.h
==================================================

#ifndef __project_management_h
#define __project_management_h
#define MINUTE (60)
#define HOUR (60 * 60)
#define DAY (HOUR * 24)
#define WEEK (DAY * 7)
#define PROJECT_LOCK (5 * MINUTE)
#define TIME_BETWEEN_POSTINGS (7 * DAY)
#define STATUS ({"heap", "development", "playtesting", "play", "limbo"})
#define SIZE ({"very small", "small", "medium", "large", "very large", "huge", "special"})
#define COMPLEXITY ({"low", "medium", "high", "very high", "special"})
#define PROJECT_SAVE "/save/project"
#define TMP_SAVE "/save/project_tmp"
#define PROJECT_LOG "PROJECT_MANAGEMENT"
#define PROJECT_HANDLER "/obj/handlers/project_management"
#define TWIKI_BASE "http:
#define WHATWHAT ("/www/whatwhat")
#define PROJECT "project"
#define TASK "task"
#define NOTE "note"
#define FILE "file"
#define PLAYTESTING "playtesting"
#define CALLBACK "project_callback"
class task {
  string id;
  string task_name;
  string comments;
  string *assigned_to;
  string added_by;
  string aims;
  int percent_complete;
  int completion_date;
  int date_added;
}
class note {
  string id;
  int date_added;
  string added_by;
  string note;
}
class file {
  string file;
  int access;
  string task;
}
class project {
  string id;
  string name;
  string leader;
  string added_by;
  string description;
  string pt_notes;
  string what_touched;
  string touched_by;
  int date_added;
  int date_completed;
  int status;
  int percent_complete;
  int estimated_completion;
  int last_touched;
  int last_status_change;
  string *twiki;
  string *playtesters;
  string *domains;
  string *creators;
  string *sub_projects;
  class file *files;
  class task *tasks;
  class note *notes;
  int last_rotation;
  int size;
  int complexity;
  int current_rotation;
  string *last_pt_cohort;
  string *all_pts;
  string *guild_specific;
}
class project_tmp {
  string id;
  string name;
  string leader;
  string added_by;
  string description;
  string pt_notes;
  string *domains;
  string *creators;
  string *sub_projects;
  class file *files;
  string *twiki;
  string *playtesters;
  string what_touched;
  string touched_by;
  int date_added;
  int date_completed;
  int status;
  int percent_complete;
  int estimated_completion;
  int last_touched;
  int last_status_change;
  class task *tasks;
  class note *notes;
}
#endif

==================================================
FILE: pub.h
==================================================

#ifndef __SYS__PUB
#define __SYS__PUB
#define SOFTDRINK "softdrink"
#define ALCOHOL   "alcohol"
#define FOOD      "food"
#define DR_TYPE   0
#define DR_COST   1
#define DR_HEAL   2
#define DR_VOLUME 3
#define DR_INTOX  4
#define DR_DRMESS 5
#define DR_OTHMES 6
#define DR_OTHMESS 6
#endif

==================================================
FILE: quest_handler.h
==================================================

#ifndef __SYS__QUEST_HANDLER
#define __SYS__QUEST_HANDLER
#define QUEST_HANDLER "/obj/handlers/quest_handler"
#endif

==================================================
FILE: race.h
==================================================

#ifndef __SYS__RACE
#define __SYS__RACE
#define R_OBJECT 0
#define STD_RACE "/std/race/standard"
#endif

==================================================
FILE: random_names.h
==================================================

#ifndef __RANDOM_NAMES_H
#define __RANDOM_NAMES_H
#define RANDOM_NAME_GENERATOR "/obj/handlers/random_names"
#define RANDOM_NAME_SAVE_FILE "/save/random_names/random_names"
#define RANDOM_NAME_DATA_DIR  "/save/random_names/data/"
#endif

==================================================
FILE: ranged_response.h
==================================================

#define RUN 1
#define FIGHT 2
#define STAND 3

==================================================
FILE: reaction.h
==================================================

#ifndef __REACTION_H
#define __REACTION_H
class reaction {
    mixed ratio;
    string result;
    float result_amt;
    string message;
    mixed *func;
}
#define OBJ_A   1
#define OBJ_B   2
#define OBJ_X   3
#define ENV     4
#define ENV2    5
#define AMT_A   6
#define AMT_B   7
#endif

==================================================
FILE: refresh.h
==================================================

#ifndef __REFRESH_H
#define __REFRESH_H
#define REFRESH_HANDLER "/obj/handlers/refresh"
#define PARTIAL_REFRESH 0
#define TOTAL_REFRESH 1
#define PLAYER_DELETED 2
#endif

==================================================
FILE: report_handler.h
==================================================

#define SAVEPATH  "/save/cases/"
#define RECENT    (SAVEPATH+"recent.o")
#define NEWCASES  (SAVEPATH+"new.o")
#define NO_RECENT 20
#define NAME      0
#define CHARS     1
#define CREATOR   2
#define TIME      3
#define CATEGORY  4
#define REPORT    5
#define HIGHLORD  6
#define DECISION  7

==================================================
FILE: reversi.h
==================================================

#define MAX_PAGE ((int)this_player()->query_rows()-3)
#define TP_NAME this_player()->query_name()
#define SAVE_FILE "/w/pinkfish/save/reversi"
#define BOARD_THING "/w/pinkfish/board_getter"
#define REVERSI_OB "/w/pinkfish/reversi_board"
#define BOARD_PATH "/w/pinkfish/save/reversi/"
#define MIN_TIME (60*60*24*14)
#undef DEBUG
#undef DEBUG2
#define MAX_GAMES 10
#define R_PLAYER1 0
#define R_PLAYER2 1
#define R_BOARD 2
#define R_MOVE_NO 3
#define R_LAST 4
#define R_LASTX 5
#define R_LASTY 6
#define BOARD_COL "%^B_GREEN%^%^WHITE%^"
#define BLACK_COL "%^B_BLACK%^"
#define WHITE_COL "%^B_WHITE%^"
#define END_TILE  "%^B_GREEN%^"
#define RESET     "%^RESET%^"
#define SETUP_COL "%^B_CYAN%^"

==================================================
FILE: ritual_system.h
==================================================

#define EFFECTS "/std/effects/faith/"
#define ITEMS "/d/guilds/priests/items/"
#define RITUALS "/obj/rituals"
#define ROOMS "/d/guilds/priests/rooms"
#define INHERITS RITUALS "/inherits"
#define SHADOWS "/std/shadows/faith/"
#define RITUAL_DIRECT_NONE       0
#define RITUAL_DIRECT_ROOM       1
#define RITUAL_DIRECT_NON_LIVING 2
#define RITUAL_DIRECT_LIVING     4
#define RITUAL_DIRECT_SELF       8
#define RITUAL_DIRECT_MULTIPLE   16
#define RITUAL_DIRECT_EXTERN     32
#define RITUAL_CALCULATE_DYNAMIC  0
#define IMBUE_PERFORMER -1
#define IMBUE_PRIEST     1
#define SUCCESS -1
#define FAILURE -2
#define STOPPED -3
#define RITUAL EFFECTS"/basic_ritual"
#define SHADOW SHADOWS"/basic_ritual"
#define RELIGIOUS   "religious"
#define MENTAL      "mental"
#define SPEECH      "speech"
#define VISION      "vision"
#define MOVEMENT    "movement"
#define ENVIRONMENT "environment"
#define MISC        "misc"
#define FAMILY "faith.rituals" + info->family
#define CURING_INHERIT INHERITS "/basic_healing"
#define SHIELD_INHERIT INHERITS "/basic_shield"
#define PASSAGE_INHERIT INHERITS "/basic_passage"
#define ALCOHOL_INHERIT INHERITS "/basic_alcohol"
#define WARD_BASE SHADOWS +"/base_ward"
class stage {
  int key;
  string *messages;
  string skill;
  int level;
  string *materials;
  string *consumables;
  int pause;
  int time_modifier;
  function success_func;
  string prayer;
  int imbue_source;
}
class ritual {
   string name;
   string family;
   int base_gp_cost;
   int *align;
   int targets;
   class stage *stages;
   int pk_check;
   int teach_base;
   int learn_base;
   string training_skill;
   int movement;
   int speech;
   int vision;
   string *materials, *consumables;
   function target_check;
   string resist_skill;
   string help;
   int offensive;
   object caster;
   object imbue;
   object *rit_targets;
   object *resistors;
   int current_stage;
   int start_time;
   int target_count;
   function valid;
   int degree;
   string deity;
   mapping difficulties;
   mapping benefits;
}

==================================================
FILE: room.h
==================================================

#ifndef __SYS__ROOM
#define __SYS__ROOM
#define ROOM_HANDLER "/obj/handlers/room_handler"
#define ROOM_DEST       0
#define ROOM_EXIT       1
#define ROOM_OBV        2
#define ROOM_SIZE       3
#define ROOM_FUNC       4
#define ROOM_ENTER      5
#define ROOM_REL        6
#define ROOM_LOOK       7
#define ROOM_LOOK_FUNC  8
#define ROOM_GRADE      9
#define ROOM_MESS      10
#define ROOM_LINK_MESS 11
#define ROOM_NO_MAP    12
#define ROOM_DELTA     13
#define ROOM_NPC_STOP  14
#define ROOM_EXTRA_MOVE_MESS 15
#define DOOR_OBJECT "/std/room/basic/door"
#define ITEM_OBJECT "/std/room/basic/item"
#define CHATTER_OBJECT "/std/room/basic/chatter"
#define SITUATION_CHANGER_OBJECT  "/std/room/basic/situation_changer"
#define LINKER_OBJECT "/std/room/basic/linker"
#define TERRAIN_OBJECT "/std/room/basic/terrain"
#define WALL_OBJECT "/std/room/basic/wall"
#define ROOM_VOID "/room/void"
#define ENCHANT_HALF 3600
#define ROOM_KEEP_PROP "room keep"
#define ROOM_NOT_REPLACE_PROGRAM_PROP "replace program"
#define ROOM_IDLE_TIMEOUT 900
#define ROOM_HELP_FILE_DIR "/doc/room/"
#define ROOM_HELP_FILE_PROPERTY "help file name"
#define ROOM_DAY_INDEX 1
#define ROOM_NIGHT_INDEX 0
#define ROOM_DEFAULT_INDEX 2
#endif

==================================================
FILE: route.h
==================================================

#ifndef __ROUTE_H
#define __ROUTE_H
#define ROUTE_HANDLER "/obj/handlers/route_handler"
#endif

==================================================
FILE: runtime_config.h
==================================================

#ifndef RUNTIME_CONFIG_H
#define RUNTIME_CONFIG_H
#define BASE_CONFIG_STR        0
#define CFG_STR(x) ((x) + BASE_CONFIG_STR)
#define __MUD_NAME__                CFG_STR(0)
#define __ADDR_SERVER_IP__          CFG_STR(1)
#define __MUD_LIB_DIR__             CFG_STR(2)
#define __BIN_DIR__                 CFG_STR(3)
#define __LOG_DIR__                 CFG_STR(4)
#define __INCLUDE_DIRS__            CFG_STR(5)
#define __SAVE_BINARIES_DIR__       CFG_STR(6)
#define __MASTER_FILE__             CFG_STR(7)
#define __SIMUL_EFUN_FILE__         CFG_STR(8)
#define __SWAP_FILE__               CFG_STR(9)
#define __DEBUG_LOG_FILE__          CFG_STR(10)
#define __DEFAULT_ERROR_MESSAGE__   CFG_STR(11)
#define __DEFAULT_FAIL_MESSAGE__    CFG_STR(12)
#define __GLOBAL_INCLUDE_FILE__     CFG_STR(13)
#define __MUD_IP__                  CFG_STR(14)
#define BASE_CONFIG_INT (BASE_CONFIG_STR + 15)
#define CFG_INT(x)  ((x) + BASE_CONFIG_INT)
#define __MUD_PORT__                CFG_INT(0)
#define __ADDR_SERVER_PORT__        CFG_INT(1)
#define __TIME_TO_CLEAN_UP__        CFG_INT(2)
#define __TIME_TO_RESET__           CFG_INT(3)
#define __TIME_TO_SWAP__            CFG_INT(4)
#define __COMPILER_STACK_SIZE__     CFG_INT(5)
#define __EVALUATOR_STACK_SIZE__    CFG_INT(6)
#define __INHERIT_CHAIN_SIZE__      CFG_INT(7)
#define __MAX_EVAL_COST__           CFG_INT(8)
#define __MAX_LOCAL_VARIABLES__     CFG_INT(9)
#define __MAX_CALL_DEPTH__          CFG_INT(10)
#define __MAX_ARRAY_SIZE__          CFG_INT(11)
#define __MAX_BUFFER_SIZE__         CFG_INT(12)
#define __MAX_MAPPING_SIZE__        CFG_INT(13)
#define __MAX_STRING_LENGTH__       CFG_INT(14)
#define __MAX_BITFIELD_BITS__       CFG_INT(15)
#define __MAX_BYTE_TRANSFER__       CFG_INT(16)
#define __MAX_READ_FILE_SIZE__      CFG_INT(17)
#define __RESERVED_MEM_SIZE__       CFG_INT(18)
#define __SHARED_STRING_HASH_TABLE_SIZE__ CFG_INT(19)
#define __OBJECT_HASH_TABLE_SIZE__        CFG_INT(20)
#define __LIVING_HASH_TABLE_SIZE__        CFG_INT(21)
#define __FD6_PORT__		    CFG_INT(22)
#define __FD6_KIND__		    CFG_INT(23)
#define RUNTIME_CONFIG_NEXT CFG_INT(24)
#define NUM_CONFIG_STRS (BASE_CONFIG_INT - BASE_CONFIG_STR)
#define NUM_CONFIG_INTS (RUNTIME_CONFIG_NEXT - BASE_CONFIG_INT)
#endif

==================================================
FILE: security.h
==================================================

#ifndef __SYS_SECURITY_H
#define __SYS_SECURITY_H
#define SECURITY "/secure/security"
#define ACCESS "/std/basic/security"
#endif

==================================================
FILE: server.h
==================================================

#ifndef __SERVER_H__
#define __SERVER_H__
#define STRING 0
#define FILE 1
#define BLOCK_SIZE 65536
class buff {
    int Type;
    int Size;
    int Pos;
    string Filename;
    mixed Value;
}
class server {
    int Descriptor;
    int Blocking;
    int Closing;
    class buff *Buffer;
}
int eventCreateSocket(int port);
protected void eventServerListenCallback(int fd);
protected void eventServerAbortCallback(int fd);
protected void eventServerReadCallback(int fd, mixed val);
protected void eventRead(int fd, mixed val);
protected void eventServerWriteCallback(int fd);
varargs void eventWrite(int fd, mixed val, int close);
protected void eventClose(class server sock);
protected void eventSocketClosed(int fd);
int eventDestruct();
protected void eventNewConnection(int fd);
protected void eventSocketError(string str, int x);
function SetRead(function f);
int SetDestructOnClose(int x);
#endif

==================================================
FILE: shop.h
==================================================

#ifndef __SYS__SHOP
#define __SYS__SHOP
#define PAY_RATES ({ 100, 90, \
                     200, 80, \
                     400, 70, \
                     800, 60, \
                     1600, 50, \
                     3200, 40, \
                     6400, 30, \
                     12800, 20, \
                     10 })
#define MAX_AMOUNT 50000
#define MAX_INVENTORY 50
#define MAX_OBS 8
#endif

==================================================
FILE: situations.h
==================================================

class situation {
  string start_mess;
  string end_mess;
  string extra_look;
  function start_func;
  function end_func;
  int *chat_rate;
  string *chats;
  mixed *add_items;
  mixed *random_words;
}
#define WHEN_WEE_HOURS     ((1<<0) | (1<<1) | (1<<2) | (1<<3))
#define WHEN_EARLY_MORNING ((1<<4) | (1<<5) | (1<<6))
#define WHEN_LATE_MORNING  ((1<<7) | (1<<8) | (1<<9) | (1<<10) | (1<<11))
#define WHEN_AFTERNOON     ((1<<12) | (1<<13) | (1<<14) | (1<<15) | (1<<16))
#define WHEN_EVENING       ((1<<17) | (1<<18) | (1<<19))
#define WHEN_LATENIGHT     ((1<<20) | (1<<21) | (1<<22) | (1<<23))
#define WHEN_MIDDAY        ((1<<11) | (1<<12))
#define WHEN_MORNING       (WHEN_EARLY_MORNING | WHEN_LATE_MORNING)
#define WHEN_NIGHT         (WHEN_LATENIGHT | WHEN_WEE_HOURS)
#define WHEN_DAY           (WHEN_MORNING | WHEN_AFTERNOON)
#define WHEN_ANY_TIME      ((1<<24)-1)

==================================================
FILE: skills.h
==================================================

#ifndef __SYS__SKILLS
#define __SYS__SKILLS
#define SKILL_NAM 0
#define SKILL_LVL 1
#define SKILL_EXP 2
#define SKILL_BIT 3
#define SKILL_ARR_SIZE 4
#define SKILL_OB "/std/skills"
#define SKILL_MAX_TEACH 600
#define O_SKILL 0
#define O_NUM 1
#define O_LVL 2
#define O_XP 3
#define O_OTHER_PER 4
#define STD_SKILLS_COVERT ({ \
        "covert", 0, 0, ({ \
            "stealth", 0, 0, ({ \
                "inside", 0, 0, ({ }), \
                "outside", 0, 0, ({ }), \
                "underwater", 0, 0, ({ }), \
            }), \
            "hiding", 0, 0, ({ \
               "person", 0, 0, ({ }), \
               "object", 0, 0, ({ }), \
            }), \
            "lockpick", 0, 0, ({ \
                "doors", 0, 0, ({ }), \
                "safes", 0, 0, ({ }), \
                "traps", 0, 0, ({ }), \
            }), \
            "manipulation", 0, 0, ({ \
                "palming", 0, 0, ({ }), \
                "passing", 0, 0, ({ }), \
                "sleight-of-hand", 0, 0, ({ }), \
                "stealing", 0, 0, ({ }), \
            }), \
            "casing", 0, 0, ({ \
                "person", 0, 0, ({ }), \
                "place", 0, 0, ({ }), \
            }), \
            "items", 0, 0, ({ \
                "poisons", 0, 0, ({ }), \
                "traps", 0, 0, ({ }), \
                "weapons", 0, 0, ({ }), \
            }), \
            "points", 0, 0, ({ }), \
        }), \
    })
#define STD_SKILLS_CRAFTS ({ \
        "crafts", 0, 0, ({ \
            "smithing", 0, 0, ({ \
                "gold", 0, 0, ({ }), \
                "silver", 0, 0, ({ }), \
                "black", 0, 0, ({ \
                    "tools", 0, 0, ({ }), \
                    "weapons", 0, 0, ({ }), \
                    "armour", 0, 0, ({ }), \
                }), \
                "gem", 0, 0, ({ \
                    "cutting", 0, 0, ({ }), \
                    "polishing", 0, 0, ({ }), \
                    "setting", 0, 0, ({ }), \
                }), \
                "locks", 0, 0, ({ }), \
            }), \
            "mining", 0, 0, ({ \
                "gem", 0, 0, ({ }), \
                "ore", 0, 0, ({ \
                    "panning", 0, 0, ({ }), \
                }), \
                "mineral", 0, 0, ({ }), \
            }), \
            "hunting", 0, 0, ({ \
                "tracking", 0, 0, ({ }), \
                "fishing", 0, 0, ({ }), \
                "trapping", 0, 0, ({ }), \
                "foraging", 0, 0, ({ }), \
            }), \
            "carpentry", 0, 0, ({ \
                "furniture", 0, 0, ({ }), \
                "coopering", 0, 0, ({ }), \
                "turning", 0, 0, ({ }), \
                "whittling", 0, 0, ({ }), \
            }), \
            "pottery", 0, 0, ({ \
                "forming", 0, 0, ({ \
                    "throwing", 0, 0, ({ }), \
                    "shaping", 0, 0, ({ }), \
                }), \
                "glazing", 0, 0, ({ }), \
                "staining", 0, 0, ({ }), \
                "firing", 0, 0, ({ }), \
            }), \
            "materials", 0, 0, ({ \
                "tanning", 0, 0, ({ }), \
                "leatherwork", 0, 0, ({ }), \
                "weaving", 0, 0, ({ }), \
                "spinning", 0, 0, ({ }), \
                "needlework", 0, 0, ({ }), \
                "dyeing", 0, 0, ({ }), \
            }), \
            "husbandry", 0, 0, ({ \
                "plant", 0, 0, ({ \
                    "edible", 0, 0, ({ }), \
                    "herbal", 0, 0, ({ }), \
                    "milling", 0, 0, ({ }), \
                    "tree", 0, 0, ({ }), \
                }), \
                "animal", 0, 0, ({ \
                    "grooming", 0, 0, ({ }), \
                    "breeding", 0, 0, ({ }), \
                    "slaughtering", 0, 0, ({ }), \
                }), \
            }), \
            "culinary", 0, 0, ({ \
                "cooking", 0, 0, ({ }), \
                "baking", 0, 0, ({ }), \
                "butchering", 0, 0, ({ }), \
                "preserving", 0, 0, ({ }), \
                "brewing", 0, 0, ({ }), \
                "distilling", 0, 0, ({ }), \
            }), \
            "arts", 0, 0, ({ \
                "design", 0, 0, ({ }), \
                "calligraphy", 0, 0, ({ }), \
                "drawing", 0, 0, ({ }), \
                "painting", 0, 0, ({ }), \
                "printing", 0, 0, ({ }), \
                "sculpture", 0, 0, ({ }), \
            }), \
            "music", 0, 0, ({ \
                "instruments", 0, 0, ({ \
                    "percussion", 0, 0, ({ }), \
                    "wind", 0, 0, ({ }), \
                    "stringed", 0, 0, ({ }), \
                    "keyboard", 0, 0, ({ }), \
                    "vocal", 0, 0, ({ }), \
                }), \
                "special", 0, 0, ({ }), \
                "theory", 0, 0, ({ }), \
                "performance", 0, 0, ({ }), \
            }), \
            "points", 0, 0, ({ }), \
        }), \
    })
#define STD_SKILLS_FAITH ({ \
        "faith", 0, 0, ({ \
            "rituals", 0, 0, ({ \
                "offensive", 0, 0, ({ \
                    "area", 0, 0, ({ }), \
                    "target", 0, 0, ({ }), \
                }), \
                "defensive", 0, 0, ({ \
                    "area", 0, 0, ({ }), \
                    "self", 0, 0, ({ }), \
                    "target", 0, 0, ({ }), \
                }), \
                "curing", 0, 0, ({ \
                    "self", 0, 0, ({ }), \
                    "target", 0, 0, ({ }), \
                }), \
                "misc", 0, 0, ({ \
                    "area", 0, 0, ({ }), \
                    "self", 0, 0, ({ }), \
                    "target", 0, 0, ({ }), \
                }), \
                "special", 0, 0, ({ }), \
            }), \
            "items", 0, 0, ({ \
                "rod", 0, 0, ({ }), \
                "scroll", 0, 0, ({ }), \
            }), \
            "points", 0, 0, ({ }), \
        }), \
    })
#define STD_SKILLS_FIGHTING ({ \
        "fighting", 0, 0, ({ \
            "combat", 0, 0, ({ \
                "melee", 0, 0, ({ \
                    "sharp", 0, 0, ({ }), \
                    "pierce", 0, 0, ({ }), \
                    "blunt", 0, 0, ({ }), \
                    "unarmed", 0, 0, ({ }), \
                }), \
                "range", 0, 0, ({ \
                    "thrown", 0, 0, ({ }), \
                    "fired", 0, 0, ({ }), \
                }), \
                "parry", 0, 0, ({ \
                    "melee", 0, 0, ({ }), \
                    "range", 0, 0, ({ }), \
                }), \
                "dodging", 0, 0, ({ \
                    "melee", 0, 0, ({ }), \
                    "range", 0, 0, ({ }), \
                }), \
                "special", 0, 0, ({ \
                    "weapon", 0, 0, ({ }), \
                    "unarmed", 0, 0, ({ }), \
                    "tactics", 0, 0, ({ }), \
              }), \
            }), \
            "points", 0, 0, ({ }), \
        }), \
    })
#define STD_SKILLS_MAGIC ({ \
        "magic", 0, 0, ({ \
            "spells", 0, 0, ({ \
                "offensive", 0, 0, ({ }), \
                "defensive", 0, 0, ({ }), \
                "misc", 0, 0, ({ }), \
                "special", 0, 0, ({ }), \
            }), \
            "methods", 0, 0, ({ \
                "elemental", 0, 0, ({ \
                    "air", 0, 0, ({ }), \
                    "earth", 0, 0, ({ }), \
                    "fire", 0, 0, ({ }), \
                    "water", 0, 0, ({ }), \
                }), \
                "mental", 0, 0, ({ \
                    "animating", 0, 0, ({ }), \
                    "channeling", 0, 0, ({ }), \
                    "charming", 0, 0, ({ }), \
                    "convoking", 0, 0, ({ }), \
                    "cursing", 0, 0, ({ }), \
                }), \
                "physical", 0, 0, ({ \
                    "binding", 0, 0, ({ }), \
                    "brewing", 0, 0, ({ }), \
                    "chanting", 0, 0, ({ }), \
                    "dancing", 0, 0, ({ }), \
                    "enchanting", 0, 0, ({ }), \
                    "evoking", 0, 0, ({ }), \
                    "healing", 0, 0, ({ }), \
                    "scrying", 0, 0, ({ }), \
                }), \
                "spiritual", 0, 0, ({ \
                    "abjuring", 0, 0, ({ }), \
                    "banishing", 0, 0, ({ }), \
                    "conjuring", 0, 0, ({ }), \
                    "divining", 0, 0, ({ }), \
                    "summoning", 0, 0, ({ }), \
                }), \
            }), \
            "items", 0, 0, ({ \
                "held", 0, 0, ({ \
                    "wand", 0, 0, ({ }), \
                    "rod", 0, 0, ({ }), \
                    "staff", 0, 0, ({ }), \
                    "broom", 0, 0, ({ }), \
                }), \
                "worn", 0, 0, ({ \
                    "amulet", 0, 0, ({ }), \
                    "ring", 0, 0, ({ }), \
                }), \
                "scroll", 0, 0, ({ }), \
                "talisman", 0, 0, ({ }), \
            }), \
            "points", 0, 0, ({ }), \
        }), \
    })
#define STD_SKILLS_OTHER ({ \
        "other", 0, 0, ({ \
            "trading", 0, 0, ({ \
                 "buying", 0, 0, ({ }), \
                 "selling", 0, 0, ({ }), \
                 "valueing", 0, 0, ({ \
                    "gems", 0, 0, ({ }), \
                    "jewellery", 0, 0, ({ }), \
                    "weapons", 0, 0, ({ }), \
                    "armour", 0, 0, ({ }), \
                }), \
            }), \
            "movement", 0, 0, ({ \
                 "swimming", 0, 0, ({ }), \
                 "riding", 0, 0, ({ \
                     "horse", 0, 0, ({ }), \
                     "camel", 0, 0, ({ }), \
                 }), \
                 "climbing", 0, 0, ({ \
                     "tree", 0, 0, ({ }), \
                     "rock", 0, 0, ({ }), \
                     "rope", 0, 0, ({ }), \
                 }), \
                 "sailing", 0, 0, ({ }), \
            }), \
            "acrobatics", 0, 0, ({ \
                 "tumbling", 0, 0, ({ }), \
                 "vaulting", 0, 0, ({ }), \
                 "balancing", 0, 0, ({ }), \
            }), \
            "evaluating", 0, 0, ({ \
                "weapons", 0, 0, ({ }), \
                "armour", 0, 0, ({ }), \
            }), \
            "culture", 0, 0, ({ \
                "ankh-morporkian", 0, 0, ({ }), \
                "djelian", 0, 0, ({ }), \
                "ephebian", 0, 0, ({ }), \
                "agatean", 0, 0, ({ }), \
            }), \
            "perception", 0, 0, ({ }), \
            "direction", 0, 0, ({ }), \
            "health", 0, 0, ({ }), \
            "points", 0, 0, ({ }), \
        }), \
    })
#define STD_SKILLS ( STD_SKILLS_COVERT + STD_SKILLS_CRAFTS + STD_SKILLS_FAITH + STD_SKILLS_FIGHTING + STD_SKILLS_MAGIC + STD_SKILLS_OTHER )
#endif

==================================================
FILE: snmp.h
==================================================

#define LISTEN_PORT		4161
#define COMMUNITY		"mrtg-snmpd"
#define SNMPHANDLER		"/obj/handlers/snmp_handler"
#define ID			0
#define ES			1
#define EI			2
#define	INTEGER			2
#define	BIT_STRING		3
#define OCTET_STRING		4
#define	NULL			5
#define OBJECT_IDENT		6
#define	SEQUENCE		48
#define IPADDRESS		64
#define	COUNTER			65
#define	GAUGE			66
#define	TIMETICKS		67
#define	OPAQUE			68
#define	NSAPADDRESS		69
#define	GETREQUESTPDU		160
#define	GETNEXTREQUESTPDU	161
#define	GETRESPONSEPDU		162
#define	SETREQUESTPDU		163
#define	TRAPPDU			164

==================================================
FILE: socket.h
==================================================

#ifndef __SYS__SOCKET
#define __SYS__SOCKET
#include <socket_errors.h>
#define MUD 0
#define STREAM 1
#define DATAGRAM 2
#define STREAM_BINARY 3
#define DATAGRAM_BINARY 4
#define INETD_TYPE 5
#endif

==================================================
FILE: socket_err.h
==================================================

#ifndef _SOCKET_ERRORS_H_
#define _SOCKET_ERRORS_H_
#define EESUCCESS	  1
#define EESOCKET	 -1
#define EESETSOCKOPT	 -2
#define	EENONBLOCK	 -3
#define EENOSOCKS	 -4
#define EEFDRANGE	 -5
#define EEBADF		 -6
#define EESECURITY	 -7
#define	EEISBOUND	 -8
#define EEADDRINUSE	 -9
#define EEBIND		-10
#define EEGETSOCKNAME	-11
#define EEMODENOTSUPP	-12
#define EENOADDR	-13
#define EEISCONN	-14
#define EELISTEN	-15
#define EENOTLISTN	-16
#define EEWOULDBLOCK	-17
#define EEINTR		-18
#define EEACCEPT	-19
#define	EEISLISTEN	-20
#define EEBADADDR	-21
#define EEALREADY	-22
#define EECONNREFUSED	-23
#define EECONNECT	-24
#define EENOTCONN	-25
#define EETYPENOTSUPP	-26
#define	EESENDTO	-27
#define	EESEND		-28
#define	EECALLBACK	-29
#define EESOCKRLSD	-30
#define EESOCKNOTRLSD   -31
#define EEBADDATA       -32
#define	ERROR_STRINGS	 33
#endif

==================================================
FILE: socket_errors.h
==================================================

#ifndef _SOCKET_ERRORS_H_
#define _SOCKET_ERRORS_H_
#define EESUCCESS	  1
#define EESOCKET	 -1
#define EESETSOCKOPT	 -2
#define	EENONBLOCK	 -3
#define EENOSOCKS	 -4
#define EEFDRANGE	 -5
#define EEBADF		 -6
#define EESECURITY	 -7
#define	EEISBOUND	 -8
#define EEADDRINUSE	 -9
#define EEBIND		-10
#define EEGETSOCKNAME	-11
#define EEMODENOTSUPP	-12
#define EENOADDR	-13
#define EEISCONN	-14
#define EELISTEN	-15
#define EENOTLISTN	-16
#define EEWOULDBLOCK	-17
#define EEINTR		-18
#define EEACCEPT	-19
#define	EEISLISTEN	-20
#define EEBADADDR	-21
#define EEALREADY	-22
#define EECONNREFUSED	-23
#define EECONNECT	-24
#define EENOTCONN	-25
#define EETYPENOTSUPP	-26
#define	EESENDTO	-27
#define	EESEND		-28
#define	EECALLBACK	-29
#define EESOCKRLSD	-30
#define EESOCKNOTRLSD   -31
#define EEBADDATA       -32
#define	ERROR_STRINGS	 33
#endif

==================================================
FILE: soul.h
==================================================

#ifndef __SYS_SOUL_H
#define __SYS_SOUL_H
#define PATTERNS 0
#define SINGLE 1
#define TARGET 2
#define NO_ARGUMENTS 0
#define ARGUMENTS 1
#define SELF     0
#define REST     1
#define TARG     2
#define ARGS     3
#define FORCE    4
#define POSITION 5
#define POSITION_SINGLE 2
#define ARG_SIZE 6
#define SMALL_ARG_SIZE 4
#define SOUL_OBJECT "/obj/handlers/new_soul"
#define SOUL_COMPILER "/obj/handlers/soul_compiler"
#define SOUL_DIR "/soul/"
#define ONLY_ARGUMENT 1
#define NO_ARGUMENT 2
#define ARGUMENT_FIRST 3
#define ARGUMENT_SECOND 4
#define ONLY_TARGET 5
#endif

==================================================
FILE: spells.h
==================================================

#ifndef __SYS__SPELLS
#define __SYS__SPELLS
#define SP_OBJECT 1
#define SP_FUNC 2
#define SP_PARAM 3
#define S_OBJECT 0
#define S_FUNC 1
#define SP_NO_RNDS 0
#endif

==================================================
FILE: state_change.h
==================================================

#ifndef __STATE_CHANGE_H
#define __STATE_CHANGE_H
class state_change {
    string result;
    float factor;
    function *func;
    int playtester;
}
#define STATE_CHANGE     ("/obj/handlers/state_change")
#endif

==================================================
FILE: sur.h
==================================================

#if !defined(__SUR__)
#define __SUR__
#define SUR                    "/d/sur/"
#define STO_LAT                SUR "StoLat/"
#define NOWHERE                SUR "Nowhere/"
#define DINKY                  SUR "Dinky/"
#define SHEEPRIDGE             SUR "Sheepridge/"
#define HOLYWOOD               SUR "Holywood/"
#define PEKAN_FORD             SUR "PekanFord/"
#define HILLSHIRE              SUR "Hillshire/"
#define CONSORT                SUR "Consort/"
#define SCROGDEN               SUR "Scrogden/"
#define RHAM_NITZ              SUR "Rham_Nitz/"
#define CHIRM                  SUR "Chirm_dev/"
#define JOWSERS_COVE           SUR "JowsersCove_dev/"
#define PSEUDOPOLIS            SUR "Pseudopolis_dev/"
#define QUIRM                  SUR "Quirm_dev/"
#define SCROTE                 SUR "Scrote_dev/"
#define STO_HELIT              SUR "Sto_Helit/"
#define STO_KERRIG             SUR "StoKerrig_dev/"
#define WEEZENT                SUR "Weezent/"
#define STO_PLAINS             SUR "Sto_Plains/"
#define SKUND_FOREST           SUR "Skund/"
#define CARRACK_MTNS           SUR "Carrack_Mtns/"
#define MORPORK_MTNS           SUR "Morpork_Mtns/"
#define ANKH_RIVER             SUR "Ankh_River/"
#define BEL_SHAMHAROTH         SUR "Bel_Shamharoth/"
#define DRYAD                  SUR "Dryad/"
#define HAUNTED_HOUSE          SUR "HauntedHouse/"
#define SUR_ITEMS              SUR "items/"
#define SUR_CHARS              SUR "chars/"
#define SUR_HOSPITAL           SUR "hospital/sur_hospital"
#define SUR_ROADS              SUR "roads/"
#define SUR_CURRENCY_DEFAULT   "Ankh-Morpork"
#define SAVE                   "/save/"
#define SUR_SAVE               SAVE "sur/"
#define SUR_INHERIT            SUR "inherit/"
#define SUR_HUMAN              SUR_INHERIT "sur_human"
#define SUR_ANIMAL             SUR_INHERIT "sur_animal"
#define SUR_PEDDLER            SUR_INHERIT "sur_peddler"
#define SUR_INSIDE             SUR_INHERIT "inside_room"
#define SUR_OUTSIDE            SUR_INHERIT "outside_room"
#define SUR_ITEM_SHOP_INSIDE   SUR_INHERIT "item_shop_inside"
#define SUR_ITEM_SHOP_OUTSIDE  SUR_INHERIT "item_shop_outside"
#define SUR_GEN_SHOP_INSIDE    SUR_INHERIT "general_shop_inside"
#define SUR_GEN_SHOP_OUTSIDE   SUR_INHERIT "general_shop_outside"
#define SHORT_ROAD             10000
#define MEDIUM_ROAD            25000
#define LONG_ROAD              50000
#endif

==================================================
FILE: surface.h
==================================================

#ifndef __SYS__SURFACE
#define __SYS__SURFACE
#define SURFACE_MODULE "/std/basic/surface"
#define SURFACE_SHADOW "/std/shadows/misc/surface"
#endif

==================================================
FILE: talker.h
==================================================

class talker_args {
    int status;
    string *channels;
    int verbose;
    int local_echo;
    mixed colour;
}
class cache_data {
    int playtester;
    int talker_quest;
    int apex_member;
}
#define LIST_FORMAT "   %12-s %*-=s\n"
#define HIST "/obj/handlers/hist_handler"
#define ON_PATTERN "{on|off}"
#define VERBOSE_PATTERN "{brief|verbose}"
#define CHANNEL_PATTERN "channels"
#define NEW_CHANNEL_PATTERN "<word'new channel'>"
#define SET_COLOUR_FULL_PATTERN "colour <word'channel'> <string'colour'> for <direct:object'talker'>"
#define SET_COLOUR_PATTERN "colour <word'channel'> <string'colour'>"
#define COLOUR_LIST "colour list"
#define TOGGLE_COLOUR_PATTERN "colour"
#define COLOUR_ON_OFF_PATTERN "colour {on|off|reset}"
#define DELETE_CHANNEL_PATTERN "delete <word'channel'>"
#define HISTORY_PATTERN "history"
#define HISTORY_CHANNEL_PATTERN "history <word'channel'>"
#define LIST_PATTERN "list"
#define LIST_CHANNEL_PATTERN "list <word'channel'>"
#define LIST_CHANNEL_PATTERN_BRIEF "list brief <word'channel'>"
#define ECHO_PATTERN "echo {on|off}"
#define DEFAULT_COLOUR "%^BOLD%^%^GREEN%^"
#define DEFAULT_COLOUR_SETTINGS ([ "default" : DEFAULT_COLOUR, "status" : "on" ])
#define DEFAULT_COLOUR_WITH(n) ([ "default" : (n), "status" : "on" ])

==================================================
FILE: tasks.h
==================================================

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

==================================================
FILE: telnet.h
==================================================

#define DO 253
#define IAC 255
#define SB  250
#define SE  240
#define TELOPT_TTYPE 24
#define TELOPT_NAWS 31
#define TELOPT_MXP 91
#define TELQUAL_IS 0
#define TELQUAL_SEND 1

==================================================
FILE: term.h
==================================================

#ifndef __SYS__TERM
#define __SYS__TERM
#define TERM_HANDLER "/obj/handlers/term"
#endif

==================================================
FILE: terrain.h
==================================================

#ifndef __SYS__TERRAIN
#define __SYS__TERRAIN
#define TERRAIN_MAP "/obj/handlers/terrain_handler"
#define TERRAIN_LOG "/obj/handlers/terrain_things/logroom"
#define RESTORE_PATH "/save/terrains/"
#endif

==================================================
FILE: terrain_map.h
==================================================

#ifndef __TERRAIN_MAP_H
#define __TERRAIN_MAP_H
#define TERRAIN_MAP_WORLD_MAP "/obj/handlers/world_map"
#define TERRAIN_MAP              "/std/room/inherit/terrain_map/"
#define TERRAIN_MAP_FEATURE_LOCAL  TERRAIN_MAP + "feature_local"
#define TERRAIN_MAP_SIMPLE_FEATURE_BASE  TERRAIN_MAP + "simple_feature"
#define TERRAIN_MAP_FEATURE_BASE  TERRAIN_MAP + "feature_base"
#define TERRAIN_MAP_DISTANCE_BASE  TERRAIN_MAP + "distance_str"
#define TERRAIN_MAP_REGION_RECTANGULAR  TERRAIN_MAP + "region_rect"
#define TERRAIN_MAP_REGION_POLYGON  TERRAIN_MAP + "region_poly"
#define TERRAIN_MAP_REGION_LINE  TERRAIN_MAP + "region_line"
#define TERRAIN_MAP_HANDLER_BASE  TERRAIN_MAP + "handler_base.c"
#define TERRAIN_MAP_FACTORY     TERRAIN_MAP + "factory.c"
#define TERRAIN_MAP_FACTORY_BASE     TERRAIN_MAP + "factory_base.c"
#define TERRAIN_MAP_ROOM_BASE     TERRAIN_MAP + "terrain_room.c"
#define TERRAIN_MAP_OUTSIDE_BASE  TERRAIN_MAP + "outside_base.c"
#define TERRAIN_MAP_WATER_OUTSIDE_BASE  TERRAIN_MAP + "water_outside_base.c"
#define TERRAIN_MAP_WATER_INSIDE_BASE  TERRAIN_MAP + "water_inside_base.c"
#define TERRAIN_MAP_INSIDE_BASE   TERRAIN_MAP + "inside_base.c"
#define TERRAIN_MAP_AIR_BASE TERRAIN_MAP + "air_base.c"
#define TERRAIN_MAP_ONE_MILE 73920
#define TERRAIN_MAP_HALF_MILE 36960
#define TERRAIN_MAP_GRID_SIZE (7 * TERRAIN_MAP_ONE_MILE)
#define TERRAIN_MAP_IN_LOOK_PROP "terrain map look"
#define TERRAIN_MAP_LONG_JUMP_PROPERTY "terrain map jump"
#define TERRAIN_MAP_WHOLE_SENTANCE_FLAG 1
#define TERRAIN_MAP_BLOCKING_FLAG       2
#define TERRAIN_MAP_JOURNEY_EXIT "journey "
#define TERRAIN_MAP_WALK_EXIT "walk "
#define TERRAIN_MAP_DEFAULT_AIR_ROOM "/room/air_terrain"
class coord {
   int x;
   int y;
   int z;
}
#define TERRAIN_MAP_WORLD_BOUNDARY (56 * TERRAIN_MAP_ONE_MILE)
#define TERRAIN_MAP_WORLD_REGION_SIZE 15
#define TERRAIN_MAP_WORLD_REGION_BOUNDARY (TERRAIN_MAP_WORLD_REGION_SIZE * BOUNDARY)
#define TERRAIN_MAP_WORLD_OFFSET (100 * TERRAIN_MAP_WORLD_BOUNDARY)
#define TERRAIN_MAP_WORLD_REGION_WIDTH 15
#define TERRAIN_MAP_WORLD_PIXEL_WIDTH 768
#define TERRAIN_MAP_WORLD_LOW_X (-(TERRAIN_MAP_WORLD_PIXEL_WIDTH / 2) * TERRAIN_MAP_GRID_SIZE * 10)
#define TERRAIN_MAP_WORLD_LOW_Y (-(TERRAIN_MAP_WORLD_PIXEL_WIDTH / 2) * TERRAIN_MAP_GRID_SIZE * 10)
#define TERRAIN_MAP_WORLD_HIGH_X ((TERRAIN_MAP_WORLD_PIXEL_WIDTH / 2) * TERRAIN_MAP_GRID_SIZE * 10)
#define TERRAIN_MAP_WORLD_HIGH_Y ((TERRAIN_MAP_WORLD_PIXEL_WIDTH / 2) * TERRAIN_MAP_GRID_SIZE * 10)
#define TERRAIN_MAP_ROOM_EXACT 0
#define TERRAIN_MAP_ROOM_MAP   1
#define TERRAIN_MAP_ROOM_CLIMB 2
#endif

==================================================
FILE: tokenise.h
==================================================

#ifndef __SYS__TOKENISE
#define __SYS__TOKENISE
#define TOK_PLUS 1
#define TOK_MINUS 2
#define TOK_MULT 3
#define TOK_DIV 4
#define TOK_OBRAC 5
#define TOK_CBRAC 6
#define TOK_SARRAY 7
#define TOK_EARRAY 8
#define TOK_SMAPPING 9
#define TOK_EMAPPING 10
#define TOK_COLON 11
#define TOK_COMMA 12
#define TOK_TAB 13
#define TOK_CALL 14
#define TOK_DOT 15
#define TOK_DOTDOT 16
#define TOK_LESS 17
#define TOK_GREATOR 18
#define TOK_LESSEQ 19
#define TOK_GREATOREQ 20
#define TOK_EQUAL 21
#define TOK_ASSIGN 22
#endif

==================================================
FILE: top_ten_tables.h
==================================================

#ifndef __TOP_TEN_TABLES_H
#define __TOP_TEN_TABLES_H
#define TOP_TEN_HANDLER "/obj/handlers/top_ten_handler"
#define TOP_TEN_NAME 0
#define TOP_TEN_RATING 1
#define TOP_TEN_LEVEL 2
#define TOP_TEN_AGE 3
#define TOP_TEN_LARGEST_FAMILY    0
#define TOP_TEN_OLDEST_FAMILY     1
#define TOP_TEN_MOST_QUEST_POINTS 2
#define TOP_TEN_MOST_GUILD        3
#define TOP_TEN_MOST_PKS          4
#define TOP_TEN_SINGLE_GENDER     5
#define TOP_TEN_OLDEST_LOGONS     6
#define TOP_TEN_MOST_RELATIONSHIPS 7
class top_ten_family_guild {
   int num;
   string top_family_name;
}
#endif

==================================================
FILE: tune.h
==================================================

#ifndef __SYS__TUNE
#define __SYS__TUNE
#define TIME_BETWEEN_HEAL 5
#define MIN_TIME 2*60*60*60
#define STD_COST 125
#define LEVEL_DIV 3
#define DEFAULT_COST 10
#define COST_DIV 20
#define TIME_DIV 300
#define MAX_AL 10000
#define SHOUT_DISTANCE 1000
#endif

==================================================
FILE: twilight.h
==================================================

#define NEVER 2
#define DAY   1
#define NIGHT 0
#define WEATHER_HANDLER         "/obj/handlers/weather.c"
#define CHANGING_OUTSIDE_OBJECT "/std/room/twilight.c"

==================================================
FILE: type.h
==================================================

#ifndef _TYPE_H
#define _TYPE_H
#define INT             "int"
#define STRING  	"string"
#define ARRAY   	"array"
#define OBJECT  	"object"
#define MAPPING         "mapping"
#define FUNCTION        "function"
#define FLOAT           "float"
#define BUFFER          "buffer"
#define CLASS           "class"
#endif

==================================================
FILE: udp.h
==================================================

#ifndef __SYS__UDP
#define __SYS__UDP
#ifndef __UDP_H
#define __UDP_H
#define NAMESERVER_CD "/net/nameserver_cd"
#define UDP_PATH "/net/udp/"
#define NETMAIL_D "/net/daemon/netmaild"
#define PING_Q (UDP_PATH+"ping_q")
#define PING_A (UDP_PATH+"ping_a")
#define MUDLIST_UDP ({ "165.95.7.122", 5678, "199.199.122.10", 1709, "129.16.117.21", 2500, "198.69.82.2", 5563, "129.10.114.86", 5563 })
#define UDP_STARTUP "startup"
#define UDP_SHUTDOWN "shutdown"
#define UDP_BOARD_Q "board_q"
#define UDP_PING_Q "ping_q"
#define UDP_PING_A "ping_a"
#define UDP_SUPPORT_Q "support_q"
#define UDP_SUPPORT_A "support_a"
#define UDP_RWHO_Q "rwho_q"
#define UDP_RWHO_A "rwho_a"
#define UDP_MUDLIST_Q "mudlist_q"
#define UDP_MUDLIST_A "mudlist_a"
#define UDP_GFINGER_Q "gfinger_q"
#define UDP_GFINGER_A "gfinger_a"
#define UDP_WARNING "warning"
#define UDP_GTELL "gtell"
#define UDP_GWIZMSG "gwizmsg"
#define UDP_AFFIRMATION_A "affirmation_a"
#define UDP_MAIL_A "mail_a"
#define UDP_MAIL_Q "mail_q"
#define UDP_LOCATE_Q "locate_q"
#define UDP_LOCATE_A "locate_a"
#define MAX_RETRYS 2
#define UDP_NO_CONTACT "_udp_no_contact"
#endif
#endif

==================================================
FILE: underworld.h
==================================================

#define UNDERWORLD  "/d/underworld/"
#define DEATH           "/d/underworld/death/"
#define DEATH_INSIDE    DEATH +"inside/"
#define DEATH_OUTSIDE   DEATH +"outside/"
#define DEATH_LIFE      DEATH +"life_rooms/"
#define DEATH_CHARS     DEATH +"chars/"
#define DEATH_ITEMS     DEATH +"items/"
#define DEATH_NEW       UNDERWORLD + "death_new/"
#define DOPPLES         UNDERWORLD + "dopples/"
#define DOPPLES_SAVE    DOPPLES + "save/"
#define MOVING_SHOP             UNDERWORLD + "moving_shop/"
#define MOVING_SHOP_INHERITS    MOVING_SHOP +"inherits/"
#define MOVING_SHOP_CHARS       MOVING_SHOP +"chars/"
#define MOVING_SHOP_EFFECTS     MOVING_SHOP +"effects/"
#define MOVING_SHOP_ITEMS       MOVING_SHOP +"items/"
#define MOVING_SHOP_ROOMS       MOVING_SHOP +"rooms/"
#define MOVING_SHOP_SHADOWS     MOVING_SHOP +"shadows/"
#define MOVING_SHOP_SPELLS      MOVING_SHOP +"spells/"
#define PLANES "/d/underworld/planes/"
#define AWFFICE PLANES +"awffice/"
#define DEMONS "/d/underworld/demons/"
#define ELEMENTALS "/d/underworld/elementals/"
#define IMPS "/d/underworld/imps/"

==================================================
FILE: unseen.h
==================================================

#define UNIVERSITY            "/d/guilds/wizards/Ankh-Morpork/"
#define ANCIENT_ASSEMBLY      UNIVERSITY +"ancient_assembly/"
#define NEW_HALL              UNIVERSITY +"new_hall/"
#define TURNWISE_COURT        UNIVERSITY +"turnwise_court/"
#define WIDDERSHINS_COURT     UNIVERSITY +"widdershins_court/"

==================================================
FILE: user_parser.h
==================================================

#ifndef __SYS_PARSER_H
#define __SYS_PARSER_H
#define PATTERN_WEIGHT 0
#define PATTERN_STRING 1
#define OLD_PATTERN_STRING 2
#define OBJS 3
#define WORD_LIST 1
#define STRING 2
#define OPTIONAL 3
#define DIRECT_OBJECT 4
#define INDIRECT_OBJECT 5
#define NUMBER 6
#define LIVING 7
#define SINGLE_WORD 8
#define DISTANT_LIVING 9
#define ANY_LIVING 10
#define ANY_OBJECT 11
#define SHORT_STRING 12
#define FRACTION 13
#define WIZ_PRESENT_TARGET 14
#define WORD_LIST_SPACES 15
#define OPTIONAL_SPACES 16
#define TARGET_PLAYER 17
#define QUOTED_STRING 18
#define PATTERN ({ "","","<string> ","[","<direct> ","<indirect> ", \
                   "<number> ", "","<word> ","","","","<string:short> ", \
                   "<fraction> ", "", "", "[", "", "<string:quoted>" })
#define FIND_NONE 0
#define FIND_FIRST 1
#define FIND_LAST 2
#define ENV_HERE       0
#define ENV_ME         1
#define ENV_HERE_ME    2
#define ENV_DIRECT_OBS 3
#define ENV_ME_HERE    4
#define MASTER "/secure/master"
#define PATTERN_OB "/obj/handlers/pattern_compiler"
#endif

==================================================
FILE: vault.h
==================================================

#ifndef __VAULT_H
#define __VAULT_H
#include <money.h>
#define FEE_AMT 100
#define INIT_AMT 2000
#define FEE_AMT_STRING (string)(MONEY_HAND->money_value_string(100, this_object()->query_property("place")))
#define INIT_AMT_STRING (string)(MONEY_HAND->money_value_string(2000, this_object()->query_property("place")))
#define VAULT_SAVE "/save/vaults/"
#endif

==================================================
FILE: virtual.h
==================================================

#ifndef __SYS__VIRTUAL
#define __SYS__VIRTUAL
#define SERVER "/global/virtual/server"
#define VR_HAND "/global/virtual/vr_hand.c"
#define VIRTUAL_HANDLER "/obj/handlers/virtuals"
#define CLONER "/global/cloner"
#define VIRTUAL_NAME_PROP "virtual name"
#endif

==================================================
FILE: virtual_room.h
==================================================

#ifndef __SYS__VIRTUAL_ROOM
#define __SYS__VIRTUAL_ROOM
#include <virtual.h>
#define FLAG 0
#define DELAY 1
#define CLONE 2
#define MESS 3
#define REMOVABLE 0
#define FIXED 1
#define UNIQUE 2
#endif

==================================================
FILE: virtual_spell.h
==================================================

#define TRICK_HANDLER     load_object( "/obj/spells/trick_handler" )
#define VIRTUAL_SPELL_OB  "/obj/spells/virtual_spell"
#define SET_STONE         "/obj/magic/lg_hag_stone_set"
#define UNSET_STONE       "/obj/magic/lg_hag_stone_unset"
#define VIRTUAL_SPELL_EFF "/std/effects/magic/virtual_spell"
#define SPELL_DIRECT_NON_LIVING 1
#define SPELL_DIRECT_LIVING     2
#define SPELL_UNDIRECTED        3
#define SPELL _spell->name
#define STAGE _spell->stages[ stage_num - 1 ]
#define STAGE_COST  20
#define DIFF_POWER  25
#define STAGE_TIME  10
class spell_stage {
  string skill;
  int difficulty;
  string tell_msg;
  string say_msg;
  string *consumed;
}
class spell_info {
  string name;
  int target_type;
  class spell_stage *stages;
  string *needed;
  string tell_final;
  string say_final;
}
class eff_args {
  object obj;
  class spell_info spell;
  int id;
}
#include <db.h>
#include <config.h>
#define DB            "discworld"
#define TRICKS        "Tricks"
#define USER_ID       CONFIG_DB_USER
#define PASSWORD      ""
#define MAXID         "max( TrickId )"
#define ID_EXISTS     1
#define DATA_EXISTS   2

==================================================
FILE: volumes.h
==================================================

#ifndef __VOLUMES_H
#define __VOLUMES_H
#define VOLUME_MINIMUM_DRINKABLE      50
#define VOLUME_PINT      2400
#define VOLUME_GILL      600
#define VOLUME_QUART     4800
#define VOLUME_GALLON    19200
#define VOLUME_HALFPINT  (VOLUME_PINT / 2)
#define VOLUME_LITRE     4200
#define VOLUME_SHOT      100
#define VOLUME_WINE      750
#define VOLUME_FLUTE     750
#define VOLUME_WINEBOTTLE  3100
#define VOLUME_BRANDY    1450
#define VOLUME_TUMBLER   1350
#define VOLUME_COCKTAIL  750
#define VOLUME_TEACUP    960
#define VOLUME_MUG       1450
#endif

==================================================
FILE: wander.h
==================================================

#ifndef __SYS__WANDER
#define __SYS__WANDER
#define WANDER_HANDLER "/obj/handlers/wander_handler"
#endif

==================================================
FILE: weapon.h
==================================================

#ifndef __SYS__WEAPON
#define __SYS__WEAPON
#define W_ARRAY_SIZE 5
#define W_CHANCE     0
#define W_DAMAGE     1
#define W_TYPE       2
#define W_SKILL      3
#define W_FUNCTION   4
#define F_FIXED  0
#define F_NUM    1
#define F_DIE    2
#define A_ARRAY_SIZE 2
#define A_NAME       0
#define A_TYPE       1
#define A_AC         0
#define AT_ARRAY_SIZE 4
#define AT_DAMAGE    0
#define AT_SKILL     1
#define AT_TYPE      2
#define AT_NAME      3
#endif

==================================================
FILE: weapon_old.h
==================================================

#ifndef __SYS__WEAPON
#define __SYS__WEAPON
#define W_ARRAY_SIZE 7
#define W_FLAG 0
#define W_CHANCE 1
#define W_BASE 2
#define W_HIT 3
#define W_DAM 4
#define W_TYPE 5
#define W_FUN 6
#define F_FIXED 0
#define F_NUM 1
#define F_DIE 2
#define F_RAND 1
#define A_ARRAY_SIZE 2
#define A_NAME 0
#define A_TYPE 1
#define A_AC 0
#endif

==================================================
FILE: weather.h
==================================================

#ifndef __SYS__WEATHER
#define __SYS__WEATHER
#define WEATHER "/obj/handlers/weather"
#define WEATHER_HANDLER WEATHER
#define WEATHER_NO_RAIN_TYPE 0
#define WEATHER_RAIN_TYPE 3
#define WEATHER_SLEET_TYPE 2
#define WEATHER_SNOW_TYPE 1
#define CLIMATES ({ "Af", "Am", "Aw", "Bw", "Bs", "Cfa", "Cs", "Cfb", \
                    "Dw", "Ds", "Df", "Et", "Ef", "H" })
#define DEFAULT_CLIMATE "Cfb"
#endif

==================================================
FILE: weezent.h
==================================================

#define WEEZENT                "/d/sur/Weezent/"
#define BETWEENS               WEEZENT +"betweens/"
#define UNIQUES                WEEZENT +"uniques/"
#define GRFLX_NEST             WEEZENT +"grflx_nest/"
#define UNDER_WELL             WEEZENT +"under_well/"
#define VILLAGE                WEEZENT +"village/"
#define CHARS                  WEEZENT +"chars/"
#define ITEMS                  WEEZENT +"items/"
#define UTILS                  WEEZENT +"utils/"
#define HOSPITAL               ( WEEZENT +"hospital" )

==================================================
FILE: shops/bank.h
==================================================

#ifndef __SHOPS_BANK_H
#define __SHOPS_BANK_H
#define BANK_CREDIT_NOTE "/obj/misc/bank_credit_note"
#define BANK_HANDLER "/obj/handlers/bank_handler"
#endif

==================================================
FILE: shops/craft_shop.h
==================================================

#ifndef __CRAFT_SHOP_H
#define __CRAFT_SHOP_H
#define CRAFT_SHOP_INHERIT "/std/shops/craft_shop"
#define CRAFT_SHOP_CONTROLLER "/std/shops/craft_shop_controller"
#define CRAFT_SHOP_MAX_NAME_LENGTH 50
#define CRAFT_SHOP_MAIN_SAVE_FILE 1
#define CRAFT_SHOP_DATA_SAVE_FILE 2
#define CRAFT_SHOP_REMOVE_DATA_SAVE_FILE 3
#define CRAFT_CATEGORY_STATE_NOMINATING 1
#define CRAFT_CATEGORY_STATE_VOTING     2
#define CRAFT_CATEGORY_STATE_ACCEPTED   3
#define CRAFT_CATEGORY_STATE_DELETEING  4
#define CRAFT_CATEGORY_CHOICE_YES 1
#define CRAFT_CATEGORY_CHOICE_NO 2
#define CRAFT_CATEGORY_CHOICE_ABSTAIN 3
#define CRAFT_CATEGORY_ERROR -1
#define CRAFT_SHOP_EXPRESSION_HELP_DIR "/doc/furniture/expressions/"
#endif

==================================================
FILE: shops/engrave.h
==================================================

#ifndef __SYS_SHOP_ENGRAVE
#define __SYS_SHOP_ENGRAVE
#define ENGRAVE_PROP "engraveable"
#endif

==================================================
FILE: shops/item_shop.h
==================================================

#ifndef __SYS_SHOPS_ITEM_SHOP
#define __SYS_SHOPS_ITEM_SHOP
#define ITEM_SHOP_INHERIT "/std/shops/item_shop"
#define ITEM_SHOP_OUTSIDE_INHERIT "/std/shops/item_shop_outside"
#define ITEM_SHOP_ITEMS "/obj/misc/shops/"
#define ITEM_SHOP_EVENT_CLOSE "close"
#define ITEM_SHOP_EVENT_NOTHING "nothing"
#define ITEM_SHOP_EVENT_NOTHING "nothing"
#define ITEM_SHOP_EVENT_LIST "list"
#define ITEM_SHOP_EVENT_BAD_LABEL "bad_label"
#define ITEM_SHOP_EVENT_SOLD_OUT "sold_out"
#define ITEM_SHOP_EVENT_TOO_EXPENSIVE "too_expensive"
#define ITEM_SHOP_EVENT_BROWSE "browse"
#define ITEM_SHOP_EVENT_BUY_THING "buy_thing"
#endif

==================================================
FILE: shops/newspaper_archive.h
==================================================

#ifndef __NEWSPAPER_HANDLER
#define __NEWSPAPER_HANDLER
#define NEWSPAPER_ARCHIVE_EVENT_NO_PAPERS "no_papers"
#define NEWSPAPER_ARCHIVE_EVENT_LIST "list"
#define NEWSPAPER_ARCHIVE_EVENT_INVALID_PAPER "invalid_paper"
#define NEWSPAPER_ARCHIVE_EVENT_INVALID_EDITION "invalid_edition"
#define NEWSPAPER_ARCHIVE_EVENT_TOO_POOR "too_poor"
#define NEWSPAPER_ARCHIVE_EVENT_MOVE_PAPER "move_paper"
#define NEWSPAPER_ARCHIVE_EVENT_BOUGHT "bought"
#endif

==================================================
FILE: shops/pub_shop.h
==================================================

#ifndef __SYS__PUB_SHOP
#define __SYS__PUB_SHOP
#define PUB_APPETISER   0
#define PUB_MAINCOURSE  1
#define PUB_DESSERT     2
#define PUB_ALCOHOL     3
#define PUB_SOFTDRINK   4
#define PUB_HOTDRINK    5
#define PUB_MENU_FILE     "/obj/misc/menu"
#define PUB_COUNTER_FILE  "/std/shops/objs/counter"
#define PUB_GLASS_PATH    "/obj/misc/glasses/"
#define PUB_STD_TANKARD   PUB_GLASS_PATH + "std_tankard.ob"
#define PUB_STD_PINT      PUB_GLASS_PATH + "std_pint_glass.ob"
#define PUB_STD_HALFPINT  PUB_GLASS_PATH + "std_half_glass.ob"
#define PUB_STD_SHOT      PUB_GLASS_PATH + "std_shot_glass.ob"
#define PUB_STD_WINE      PUB_GLASS_PATH + "std_wine_glass.ob"
#define PUB_STD_BRANDY    PUB_GLASS_PATH + "std_brandy_glass.ob"
#define PUB_STD_TUMBLER   PUB_GLASS_PATH + "std_tumbler.ob"
#define PUB_STD_COCKTAIL  PUB_GLASS_PATH + "std_cocktail_glass.ob"
#define PUB_STD_FLUTE     PUB_GLASS_PATH + "std_flute_glass.ob"
#define PUB_STD_TEACUP    PUB_GLASS_PATH + "std_teacup.ob"
#define PUB_STD_MUG       PUB_GLASS_PATH + "std_mug.ob"
#define PUB_PLATE_PATH    "/obj/misc/plates/"
#define PUB_STD_PLATE         PUB_PLATE_PATH + "std_plate.ob"
#define PUB_STD_DISH          PUB_PLATE_PATH + "std_dish.ob"
#define PUB_STD_BOWL          PUB_PLATE_PATH + "std_bowl.ob"
#define PUB_STD_SOUPDISH      PUB_PLATE_PATH + "std_soup_dish.ob"
#define PUB_STD_DINNERPLATE   PUB_PLATE_PATH + "std_dinner_plate.ob"
#define PUB_STD_SIDEPLATE     PUB_PLATE_PATH + "std_side_plate.ob"
#define PUB_STD_DESSERTPLATE  PUB_PLATE_PATH + "std_dessert_plate.ob"
#define PUB_STD_DESSERTDISH   PUB_PLATE_PATH + "std_dessert_dish.ob"
class menu_item {
   int type;
   int cost;
   string item;
   string container;
   int volume;
   int intox;
}
#define PUB_EVENT_NOT_AVAILABLE "not_available"
#define PUB_EVENT_NOT_OPEN "not_open"
#define PUB_EVENT_BOUGHT_STUFF "bought_stuff"
#define PUB_EVENT_DEAD_PEOPLE "dead_people"
#define PUB_EVENT_FAILED_PEOPLE "failed_people"
#define PUB_EVENT_POOR_PERSON "poor_people"
#endif

==================================================
FILE: room/auction.h
==================================================

#ifndef __SYS_ROOM_AUCTION_H
#define __SYS_ROOM_AUCTION_H
#define AUCTION_FINISH_PHASE 1
#define AUCTION_WITHDRAW_PHASE 2
#define AUCTION_CLAIM_PHASE 3
#define AUCTION_RETRY_PHASE 4
#define AUCTION_EVENT_LIST "list"
#define AUCTION_EVENT_BROWSE "browse"
#define AUCTION_EVENT_BAD_ITEM "bad_item"
#define AUCTION_EVENT_BID_TOO_SMALL "bid_to_small"
#define AUCTION_EVENT_BID_BELOW_RESERVE "bid_below_reserve"
#define AUCTION_EVENT_BID "bid"
#define AUCTION_EVENT_TOO_POOR "too_poor"
#define AUCTION_EVENT_WITHDRAW "withdraw"
#define AUCTION_EVENT_CANNOT_WITHDRAW "cannot_withdraw"
#define AUCTION_EVENT_CLAIM "claim"
#define AUCTION_EVENT_NOTHING_TO_CLAIM "nothing_to_claim"
#define AUCTION_EVENT_FULL "full"
#define AUCTION_EVENT_BAD_MONEY "bad_money"
#define AUCTION_EVENT_ADD_AUCTION "add_auction"
#define AUCTION_EVENT_ADD_ABORT "add_abort"
#define AUCTION_EVENT_CONFIRM_AUCTION "confirm_auction"
#define AUCTION_EVENT_INFO "info"
#endif

==================================================
FILE: room/card_base.h
==================================================

#ifndef __CARD_BASE_H
#define __CARD_BASE_H
#define CARD_SUIT_HEARTS   1
#define CARD_SUIT_DIAMONDS 2
#define CARD_SUIT_CLUBS    3
#define CARD_SUIT_SPADES   4
#define CARD_SUIT_JOKER    5
#define CARD_NUMBER_JACK    11
#define CARD_NUMBER_QUEEN   12
#define CARD_NUMBER_KING    13
#define CARD_NUMBER_ACE     1
#define CARD_HAND_THREE         1
#define CARD_HAND_SINGLE        2
#define CARD_HAND_TWO           4
#define CARD_HAND_NO_ADORNMENTS 8
#define CARD_HAND_LETTERS       16
#ifndef CARD_BASE_NO_CLASSES
class playing_card {
   int suit;
   int number;
}
#endif
#endif

==================================================
FILE: room/carriage.h
==================================================

#ifndef __CARRIAGE_H__
#define __CARRIAGE_H__
class stop_details {
   string name;
   string path;
   int delay;
}
class stop_list_details {
   string id;
   int travel_time;
}
class route_details {
   string colour;
   int return_along;
   class stop_list_details* stops;
}
#define CARRIAGE_HANDLER_INHERIT "/std/room/inherit/carriage/handler"
#define CARRIAGE_CARRIAGE_INHERIT "/std/room/inherit/carriage/carriage"
#define CARRIAGE_CARRIAGE_POLE "/std/room/inherit/carriage/carriage_pole"
#endif

==================================================
FILE: room/club_room.h
==================================================

#ifndef __ROOM_CLUB_ROOM_H
#define __ROOM_CLUB_ROOM_H
#define CLUB_ROOM_CONTROLLER_DISCUSSED 0
#define CLUB_ROOM_CONTROLLED_FIXED     1
#define CLUB_ROOM_OWNED_PERSON   0
#define CLUB_ROOM_OWNED_POSITION 1
#define CLUB_ROOM_BOARD_COUNT "board count"
#define CLUB_ROOM_POSITION_START "position "
#define CLUB_ROOM_CONTROLLER_SAVE_FILE "club_controller"
#endif

==================================================
FILE: room/document_handler.h
==================================================

#ifndef __DOCUMENT_HANDLER_H
#define __DOCUMENT_HANDLER_H
#define DOCUMENT_HTML  2
#define DOCUMENT_NROFF 1
#define DOCUMENT_PLAIN 0
#endif

==================================================
FILE: room/newspaper.h
==================================================

#ifndef __NEWSPAPER_H
#define __NEWSPAPER_H
#define NEWSPAPER_PRESS_CREDITIALS "/obj/misc/press_credentials"
#define NEWSPAPER_HANDLER "/obj/handlers/newspaper"
#define NEWSPAPER_OB "/obj/misc/newspaper"
#define NEWSPAPER_SUBSCRIPTION_OB "/obj/furnitures/misc/newspaper_box"
#define NEWSPAPER_WWW_LOGO_BASE "/external/newspaper/logos/logo"
#define NEWSPAPER_ARTICLE_TYPE_PLAIN 1
#define NEWSPAPER_ARTICLE_TYPE_HTML 2
#define NEWSPAPER_ARTICLE_TYPE_NROFF 3
#define NEWSPAPER_ARTICLE_TYPE_SECTION 4
#define NEWSPAPER_ARTICLE_TYPE_ADVERTS 5
#define NEWSPAPER_ARTICLE_TYPE_MASK 7
#define NEWSPAPER_ARTICLE_ANONYMOUS_FLAG 1024
#define NEWSPAPER_ARTICLE_NO_XP_FLAG     2048
#define NEWSPAPER_WEB_HIT_REVENUE 40
#define NEWSPAPER_XP_PER_ARTICLE 60000
#define NEWSPAPER_XP_EDITOR 120000
class article {
   string file_name;
   string title;
   string author;
   int date_written;
   int type;
   string shown_name;
   string colour;
}
class advert {
   string text;
   string author;
   string category;
   int date_written;
   int value;
}
#endif

==================================================
FILE: room/placement.h
==================================================

#ifndef __ROOM_PLACEMENT_H__
#define __ROOM_PLACENENT_H__
#define PLACEMENT_CURRENT_ROOM_VERB "current room verb"
#define PLACEMENT_CURRENT_ROOM_OTHER "current room other"
#define PLACEMENT_CURRENT_ROOM_POSITION "current room position"
#define PLACEMENT_IMMOVABLE "immovable"
#endif

==================================================
FILE: room/room_rental.h
==================================================

#ifndef __ROOM_RENTAL_H
#define __ROOM_RENTAL_H
#define ROOM_RENTAL_HANDLER               "/obj/handlers/room_rental"
#define ROOM_RENTAL_SAVE_FILE             "/save/rental_save_file"
#define ROOM_RENTAL_INHERIT_ROOM          "/std/room/inherit/room_rental"
#define ROOM_RENTAL_INHERIT_OFFICE        "/std/room/inherit/room_rental_office"
#define ROOM_RENTAL_INHERIT_BASIC_ROOM    "/std/room/room_rental"
#define ROOM_RENTAL_INHERIT_BASIC_OFFICE  "/std/room/room_rental_office"
#define RENTAL_SUCCESS         0
#define RENTAL_NO_SUCH_ROOM    1
#define RENTAL_ALREADY_RENTED  2
#define RENTAL_AVAILABLE       3
#define RENTAL_NO_MONEY        4
#define ONE_DAY                86400
#endif

==================================================
FILE: effects/stat_adjustment.h
==================================================

#ifndef __STAT_ADJUSTMENT
#define __STAT_ADJUSTMENT
#define STAT_ADJUSTMENT_EFFECT "/std/effects/attached/stat_adjustment"
#endif

==================================================
FILE: npc/ai.h
==================================================

#ifndef __NPC_AI_H__
#define __NPC_AI_H__
#define AI_NPC_INHERIT "/std/npc/npc_intelligent"
#endif

==================================================
FILE: npc/events.h
==================================================

#ifndef __NPC_EVENTS_H__
#define __NPC_EVENTS_H__
#define EVENT_LOSE_HPS "lose hps"
#define EVENT_GAIN_HPS "gain hps"
#define EVENT_FULLY_HEALED "100% hps"
#define EVENT_75PERCENT_HPS "75% hps"
#define EVENT_50PERCENT_HPS "50% hps"
#define EVENT_25PERCENT_HPS "25% hps"
#define EVENT_MOVED "moved"
#define EVENT_GIVEN "given"
#define EVENT_PLAN_FINISHED_TAG "plan finished : "
#define EVENT_PLAN_FINISHED(PLAN) (EVENT_PLAN_FINISHED_TAG + PLAN)
#endif

==================================================
FILE: npc/goals.h
==================================================

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

==================================================
FILE: npc/plan.h
==================================================

#ifndef __NPC_PLAN_H__
#define __NPC_PLAN_H__
#define PLAN_DIR "/std/npc/plans/"
#define PLAN_BASE_INHERIT (PLAN_DIR "base")
#define PLAN_INVALID_SUTABILITY -1
#define PLAN_LOWEST_SUTABILITY 0
#define PLAN_LOW_SUTABILITY 100
#define PLAN_MEDIUM_SUTABILITY 200
#define PLAN_HIGH_SUTABILTIY 300
#endif

==================================================
FILE: npc/transport.h
==================================================

#ifndef __NPC_TRANSPORT_H
#define __NPC_TRANSPORT_H
#define RIDE_NOT_MOVING   0
#define RIDE_WALK   1
#define RIDE_TROT   2
#define RIDE_CANTER 3
#define RIDE_GALLOP 4
#define TRANSPORT_REPEATER "/std/npc/types/helper/repeater"
#define TRANSPORT_EFFECT   "/std/effects/attached/riding"
#define TRANSPORT_OWNER_EFFECT "/std/effects/attached/owned_transport"
#define TRANSPORT_ALLOW_PROP "transport allow"
#define TRANSPORT_INHERIT "/std/npc/types/transport"
#define TRANSPORT_TETHER_PROP "tether"
#define TRANSPORT_TETHER_POST_PROP "tether post"
#endif

==================================================
FILE: cmds/bury.h
==================================================

#ifndef __BURY_H
#define __BURY_H
#define BURY_EFFECT "/std/effects/room/burial"
#define BURY_TIMEOUT (5 * 60)
#define BURY_PROPERTY "bury location"
#endif

==================================================
FILE: cmds/friends.h
==================================================

#ifndef __CMDS_FRIENDS_H__
#define __CMDS_FRIENDS_H__
#define FRIENDS_CMD "/cmds/player/friend_s"
#endif

==================================================
FILE: cmds/guild_base.h
==================================================

class teach_skill  {
   string skill;
   int teach;
   int learn;
}

==================================================
FILE: cmds/offer.h
==================================================

#ifndef __OFFER_NPC_H__
#define __OFFER_NPC_H__
class offer_sale {
   int value;
   string place;
   object *sell_obs;
   object seller;
   object buyer;
}
#endif

==================================================
FILE: cmds/options.h
==================================================

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

==================================================
FILE: cmds/teach.h
==================================================

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

==================================================
FILE: cmds/twiki.h
==================================================

#ifndef __TWIKI_H
#define __TWIKI_H
#define TWIKI_HANDLER "/obj/handlers/twiki"
#endif
