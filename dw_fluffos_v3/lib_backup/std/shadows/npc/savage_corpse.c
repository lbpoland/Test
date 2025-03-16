inherit "/std/effect_shadow";
mixed move(mixed dest, string messin, string messout) {
   int ret;
   ret = player->move(dest, messin, messout);
   if (ret == 0) {
      call_out("do_savage_corpse", 0);
   }
   return ret;
}
protected void do_savage_corpse() {
   int i;
   object *obs;
   obs = all_inventory(environment(player));
   for (i = 0; i < sizeof(obs); i++) {
      if (obs[i]->query_corpse() &&
          sizeof(obs[i]->query_edible_bits_left()) > 0) {
         remove_call_out("real_savage");
         call_out("real_savage", 1 + random(120), obs[i]);
         break;
      }
   }
}
protected void real_savage(object ob) {
   string *bits;
   object bit;
   int i;
   if (!ob) {
      call_out("do_savage_corpse", 1 + random(2*60));
      return ;
   }
   bits = ob->query_edible_bits_left();
   if (sizeof(bits) > 0 && environment(ob) == environment(player)) {
      i = random(sizeof(bits));
      bit = ob->make_bit(bits[i]);
      tell_room(environment(player), capitalize(player->the_short()) +
                " rips apart " + ob->the_short() +
                " pulling off " + bit->a_short() + ".\n");
      bit->move(environment(player));
   }
   if (sizeof(bits) > 1) {
      remove_call_out("real_savage");
      call_out("real_savage", 1 + random(2*60), ob);
   } else {
      call_out("do_savage_corpse", 1 + random(2*60));
   }
}
void event_enter(object ob, string mess, object from) {
   player->event_enter(ob, mess, from);
   if (ob->query_corpse()) {
      remove_call_out("real_savage");
      call_out("real_savage", 10, ob);
   }
}