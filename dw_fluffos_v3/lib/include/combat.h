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