#include <good_fighter.h>
#define LOGFILE "good_fighter"
#define CMDS "/cmds/guild-race/fighting/"
#define DEBUG
inherit "/std/effect_shadow";
#define W_ATTACKS ([ "crush"   : "crush $N with $W", \
                     "behead"  : "behead $N with $W", \
                     "impale"  : "impale $N with $W", \
                     "stab"    : "stab $N with $W", \
                     "pierce"  : "pierce $N with $W", \
                     "bash"    : "bash $N with $W", \
                     "smash"   : "smash $N with $W", \
                     "slash"   : "slash $N with $W", \
                     "slice"   : "slice $N with $W", \
                     "hack"    : "hack $N with $W", \
                     "chop"    : "chop $N with $W", \
                     "feint"   : "feint at $N with $W" ])
#define U_ATTACKS ([ "trip"    : "trip $N", \
                     "shove"   : "shove $N" ])
string *specials;
mapping weapons;
int bluntorsharp;
int dodgeorparry;
object victim;
void create()
{
  specials = ({ });
  weapons = ([ ]);
}
protected void check_skill(string skill, int level)
{
  int cur;
  cur = player->query_skill(skill);
  if (cur < level)
    player->add_skill_level(skill, level - cur);
}
protected void check_add_command(string command, string skill, int level)
{
  int cur;
  cur = player->query_skill(skill);
  if (cur >= level) {
    player->add_known_command(command);
    specials += ({ command });
  }
}
void good_fighter_setup()
{
  int adjust;
  int lvl;
  int *args = arg();
  if (!args || !arrayp(args) || sizeof(args) != 2)
    return;
  specials = ({ });
  bluntorsharp = args[0];
  dodgeorparry = args[1];
  lvl = player->query_level();
  check_skill("other.perception", lvl / 2);
  check_skill("other.health", lvl);
  adjust += (lvl / 3);
  if (bluntorsharp == USE_PIERCE) {
    check_skill("fighting.combat.melee.blunt", lvl - adjust);
    check_skill("fighting.combat.melee.sharp", lvl - adjust);
    check_skill("fighting.combat.melee.pierce", lvl + adjust);
    check_skill("fighting.combat.melee.unarmed", lvl - adjust);
  } else if (bluntorsharp == USE_BLUNT) {
    check_skill("fighting.combat.melee.blunt", lvl + adjust);
    check_skill("fighting.combat.melee.sharp", lvl - adjust);
    check_skill("fighting.combat.melee.pierce", lvl - adjust);
    check_skill("fighting.combat.melee.unarmed", lvl - adjust);
  } else if (bluntorsharp == USE_SHARP) {
    check_skill("fighting.combat.melee.blunt", lvl - adjust);
    check_skill("fighting.combat.melee.sharp", lvl + adjust);
    check_skill("fighting.combat.melee.pierce", lvl - adjust);
    check_skill("fighting.combat.melee.unarmed", lvl - adjust);
  } else if (bluntorsharp == USE_UNARMED) {
    check_skill("fighting.combat.melee.blunt", lvl - adjust);
    check_skill("fighting.combat.melee.sharp", lvl - adjust);
    check_skill("fighting.combat.melee.pierce", lvl - adjust);
    check_skill("fighting.combat.melee.unarmed", lvl + adjust);
  } else {
    check_skill("fighting.combat.melee.blunt", lvl);
    check_skill("fighting.combat.melee.sharp", lvl);
    check_skill("fighting.combat.melee.pierce", lvl);
    check_skill("fighting.combat.melee.unarmed", lvl);
  }
  adjust = lvl * 2 / 3;
  if (dodgeorparry == DEFEND_DODGE) {
    check_skill("fighting.combat.dodging", lvl + adjust);
    check_skill("fighting.combat.parry", lvl - adjust);
    player->init_command("tactics response dodge", 1);
  } else if (dodgeorparry == DEFEND_PARRY) {
    check_skill("fighting.combat.dodging", lvl - adjust);
    check_skill("fighting.combat.parry", lvl + adjust);
    player->init_command("tactics response parry", 1);
  } else {
    check_skill("fighting.combat.dodging", lvl);
    check_skill("fighting.combat.parry", lvl);
    player->init_command("tactics response neutral", 1);
  }
  check_skill("fighting.combat.special", lvl / 2);
  check_skill("fighting.points", lvl * 2);
  player->init_command("tactics attitude offensive", 1);
  if (bluntorsharp != USE_BLUNT) {
    if (dodgeorparry == DEFEND_PARRY)
      check_add_command("riposte", "fighting.combat.special", 15);
    if (bluntorsharp == USE_SHARP || bluntorsharp == USE_BALANCED)  {
      check_add_command("hack", "fighting.combat.special", 15);
      check_add_command("slash", "fighting.combat.special", 15);
      check_add_command("slice", "fighting.combat.special", 75);
      check_add_command("chop", "fighting.combat.special", 75);
      if (player->query_guild_ob() == "/std/guilds/warrior")
        check_add_command("behead", "fighting.combat.special", 150);
    }
    if (bluntorsharp == USE_PIERCE) {
      check_add_command("stab", "fighting.combat.special", 15);
      check_add_command("pierce", "fighting.combat.special", 75);
      if (player->query_guild_ob() == "/std/guilds/warrior")
        check_add_command("impale", "fighting.combat.special", 150);
    }
  } else {
    check_add_command("bash", "fighting.combat.special", 15);
    check_add_command("smash", "fighting.combat.special", 75);
    if (player->query_guild_ob() == "/std/guilds/warrior")
      check_add_command("crush", "fighting.combat.special", 150);
  }
  check_add_command("feint", "fighting.combat.special", 15);
  check_add_command("trip", "fighting.combat.special", 15);
  check_add_command("shove", "fighting.combat.special", 15);
  player->add_known_command("concentrate");
}
protected int check_weapon(object weapon, string command) {
  if(!weapon->query_attack_names())
    return 0;
  switch(command) {
  case "crush":
    command = "smash";
    break;
  case "behead":
    command = "slice";
    break;
  case "impale":
    command = "impale";
    break;
  case "riposte":
    command = "slash";
    break;
  case "feint":
    return 1;
  }
  return (member_array(command, weapon->query_attack_names()) != -1);
}
void event_fight_in_progress(object attacker, object opponent)
{
  object ts, weapon;
  int chance;
  string cmd;
  ts = player;
  ts->event_fight_in_progress(attacker, opponent);
  if(ts->query_specific_gp("fighting") < 50)
    return;
  if (victim && !objectp(victim))
    victim = 0;
  if (victim && !interactive(victim))
    victim = 0;
  if (victim && environment(victim) != environment(player))
    victim = 0;
  if (victim && victim != attacker)
    return;
  if (!victim) {
    if(member_array(attacker, ts->query_attacker_list()) != -1)
       victim = attacker;
    if (!victim)
      return;
  }
  if(!sizeof(player->query_weapons()) &&
     player->query_combat_attitude() != "wimp" &&
     arg()[0] != USE_UNARMED) {
    object *shields;
    player->queue_command("tactics attitude wimp", 1);
    shields = filter(player->query_holding(), (: $1 && $1->id("shield") :));
    if(!sizeof(shields)) {
      if(player->query_race_ob() == "/std/races/troll") {
        if(!player->query_unarmed_parry())
          player->queue_command("tactics parry unarmed");
      } else {
        player->queue_command("tactics response dodge", 2);
      }
    }
  }
  chance = (player->query_level() / 12) + 5;
  if(chance > 25)
    chance = 25;
  if(sizeof(player->query_specials()))
    chance /= (sizeof(player->query_specials()) * 10);
  if(random(100) + 1 < chance) {
    string *candidates;
    int i;
    candidates = ({ });
    foreach(weapon in player->query_weapons()) {
      if(!weapons[weapon]) {
        weapons[weapon] = ({ });
        for (i = 0; i < sizeof(specials); i++)
          if(W_ATTACKS[specials[i]] && check_weapon(weapon, specials[i])) {
            weapons[weapon] += ({ replace(W_ATTACKS[specials[i]], "$W",
                                          weapon->query_short()) });
          }
      }
      candidates += weapons[weapon];
    }
    if(!weapons["unarmed"]) {
      weapons["unarmed"] = ({ });
      for(i=0; i<sizeof(specials); i++)
        if(U_ATTACKS[specials[i]])
          weapons["unarmed"] += ({ U_ATTACKS[specials[i]] });
    }
    candidates += weapons["unarmed"];
#ifdef DEBUG
#endif
    if(sizeof(candidates)) {
      cmd = replace(candidates[random(sizeof(candidates))], "$N",
                    victim->query_name());
#ifdef DEBUG
      debug_printf("Trying to perform: %O", cmd);
#endif
      player->do_command(cmd, 1);
    } else {
#ifdef DEBUG
      debug_printf("No command to perform");
#endif
    }
  }
}
mixed *stats()
{
  if (!player || !objectp(player))
    return ({ ({ "good fighter", "unattached" }) });
  return player->stats() + ({
    ({ "good fighter",
      ((bluntorsharp == USE_BLUNT) ? "blunt" :
        ((bluntorsharp == USE_PIERCE) ? "pierce" :
          ((bluntorsharp == USE_SHARP) ? "sharp" : "balanced"))) +
      ((dodgeorparry == DEFEND_DODGE) ? " dodger" :
        ((dodgeorparry == DEFEND_PARRY) ? " parrier" : " fighter")) }),
    ({ "managed commands", implode(specials, ", ") })
  });
}