#include "path.h"
#include <effect.h>
#include <player.h>
void beginning( object player, object *things, int id ) {
   tell_object( player, "You prepare to bob "+
         (string)things[ 0 ]->the_short() +".\n" );
   player->set_data( ({ "unarmed", "blunt", "hands" }) );
   player->submit_ee( 0, 10 * COMBAT_SPEED, EE_REMOVE );
}
void end( object player, object *things, int id ) {
   if ( sizeof( things ) )
      tell_object( player, "You missed your opportunity!\n" );
}
void restart( object player, object *things, int id ) {
   player->submit_ee( 0, 0, EE_REMOVE );
}
string query_classification() { return "fighting.combat.special.punch"; }
string query_shadow_ob() { return SHADOWS +"bob"; }