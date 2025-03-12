#include <tasks.h>
#define QUEST_MAX 570
#define INFORM
inherit "/std/effect_shadow";
string *data;
void set_data( string *words ) { data = words; }
mapping special_attack( object target ) {
   int i, damage, skill;
   object *args;
   mixed *attacks;
   args = arg();
   if (!args) {
      return 0;
   }
   if ( !data || ( (string)player->query_combat_attitude() != "offensive" ) ||
         ( target != args[ 0 ] ) || !args[ 1 ] ) {
      tell_object( player, "You lose the moment!\n" );
      set_arg( 0 );
      remove_this_effect();
      return ([ ]);
   }
   if ( ( (object)args[ 1 ]->query_wielded() != player ) &&
         ( args[ 1 ] != player ) ) {
      tell_object( player, "What did you do with "+
            (string)args[ 1 ]->the_short() +"?\n" );
      set_arg( 0 );
      remove_this_effect();
      return ([ ]);
   }
   if((object)environment(target) != (object)environment(player)) {
     tell_object(player, "Where did "+target->short()+" go?\n");
     remove_this_effect();
     return ([ ]);
   }
   attacks = (mixed *)args[ 1 ]->weapon_attacks( 100, target );
   if ( !sizeof( attacks ) )
   {
      return 0;
   }
   for ( i = 0; i < sizeof( attacks ); i += 4 ) {
      if (attacks[i + 2] == data[1] ||
            attacks[i + 2][0..sizeof(data[1])] == data[1] + "-")
        damage += attacks[ i ];
   }
   if ( !damage ) {
     tell_object( player, "You manage to botch your use of "+
                  ( args[ 1 ] == player ? "unarmed combat" :
                    (string)args[ 1 ]->the_short() ) +
                  " and barely launch a mediocre attack at "+
                  (string)target->the_short() +".\n" );
#ifdef INFORM
    event(environment(player), "inform", (string)player->query_name() +
          " special manoeuvre failed (no damage)", "combat");
#endif
     return 0;
   }
   skill = (int)player->query_skill_bonus( "fighting.combat.melee."+
         data[ 0 ] );
   switch( (int)TASKER->perform_task(player, "fighting.combat.melee."+data[0],
                                     damage, TM_COMMAND) ) {
      case AWARD :
        tell_object( player, "%^YELLOW%^"+ replace( ({ "You feel that "+
               "your skill with $weapon$ has increased.", "You feel "+
               "more able to use $weapon$.", "You seem to be a step "+
               "closer to mastering $weapon$." })[ random( 3 ) ],
               "$weapon$", ( args[ 1 ] == player ? "unarmed combat" :
               (string)args[ 1 ]->a_short() ) ) +"%^RESET%^\n" );
      case SUCCEED :
         tell_object( player, "You launch a powerful attack on "+
               (string)target->the_short() + ( args[ 1 ] == player ? "" :
               " with "+ (string)args[ 1 ]->the_short() ) +".\n" );
         damage = sqrt( ((damage*2/3)) * skill ) + ( damage * skill ) /
           QUEST_MAX;
#ifdef INFORM
    event(environment(player), "inform", (string)player->query_name() +
          " special manoeuvre success, damage: " +damage, "combat");
#endif
         break;
      default :
        damage = 1;
         tell_object( player, "You manage to botch your use of "+
               ( args[ 1 ] == player ? "unarmed combat" :
               (string)args[ 1 ]->the_short() ) +
               " and barely launch a mediocre attack at "+
               (string)target->the_short() +".\n" );
#ifdef INFORM
    event(environment(player), "inform", (string)player->query_name() +
          " special manoeuvre failed", "combat");
#endif
   }
   set_arg( 0 );
   remove_this_effect();
   return ([ args[ 1 ] : ({ damage }) + data ]);
}
int tasking_done() { return 1; }