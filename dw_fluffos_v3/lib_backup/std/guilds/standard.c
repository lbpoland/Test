#include <skills.h>
#include <tune.h>
#include <guilds.h>
#include <config.h>
inherit "/std/object";
nosave string gp_skill;
nosave string start_pos;
nosave mixed *commands;
nosave string *skills;
nosave mixed *spells;
protected void create() {
   gp_skill = "other.points";
   start_pos = CONFIG_START_LOCATION;
   skills = ({ "crafts", "faith", "fighting", "other" });
   commands = ({ });
   spells = ({ });
   ::create();
}
string query_gp_skill() { return gp_skill; }
void set_gp_skill( string word ) { gp_skill = word; }
void set_gp( object thing ) {
   if ( !thing ) {
      return;
   }
   thing->set_max_gp( 50 + (int)thing->query_skill_bonus( gp_skill ) );
}
string query_start_pos( object thing ) { return start_pos; }
void set_start_pos( string word ) { start_pos = word; }
string *query_skills() { return skills; }
void set_skills( string *words ) { skills = words; }
int add_command(string name, int add_if_player) {
   if (member_array(name, commands) != -1) {
      return 0;
   }
   commands += ({ name, ({ add_if_player }) });
   return 1;
}
int remove_command(string name) {
   int i;
   if ((i = member_array(name, commands)) == -1) {
      return 0;
   }
   commands = delete(commands, i, 1);
   return 1;
}
int do_command(string name, mixed param) {
   log_file("BAD_COMMANDS", "do_command() called on /std/guilds/standard.c\n");
   return 0;
}
int add_spell(string name, mixed ob, string func_name, int add_if_player) {
   int i;
   if ((i = member_array(name, spells)) != -1) {
      return 0;
   }
   spells += ({ name, ({ ob, func_name, add_if_player }), });
   return 1;
}
int remove_spell(string name) {
   int i;
   if ((i= member_array(name, spells)) == -1) {
      return 0;
   }
   spells = delete(spells, i, 2);
   return 1;
}
int cast_spell(string name, mixed bing) {
   int i;
   if ((i=member_array(name, spells)) == -1) {
      return 0;
   }
   return (int)call_other(spells[i+1][0], spells[i+1][1], bing);
}
mixed *query_spells() { return spells; }
string *query_commands() { return commands; }
int query_skill_cost( string skill ) { return 10; }
int query_skill_max_level( string skill ) { return 10; }
void start_player(object pl) {
   int i;
   if (!spells) {
      spells = ({ });
   }
   for (i=0;i<sizeof(spells);i+=2) {
      if (spells[i+1][2] || !interactive(pl)) {
         pl->add_spell(spells[i], spells[i+1][0], spells[i+1][1]);
      }
   }
   if (!pointerp(commands)) {
      commands = ({ });
   }
   for (i=0;i<sizeof(commands);i+=2) {
      if (commands[i+1][0] || !interactive(pl)) {
         pl->add_known_command(commands[i]);
      }
   }
}
void leave_guild() { return; }
void player_quit() { return; }
void player_save() { return; }
void player_heart_beat( string guild, object thing ) {
}
void set_level( object thing, int level, string guild ) {
   call_out( "set_new_level", 1, ({ thing, level, guild }) );
}
string adjust_primaries( object thing, int level ) {
  int i;
  string stat_list;
  stat_list = "";
  for ( i = 0; i < sizeof( skills ); i++ ) {
    if(level - thing->query_skill(skills[i]) > 0)
      thing->add_skill_level(skills[i], level - thing->query_skill(skills[i]));
    stat_list += (string)SKILL_OB->query_skill_stat(skills[i]);
    if(random(2)) {
      stat_list += "C";
    }
  }
  return stat_list;
}
void set_new_level( mixed *args ) {
   int i, j, level;
   string stat_list;
   object thing;
   thing = args[ 0 ];
   if ( !thing ) {
      return;
   }
   level = args[ 1 ];
   thing->add_skill_level("fighting", level / 4 );
   thing->add_skill_level("other", level / 4 );
   switch(thing->query_guild_ob()) {
   case "/std/guilds/warrior":
   case "/std/guilds/assassin":
     thing->add_skill_level("other.health", level);
     break;
   case "/std/guilds/thief":
     thing->add_skill_level("other.health", (level * 3) / 4);
     break;
   default:
     thing->add_skill_level("other.health", level / 2);
   }
   thing->add_skill_level("other.perception", level / 3);
   stat_list = adjust_primaries( thing, level );
   if(thing->query_property( "unique" ) ||
      thing->query_property( "keep setup stats" ) ||
      (!thing->query_race_ob() ||
       !(thing->query_race_ob())->query_humanoid()))
     return;
   thing->adjust_con( -6 + random( 3 ) );
   thing->adjust_dex( -6 + random( 3 ) );
   thing->adjust_int( -6 + random( 3 ) );
   thing->adjust_str( -6 + random( 3 ) );
   thing->adjust_wis( -6 + random( 3 ) );
   for ( i = 0; i < 25; i++ ) {
      j = random( strlen( stat_list ) );
      switch ( stat_list[ j .. j ] ) {
         case "C" :
            thing->adjust_con( 1 );
            break;
         case "D" :
            thing->adjust_dex( 1 );
            break;
         case "I" :
            thing->adjust_int( 1 );
            break;
         case "S" :
            thing->adjust_str( 1 );
            break;
         default :
            thing->adjust_wis( 1 );
            break;
      }
   }
}
int query_level( object thing ) {
   int i, lvl;
   if ( !thing || !sizeof( skills ) ) {
      return 0;
   }
   for ( i = 0; i < sizeof( skills ); i++ ) {
      lvl += (int)thing->query_skill( skills[ i ] );
   }
   lvl /= sizeof( skills );
   return lvl;
}
string query_title( object player ) { return "the Adventurer"; }
void skills_advanced( object thing, string skill, int level ) {
   if ( strsrch( skill, "covert" ) != -1 ) {
      if ( ( (int)thing->query_skill( "covert.stealth" ) > 5 ) &&
             !thing->query_known_command( "peek" ) ) {
         tell_object( thing, "You realise that you could use your newly "
                      "improved stealth to \"peek\" covertly at someone, and "
                      "maybe they won't notice...\n" );
         thing->add_known_command( "peek" );
      }
   } else if ( strsrch( skill, "fighting.combat.parry.held" ) != -1 ) {
      if ( ( (int)thing->query_skill( "fighting.combat.parry.held" ) > 50 ) &&
                  !thing->query_known_command( "riposte" ) ) {
         tell_object( thing, "You realise that you could use your newly "
                     "improved parry to \"riposte\" someones attack.\n" );
         thing->add_known_command( "riposte" );
      }
   }
}
int add_position( string sub_guild, string position,
                           int max, string* abilities, mixed* description ) {
    return POSITION_FAIL;
}
int remove_position( string sub_guild, string position ) {
    return POSITION_FAIL;
}
mapping query_positions( string sub_guild, string position ) {
    return 0;
}
string *query_position_appointments( string sub_guild, string position ) {
    return 0;
}
mixed *query_position_description( string sub_guild, string position ) {
    return 0;
}
string *query_position_abilities( string sub_guild, string position ) {
    return 0;
}
void reset_positions( string sub_guild ) {
}
int appoint_position( string sub_guild, string position,
                                 string player_name ) {
    return POSITION_FAIL;
}
int dismiss_position( string sub_guild, string position,
                                 string player_name ) {
    return POSITION_FAIL;
}
string query_position( string sub_guild, string player_name ) {
    return 0;
}
int query_guild_ability( mixed thing, string ability ) {
    return 0;
}