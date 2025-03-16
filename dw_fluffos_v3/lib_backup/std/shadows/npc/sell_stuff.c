inherit "/std/effect_shadow";
void stopped_route() {
  object *obs;
  int i;
  mixed room;
  room = arg();
  if (pointerp(room)) {
    room = room[0];
  }
  if (file_name(environment(player)) == room) {
    obs = all_inventory(player);
    for (i=0;i<sizeof(obs);i++) {
      if (!obs[i]->query_property("start equipment"))
        call_out("sell_the_stuff", 1, obs[i]);
        call_out( "drop_the_stuff", 2, obs[ i ] );
    }
    call_out( "bury_the_stuff", 3, query_multiple_short( obs ) );
  }
  call_out("remove_this_effect", 4);
}
protected void sell_the_stuff(object ob) {
  player->do_command("sell "+ob->query_name());
}
protected void drop_the_stuff( object thing ) {
   player->do_command( "drop "+ (string)thing->query_name() );
}
protected void bury_the_stuff( string words ) {
   player->do_command( "bury "+ words );
}