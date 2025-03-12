inherit "/std/effect_shadow";
int add_follower(object ob) {
   call_out("do_command", 0, "lose everyone");
   return player->add_follower(ob);
}