#include <effect.h>
#include "path.h"
#include "/std/living/stats.c"
#define CLASS "general.hp.drain"
string query_classification(){
  return CLASS;
}
string query_death_reason(){
  return "wasting away slowly";
}
void adjust_health( object player ){
  int damage,
    *enums = player->effects_matching( query_classification() );
  mixed *args;
  if( sizeof( enums ) ){
    args = player->arg_of( enums[ 0 ] );
  }
  tell_object( player, "You feel weak.\n" );
  damage = roll_MdN( 2, ( ( args[0] ) / 2 ) );
  if( ( player )->adjust_hp( -damage ) < 0 ){
    ( player )->attack_by( this_object() );
  }
  tell_creator( player,
                "Damage: " + damage + "\n" );
}
mixed  *beginning( object player, mixed *arg ){
  tell_object( player, arg[2][0] + "\n" );
  player->submit_ee( "adjust_health", ({ 5, 10 }),
                     EE_CONTINUOUS, player );
  player->submit_ee( 0, arg[1], EE_REMOVE );
  return arg;
}
mixed *merge_effect( object player, mixed *old_arg, mixed *arg ){
  arg[0] = ( old_arg[0] + arg[0] ) / 2;
  player->submit_ee( 0, arg[1] + player->expected_tt(), EE_REMOVE );
  return arg;
}
void end( object player, mixed *arg ){
  string *message = arg[2];
  tell_object( player, message[1] + "\n" );
}
void restart( object player, mixed *arg ){
  string *message = arg[2];
  tell_object( player, message[0] + "\n" );
}