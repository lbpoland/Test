#include <effect.h>
#include "path.h"
string query_classification() { return "misc.curse.alone"; }
string query_shadow_ob() { return SHADOWS+"alone"; }
int beginning( object player, int time ) {
   player->add_extra_look( this_object() );
}
void merge_effect( object player, int time1, int time2 ) {
}
void end(object player) {
   player->remove_extra_look( this_object() );
}
string extra_look( object player ) {
   if ( player == this_player() )
     return "";
   return capitalize( (string)player->query_pronoun() )+
     " can't see you.\n";
}