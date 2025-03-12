#include <effect.h>
#include <disease.h>
inherit SIMPLE_DISEASE;
void setup() {
   set_name( "Fleas" );
   set_classification( "disease.parasite.external.flea" );
  set_infection_chance( 2 );
   set_infection_check( (: living( $1 ) &&
               ( ( !userp( $1 ) && !$1->query_property( "unique" ) ) ||
               $1->query_mature() ) && !$1->query_property( "dead" ) :) );
}
int disease_start( object player, int arg, int ) {
   string race_ob;
   race_ob = (string)player->query_race_ob();
   if ( ( (string)race_ob->query_name() == "troll" ) ||
         player->query_property( "no fleas" ) ) {
      player->submit_ee( 0, 0, EE_REMOVE );
      return 0;
   }
   return arg;
}
void disease_action( object player, int, int ) {
   switch( random( 14 ) ) {
      case 0 .. 3 :
         player->remove_hide_invis( "hiding" );
         tell_object( player, "Something itches.  You scratch yourself.\n" );
         tell_room( environment( player ), (string)player->one_short() +
               " scratches "+ (string)player->query_objective() +"self.\n",
               player );
         break;
      case 4 .. 7 :
         player->remove_hide_invis( "hiding" );
         tell_object( player, "Ouch!  Something bit you!\n" );
         tell_room( environment( player ), (string)player->one_short() +
               " starts as if bitten.\n", player );
         player->adjust_hp( -10 - random( 10 ) );
         break;
      case 8 .. 11 :
         tell_object( player, "You notice a small red welt on your skin.\n" );
         break;
      default:
   }
   if(!random(10) && !userp(player))
     player->submit_ee(0, 0, EE_REMOVE);
}
int test_remove( object player, int arg, int enum, int bonus ) {
   log_file( "OLD_CURE", file_name( previous_object() ) +" "+
            file_name( this_object() ) +"\n" );
   if ( arg + bonus < 30 ) {
      player->set_arg_of( enum, arg + bonus );
      return 0;
   }
   return 1;
}