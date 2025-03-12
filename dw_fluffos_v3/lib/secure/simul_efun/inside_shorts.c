private string ob_short(object ob) {
   string ret;
   if (ob->query_clothing()) {
      ret = ob->query_pocket_mess();
   } else {
      ret = "$ob_short$";
   }
   return ret;
}
string inside_the_short(object ob, object play) {
   string str;
   if (!play) {
      play = this_player();
   }
   if (!ob) {
      ob = environment(play);
   }
   str = replace_string(ob_short(ob), "$ob_short$", ob->the_short());
   while (environment(ob) &&
          environment(ob) != play &&
          environment(ob) != environment(play)) {
      ob = environment(ob);
      str += " inside " + replace_string(ob_short(ob), "$ob_short$",
                                         ob->the_short());
   }
   return str;
}
string inside_a_short(object ob, object play) {
   string str;
   if (!play) {
      play = this_player();
   }
   if (!ob) {
      ob = environment(play);
   }
   str = replace_string(ob_short(ob), "$ob_short$", ob->a_short());
   while (environment(ob) &&
          environment(ob) != play &&
          environment(ob) != environment(play)) {
      ob = environment(ob);
      str += " inside " + replace_string(ob_short(ob), "$ob_short$",
                                         ob->the_short());
   }
   return str;
}
string inside_one_short(object ob, object play) {
   string str;
   if (!play) {
      play = this_player();
   }
   if (!ob) {
      ob = environment(play);
   }
   str = replace_string(ob_short(ob), "$ob_short$", ob->one_short());
   while (environment(ob) &&
          environment(ob) != play &&
          environment(ob) != environment(play)) {
      ob = environment(ob);
      str += " inside " + replace_string(ob_short(ob), "$ob_short$",
                                         ob->the_short());
   }
   return str;
}