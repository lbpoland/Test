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