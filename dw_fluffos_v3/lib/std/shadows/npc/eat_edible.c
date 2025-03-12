inherit "/std/effect_shadow";
protected void real_eat(object ob);
protected void do_eat_edible();
mixed move(mixed dest, string messin, string messout) {
  int ret;
  ret = player->move(dest, messin, messout);
  if (ret == 0) {
    call_out((: do_eat_edible :), 0);
  }
  return ret;
}
protected void do_eat_edible() {
  int i;
  object *obs;
  obs = all_inventory(player);
  for (i=0;i<sizeof(obs);i++) {
    if (obs[i]->query_edible()) {
      call_out((: real_eat :), 1, obs[i]);
    }
  }
}
protected void real_eat(object ob) {
  if (ob && player) {
    player->do_command("eat "+ob->query_name());
  }
}
void event_enter(object ob, string mess, object from) {
  player->event_enter(ob, mess, from);
  if (ob->query_edible()) {
    call_out("real_eat", 2, ob);
  }
}