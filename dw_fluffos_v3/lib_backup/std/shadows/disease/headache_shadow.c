inherit "/std/effect_shadow";
int query_special_manoeuvre() {
   tell_object(player, "Your head hurts too much to try anything.\n");
   return 0;
}
int command_shadowed(string verb, string arg){
   if(verb=="cast"){
     write("Your head hurts too much to muster your might.\n");
     return 1;
   }
   return player->command_shadowed(verb, arg);
}