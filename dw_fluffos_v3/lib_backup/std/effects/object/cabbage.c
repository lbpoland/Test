#include <effect.h>
void beginning( object player, int time, int id ) {
   player->submit_ee( "make_stink", ({ 20, 20 }), EE_CONTINUOUS );
   player->submit_ee( 0, time, EE_REMOVE );
}
int merge_effect( object player, int time1, int time2, int id ) {
   player->submit_ee( 0, time1 + time2 - (int)player->expected_tt(),
         EE_REMOVE );
   return time1 + time2;
}
void end( object player, int time, int id ) {
   tell_object( player, "Your stomach calms down at last.\n" );
}
void make_stink( object player, int time, int id ) {
   tell_object( player, "A huge trumpeting noise comes from your "
   "rear, closely followed by a stench of boiled cabbage.\n" );
   tell_room( environment( player ), "The smell of sprouts and cabbages from "
   + (string)player->one_short() +
         " wafts over you and you find yourself thinking of school dinners."
         "\n", player );
}
string query_classification() { return "body.smell.scent"; }
string smell_string( object player, int time ) {
   return "the delicious doughnutty smell";
}