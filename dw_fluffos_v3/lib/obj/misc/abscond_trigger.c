#define CLASS "fighting.combat.special.abscond"
#include <effect.h>
inherit "/std/object";
void init() {
   if( !environment()
    || file_name( environment( this_object() ) ) == "/room/rubbish" ) {
      return;
   }
   if( this_player()
    && this_player() == query_property( "abscond player" ) ) {
      this_player()->submit_ee2( this_player()->effects_matching(CLASS)[0],
                                 "after_command", 0, EE_REMOVE );
   }
}