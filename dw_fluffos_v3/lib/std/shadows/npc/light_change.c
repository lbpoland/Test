inherit "/std/effect_shadow";
void event_light_change(object ob, int delta) {
   call_out("delayed_event_light_change",0, ob, delta );
}
void delayed_event_light_change(object ob, int delta) {
   mixed *bit;
   int ret;
   bit = arg();
   if (functionp(bit)) {
      ret = evaluate(bit, player, ob, delta);
   } else if (pointerp(bit)) {
      ret = call_other(bit[0], bit[1], player, ob, delta);
   }
   player->event_light_change(ob, delta);
}