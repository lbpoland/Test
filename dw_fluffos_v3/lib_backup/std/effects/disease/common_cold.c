#include <disease.h>
#include <effect.h>
inherit SIMPLE_DISEASE;
void setup() {
   set_name( "Common Cold" );
   set_cure_rate( 6 );
   set_classification( "disease.infection.respiratory.cold" );
}
int disease_start( object player, int arg, int sid ) {
   tell_object( player, "You realise that your nose is running.\n" );
   player->submit_ee2( sid, "sap_strength", ({ 600, 600 }), EE_CONTINUOUS );
   return arg;
}
void disease_end( object player, int arg, int sid ) {
   if ( !player->query_property( "dead" ) )
      tell_object( player, "You realise that your nose is clear again.\n" );
}
void disease_action( object player, int arg ) {
   switch ( random( 3 ) ) {
      case 0 :
         player->new_parser( "sniff" );
         break;
      case 1 :
         player->new_parser( "cough" );
         break;
      default :
         player->new_parser( "sneeze" );
   }
}
void sap_strength( object player ) {
   tell_object( player, "You feel your strength being sapped by the cold.\n" );
   player->adjust_tmp_str( -1 );
}