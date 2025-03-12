#include "path.h"
inherit "/std/effect_shadow";
private int test_sash( object thing ) {
   return (string)thing->query_type() == "sash" &&
          sizeof(thing->query_pockets());
}
private int test_for_effect( object thing ) {
   return member_array( EFFECTS +"single_shoulder",
      (string *)thing->query_wear_effects() ) != -1;
}
void check_handicap() {
   int new_arg;
   mixed old_arg;
   object *things;
   things = (object *)player->query_wearing() - ({ 0 });
   old_arg = arg();
   if (objectp(old_arg)) {
      old_arg = 0;
   }
   new_arg = sizeof( filter_array( things, (: test_sash :), this_object() ) ) *
         sizeof( filter_array( things, (: test_for_effect :), this_object() ) );
   if ( !new_arg ) {
      remove_this_effect();
      return;
   }
   new_arg /= 2;
   if ( old_arg == new_arg ) {
      return;
   }
   player->adjust_bonus_dex( old_arg - new_arg );
   set_arg( new_arg );
}
void now_worn( object thing ) {
   player->now_worn( thing );
   if ( find_call_out( "check_handicap" ) == -1 ) {
      call_out( "check_handicap", 0 );
   }
}
void now_removed( object thing ) {
   player->now_removed( thing );
   if ( find_call_out( "check_handicap" ) == -1 ) {
      call_out( "check_handicap", 0 );
   }
}