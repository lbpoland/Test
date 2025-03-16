inherit "/cmds/base";
mixed cmd()
{
   if (this_player()->query_property("dead")) {
      object *obs;
      write("You are just a disembodied spirit.  "
            "You have mist; what else do you want?\n");
      obs = all_inventory(this_player());
      obs = filter_array(obs, (: $1->query_property("dead usable") :));
      if (sizeof(obs)) {
         write("Hang on!  You appear to have " +
               query_multiple_short(obs) + ".  Amazing.\n");
      }
      return 1;
   }
   write(sprintf("You are %s by:\n", this_player()->burden_string()) +
	 this_player()->query_living_contents(1));
   if (this_player()->query_auto_loading()) {
      write("\n%^YELLOW%^Please note that your inventory is still being "
            "generated.%^RESET%^\n");
   }
   return 1;
}
mixed *query_patterns()
{
   return ({ "", (: cmd() :) });
}