inherit "cmds/base";
string *level_colors = ({ "", "%^BOLD%^%^RED%^", "%^RED%^", "%^YELLOW%^",
                          "%^CYAN%^", "" });
mixed cmd(object *who, int wounded) {
   object person;
   string health;
   int level;
   int found;
   if(this_player()->check_dark((int)environment(this_player())->
                                 query_light())) {
      add_failed_mess("You cannot see well enough to examine someone's "
                      "health.\n");
      return 0;
   }
   foreach(person in who) {
      health = person->health_string(1, ref level);
      if (this_player() == person) {
         health = replace(health, ({ "is ", "are ", "appears ", "appear " }));
      }
      if (health) {
         if (!wounded || level != 5) {
            write(level_colors[level] + "$C$" + person->one_short(1) + " " +
                  level_colors[level] + health + ".\n%^RESET%^");
            found++;
         }
      } else {
         write(person->one_short(1) + " is so unhealthy they have forgotten "
               "how healthy they are.\n");
      }
      if (person != this_player())
         tell_object(person, this_player()->the_short(1) + " appears to be "
                  "checking out all your wounds.\n");
   }
   if (wounded && !found) {
      add_failed_mess("Unable to find any wounded people.\n");
      return 0;
   }
   say(this_player()->one_short(1) + " studies " +
       query_multiple_short(who) + ".\n");
   return 1;
}
mixed *query_patterns() {
  return ({ "<indirect:living>", (: cmd($1, 0) :),
            "wounded <indirect:living>", (: cmd($1, 1) :) });
}