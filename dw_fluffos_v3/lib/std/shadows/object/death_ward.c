inherit "/std/effect_shadow";
void event_death( object thing, object *killers, object killer,
      string room_mess, string killer_mess ) {
   int damage;
   object twit;
   player->event_death( thing, killers, killer, room_mess, killer_mess );
   if ( thing != (object)player->query_worn_by() )
      return;
   tell_room( environment( thing ), (string)player->the_short() +
         " explodes in a ball of flame!\n" );
   thing->remove_armour( player );
   player->move( "/room/rubbish" );
   foreach ( twit in killers ) {
      if ( environment( twit ) != environment( thing ) )
         continue;
      damage = arg();
      if ( twit == killer )
         damage *= 2;
      damage -= (int)twit->query_ac( "fire", damage );
      if ( damage > 0 )
         twit->adjust_hp( -damage );
      if ( (int)twit->query_hp() < 0 )
         twit->attack_by( player );
   }
   remove_this_effect();
}