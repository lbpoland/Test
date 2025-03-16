#include <effect.h>
string query_classification() { return "mudlib.snowball"; }
void beginning( object player, int amount, int id ) {
   player->add_extra_look( this_object() );
   player->submit_ee( "decrease_amount", 15, EE_CONTINUOUS );
}
void restart( object player, int amount, int id ) {
   player->add_extra_look( this_object() );
}
int merge_effect( object player, int old_amount, int new_amount, int id ) {
   return old_amount + new_amount;
}
void end( object player, int amount, int id ) {
   player->remove_extra_look( this_object() );
}
void decrease_amount( object player, int amount, int id ) {
   amount -= 3 + random( random(amount) );
   if ( amount < 0 ) {
      amount = 0;
      player->submit_ee( 0, 1, EE_REMOVE );
   }
   player->set_arg_of( (int)player->sid_to_enum( id ), amount );
   player->add_effect("/std/effects/other/wetness", roll_MdN( 10, 10 ) );
}
string extra_look( object player ) {
   int *enums;
   string desc;
   enums = (int *)player->effects_matching( "mudlib.snowball" );
   if ( !sizeof( enums ) )
      return "";
   switch ( (int)player->arg_of( enums[ 0 ] ) ) {
      case 0 .. 99 :
         desc = " has a little bit of snow";
         break;
      case 100 .. 199 :
         desc = " has a bit of snow";
         break;
      case 200 .. 299 :
         desc = " has a few small lumps of snow";
         break;
      case 300 .. 399 :
         desc = " has a few lumps of snow";
         break;
      case 400 .. 499 :
         desc = " has a number of lumps of snow";
         break;
      case 500 .. 599 :
         desc = " has quite a lot of snow";
         break;
      case 600 .. 699 :
         desc = " has a lot of snow";
         break;
      default :
         desc = " has a thick layer of snow";
   }
   return capitalize( (string)player->query_pronoun() ) + desc +" on "+
         (string)player->query_possessive() +" face.\n";
}