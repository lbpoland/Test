#include <effect.h>
int beginning( object player, int time ) {
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
    tell_object( player, "Your ability to mangle the english language "
                         "returns.\n");
}
string query_classification() { return "misc.curse.antisqeal"; }
string query_shadow_ob() { return "/std/shadows/curses/antisqeal"; }