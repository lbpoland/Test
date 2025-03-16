#include <effect.h>
string query_classification() { return "misc.curse.smurf"; }
string query_shadow_ob() { return "/std/shadows/curses/ensmurfed"; }
int beginning( object player, int time ) {
   tell_object( player, "You suddenly find yourself filled with a strange "
               "fear of someone called \"Gargamel\".\n");
   if (time)
     player->submit_ee( 0, time, EE_REMOVE );
   return time;
}
int merge_effect( object player, int time1, int time2 ) {
   int duration;
   duration = time2 + player->expected_tt();
   player->submit_ee( 0, duration, EE_REMOVE );
   return duration;
}
void end( object player, int time ) {
   tell_object( player, "Your fear of Gargamel has abated.\n");
}