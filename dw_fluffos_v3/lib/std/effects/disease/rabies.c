#include <effect.h>
#define COMBAT_EFFECT "/std/effects/fighting/combat"
string *wretch_msg = ({
    "You start to froth at the mouth and your head spins.\n",
    "The pain is so intense you want to rip your eyes out.\n",
    "The pain from your ripped flesh radiates through your body.\n",
    "You feel like howling at the moon in rabid madness.\n",
    "You spray rabid froth everywhere.\n"
});
string *room_msg = ({
    " starts to froth at the mouth and looks crazed.\n",
    "'s eyes roll in crazed fury.\n",
    " seethes in agony.\n",
    " howls at the moon in rabid agony.\n",
    " sprays froth everywhere.\n"
});
string query_classification() { return "body.disease.rabies"; }
int beginning( object player, int time ) {
   if( player->query_property( "undead" ) ) {
      player->submit_ee( 0, 0, EE_REMOVE );
      return -1;
   }
   player->submit_ee( "wretch", ({ 30, 60 }), EE_CONTINUOUS );
   player->submit_ee( 0, time, EE_REMOVE );
   player->adjust_bonus_wis( -2 );
   player->adjust_bonus_int( -2 );
   tell_object( player, "Throbbing pains radiate from your bite wound, and "
      "you feel your sanity slip away.\n" );
   return time;
}
int merge_effect( object player, int time1, int time2 ) {
    return time1;
}
int restart( object player, int time ) {
   player->adjust_bonus_wis( -2 );
   player->adjust_bonus_int( -2 );
   return time;
}
void end( object player, int time ) {
   player->adjust_bonus_int( 2 );
   player->adjust_bonus_wis( 2 );
   tell_object( player, "You feel the madness leave you, and stop frothing"
      ".\n" );
}
void wretch( object player, int time ) {
    int msg_no;
    msg_no = random( sizeof( wretch_msg ) );
    tell_object( player, wretch_msg[ msg_no ] );
    tell_room( environment( player ), (string)player->the_short() +
              room_msg[ msg_no ], player );
    player->adjust_hp( - ( ( (int)player->query_hp() / 10 ) +
                           ( random( 50 ) ) ) );
    COMBAT_EFFECT->monitor_points( player, 1 );
}
string query_death_reason() {
   return "a nasty case of rabies";
}