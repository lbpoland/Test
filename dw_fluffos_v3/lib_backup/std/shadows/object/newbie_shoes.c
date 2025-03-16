#include <move_failures.h>
#include "path.h"
inherit "/std/effect_shadow";
int query_orthopaedic_shoes() { return 1; }
string query_msgin()
{
return "$N stagger$s clumsily from $F.";
}
string query_msgout()
{
return "$N stagger$s $T clumsily.";
}
int move(mixed dest, string inmsg, string outmsg)
{
  int ret;
  ret = player->move(dest, inmsg, outmsg);
  if (ret == MOVE_OK) {
    tell_object( player, "You wince as spikes seem to drive themselves "
      "into the balls of your feet, but you get there eventually.\n" );
  }
  return ret;
}
int test_for_effect( object thing ) {
   return member_array( EFFECTS +"newbie_shoes",
      (string *)thing->query_wear_effects() ) != -1;
}
void taken_off(object what, string eff)
{
  if (eff != EFFECTS + "newbie_shoes")
    player->taken_off(what, eff);
  else {
    remove_this_effect();
  }
}