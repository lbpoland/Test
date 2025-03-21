object player;
void setup_shadow( object thing ) {
   shadow( thing, 1 );
   player = thing;
}
void dest_offler_shadow() { destruct( this_object() ); }
int adjust_hp( int number, object thing, object weapon, string attack ) {
   if ( number > 0 )
      return (int)player->adjust_hp( number, thing, weapon, attack );
   else
      return (int)player->query_hp();
}
int set_hp( int number, object thing ) {
   int current;
   current = (int)player->query_hp();
   if ( number > current )
      return (int)player->set_hp( number, thing );
   else
      return current;
}
void do_death() { return; }
int second_life() { return 1; }
int attack_by( object thing ) {
   tell_object( thing, (string)player->the_short() +
         " is prevented from fighting by Offler.\n" );
   thing->stop_fight( this_object() );
   return 0;
}
int attack_ob( object thing ) {
   tell_object( player, "You are prevented from fighting by Offler.\n" );
   thing->stop_fight( this_object() );
   return 0;
}
int query_unambushable() { return 1; }
void do_ambushed() {
   write( "You suddenly see a terrifying image of a huge crocodile!\n" );
   this_player()->run_away();
}
int no_offense() {
   write( "You are prevented from offensive actions by Offler.\n" );
   return 1;
}
int cast() {
   write( "You are about to start when Offler stops you.\n" );
   return 1;
}