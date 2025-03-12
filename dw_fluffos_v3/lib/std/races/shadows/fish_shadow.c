object my_player;
void init_shadow(object ob) {
  my_player = ob;
  shadow(ob, 1);
}
int query_ac(string type, int dam) {
  int i;
  i = (int)my_player->query_ac(type);
  if (environment(my_player)->query_underwater())
    return i*100;
  return i;
}
int move(object ob, string s1, string s2) {
  int i;
  i = (int)my_player->move(ob, s1, s2);
  if (!i && !ob->query_underwater())
    call_out("do_drown", 2);
  else
    remove_call_out("do_drown");
  return i;
}
void do_drown() {
  tell_room(my_player, my_player->one_short()+" gasps for air.\n");
  my_player->adjust_hp(random(50)+50);
  call_out("do_drown", 2);
}