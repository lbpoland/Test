#include "path.h"
#include <effect.h>
#include <weather.h>
#define MAX_EFFECT 200
#define MAX_DURATION 120
#define MAX_STRENGTH 240
#define MIN_STRENGTH 20
string query_classification() { return "body.wetness"; }
int beginning( object player, int wetness, int id ) {
  int dryness;
  tell_object( player, "Squelch.\n" );
  player->submit_ee( "squelch", ({ 20, 20 }), EE_CONTINUOUS );
  player->add_extra_look( this_object() );
  if(dryness = (int)player->check_dryness())
    wetness -= dryness;
  if ( wetness > (int)player->query_weight() )
    wetness = (int)player->query_weight();
  return wetness;
}
void restart( object player ) {
  player->add_extra_look( this_object() );
}
int merge_effect( object player, int new_wetness, int old_wetness, int id ) {
  int wetness, dryness;
  wetness = new_wetness + old_wetness;
  if(dryness = (int)player->check_dryness())
    wetness -= dryness;
  if ( wetness > (int)player->query_weight() )
      wetness = (int)player->query_weight();
  if ( wetness <= 0 )
    player->submit_ee(0, 0, EE_REMOVE );
  return wetness;
}
void end( object player, int strength, int id ) {
  tell_object(player, "You feel dry now.\n");
  player->remove_extra_look( this_object() );
}
void squelch(object player, int wetness, int id) {
  string loc;
  object env;
  int bingle;
  env = environment(player);
  if(!env)
    return;
  loc = (string)env->query_property("location");
  if(loc == "outside" && (int)WEATHER->query_temperature(env) > 0) {
    bingle = (int)WEATHER->query_temperature(env) / 2 +
      env->query_property("warmth");
  } else if(loc == "inside")
    bingle = (20 / 2) + env->query_property( "warmth" );
  if(player->query_personal_temp() / 3 > bingle)
    bingle -= (player->query_personal_temp() / 3);
  if(!env->query_water() && bingle > 0)
    wetness -= bingle;
  if(player->query_property("dead"))
    wetness = 0;
  if(wetness <= 0)
    player->submit_ee(0, 0, EE_REMOVE );
  if (wetness > 10 && !random(3) && !env->query_water() ) {
    tell_object(player, "Squelch.\n" );
  }
  player->set_arg_of(player->sid_to_enum(id), wetness);
}
string wet_string( object player, int self ) {
  int wetness;
  int *enums;
  enums = (int *)player->effects_matching( "body.wetness" );
  if ( !sizeof( enums ) )
    return "";
  wetness = (int)player->arg_of(enums[0]);
  if (!intp(wetness)) {
     wetness = 0;
     player->submit_ee(0, 0, EE_REMOVE );
  }
  switch ( ( wetness * 100 ) / ( 1 +
      (int)player->query_weight() ) ) {
    case 0 .. 5 :
      if (self)
        return "look slightly wet";
      else
        return "looks slightly wet";
    case 6 .. 10 :
      if (self)
        return "look rather wet";
      else
        return "looks rather wet";
    case 11 .. 30 :
      if (self)
        return "look wet and bedraggled";
      else
        return "looks wet and bedraggled";
    case 31 .. 80 :
      if (self)
        return "are soaked and don't look that well at all";
      else
        return "is soaked and doesn't look that well at all";
    case 81 .. 100 :
      if (self)
        return "look like you have just been dunked in a lake";
      else
        return "looks like "+ player->query_pronoun() +
          " has just been dunked in a lake";
      break;
    default :
      return "";
  }
}
string extra_look(object player)  {
   return capitalize(player->query_pronoun()) + " " + wet_string(player, 0) +
             ".\n";
}