#include <effect.h>
string query_classification() { return "object.wet"; }
void beginning( object thing, int amount, int id ) {
   thing->submit_ee( "dry_off", ({ 30, 90 }), EE_CONTINUOUS );
   thing->add_extra_look( this_object() );
   thing->add_adjective("wet");
}
int merge_effect( object thing, int old_amount, int new_amount, int id ) {
   return old_amount + new_amount;
}
void end( object thing, int amount, int id ) {
   thing->remove_extra_look( this_object() );
   thing->remove_adjective("wet");
}
void restart( object thing, int amount, int id ) {
   thing->add_extra_look( this_object() );
}
void dry_off( object thing, int amount, int id ) {
   amount -= 100 + amount / 10;
   if ( amount > 0 )
      thing->set_arg_of( (int)thing->sid_to_enum( id ), amount );
   else
      thing->submit_ee( 0, 0, EE_REMOVE );
}
string wet_string( object thing ) {
   int *enums;
   string wetness;
   enums = (int *)thing->effects_matching( "object.wet" );
   if ( !sizeof( enums ) )
      return "";
   switch ( (int)thing->arg_of( enums[ 0 ] ) / ( 1 +
         (int)thing->query_weight() ) ) {
      case 0 :
         return "just barely damp";
      case 1 .. 5 :
         wetness = "slightly wet";
         break;
      case 6 .. 10 :
         wetness = "wet";
         break;
      case 11 .. 30 :
         wetness = "very wet";
         break;
      case 31 .. 80 :
         wetness = "sopping wet";
         break;
      default :
          wetness = "absolutely soaking wet";
   }
   return wetness;
}
string extra_look(object thing)  {
   return "It is " + wet_string(thing) + ".\n";
}