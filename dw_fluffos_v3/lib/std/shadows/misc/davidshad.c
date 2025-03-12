object player;
void setup_shadow( object thing ) {
   shadow( thing, 1 );
   player = thing;
}
void dest_shadow() { destruct( this_object() ); }
void run_away() {
  tell_object(player, "You feel too peaceful to run away.\n");
}
int pk_check( mixed thing1, mixed thing2, int off_line ) {
  return 1;
}
void start_attack(){}
void adjust_hp( int number, object attacker ) {
  if(player->query_attacker_list()) {
    foreach(attacker in player->query_attacker_list()) {
      attacker->stop_fight(player);
      player->stop_fight(attacker);
    }
  }
    return;
}
void adjust_gp( int number ) {
  if ( number < 0 )
    return player->adjust_gp( number );
  return;
}
int attack_by(object ob) {
  ob->stop_fight(player);
  player->stop_fight(ob);
  return 1;
}