inherit "/std/effect_shadow";
void event_enter(object ob, string mess, object from) {
   mixed *bit = ({ });
   int ret;
   if (environment(ob) == player) {
      if(sizeof(arg()) > 1)
        bit = arg();
          else
        bit = ({ arg() });
           if (sizeof(bit) < 2)
              ret = evaluate(bit[0], player, ob, mess, from);
           else
              ret = call_other(bit[0], bit[1], player, ob, mess, from);
   }
   player->event_enter(ob, mess, from);
}