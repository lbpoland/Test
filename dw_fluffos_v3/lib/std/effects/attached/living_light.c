#include "path.h"
#include <effect.h>
#define COST_PER_ROUND 30
#define INTENSITY 25
string query_classification() { return "magic.body.light"; }
int beginning( object player ) {
   tell_object( player, "A soft glow spreads out from your middle to "+
         "envelop you.\n" );
   tell_room( environment( player ), "A soft glow spreads out from "+
         (string)player->the_short() +"'s middle to envelop "+
         (string)player->query_objective() +".\n", player );
   player->adjust_light( INTENSITY );
   player->add_extra_look( this_object() );
   player->submit_ee( "decrease_points", 1, EE_ONCE );
   player->submit_ee( "decrease_points", ({ 30, 60 }), EE_CONTINUOUS );
   return INTENSITY;
}
void restart( object player, int light ) {
   player->adjust_light( light );
   player->add_extra_look( this_object() );
}
int merge_effect( object player, int light ) {
   int times;
   times = sizeof( filter_array( (object *)player->query_armours(),
         "test_for_effect", this_object() ) );
   if ( light >= ( INTENSITY * times ) )
      return light;
   tell_object( player, "The light surrounding you intensifies.\n" );
   tell_room( environment( player ), "The light around "+
         (string)player->short() +" grows brighter.\n", player );
   player->adjust_light( INTENSITY );
   return light + INTENSITY;
}
void end( object player, int light ) {
   tell_object( player, "The light surrounding you flickers and winks "+
         "out.\n" );
   tell_room( environment( player ), "The light around "+
         (string)player->short() +" flickers and winks out.\n", player );
   player->adjust_light( -light );
   player->remove_extra_look( this_object() );
}
int test_for_effect( object thing ) {
   if( !thing || !thing->query_wear_effects() )
     return 0;
   return member_array( file_name( this_object() ),
         (string *)thing->query_wear_effects() ) != -1;
}
void decrease_points( object player, int light, int id ) {
   int times;
   if ( player->query_auto_loading() )
      return;
   times = sizeof( filter_array( (object *)player->query_armours(),
         "test_for_effect", this_object() ) );
   if ( !times ) {
      player->submit_ee( 0, 0, EE_REMOVE );
      return;
   }
   if ( (int)player->query_gp() < times * COST_PER_ROUND ) {
      player->submit_ee( 0, 0, EE_REMOVE );
      return;
   }
   player->clear_gp_info();
   player->adjust_gp( - times * COST_PER_ROUND );
   if ( light != ( times * INTENSITY ) ) {
      tell_object( player, "The light surrounding you flickers and "+
            "stabilises, only a little dimmer than before.\n" );
      tell_room( environment( player ), "The light around "+
         (string)player->short() +" flickers and stabilises, only a "+
         "little dimmer than before.\n", player );
      player->adjust_light( times * INTENSITY - light );
      light = times * INTENSITY;
      player->set_arg_of( (int)player->sid_to_enum( id ), light );
   }
}
string extra_look( object player ) {
   return capitalize( (string)player->query_pronoun() ) +" is surrounded by "+
         "a soft yellow glow.\n";
}