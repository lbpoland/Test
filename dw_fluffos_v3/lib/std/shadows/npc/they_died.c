inherit "/std/effect_shadow";
void event_death(object ob, string mess) {
   mixed *bit;
   int ret;
   bit = arg();
   if (functionp(bit)) {
      ret = evaluate(bit, player, ob, mess);
   } else if (pointerp(bit)) {
      ret = call_other(bit[0], bit[1], player, ob, mess);
   }
   player->event_exit(ob, mess);
}