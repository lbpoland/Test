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