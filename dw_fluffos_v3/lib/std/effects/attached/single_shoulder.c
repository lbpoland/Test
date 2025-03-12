#include "path.h"
#include <effect.h>
string query_classification() { return "mudlib.clothing.single-shoulder"; }
int query_indefinite() { return 1; }
string query_shadow_ob() { return SHADOWS +"single_shoulder"; }
int merge_effect( object, int old_arg, int new_arg ) {
   if (objectp(new_arg)) {
      new_arg = 0;
   }
   if (objectp(old_arg)) {
      old_arg = 0;
   }
   return old_arg + new_arg;
}
void restart( object player, int handicap ) {
   player->adjust_bonus_dex( -handicap );
}
void end( object player, int handicap ) {
   if (intp(handicap)) {
      player->adjust_bonus_dex( handicap );
   }
}