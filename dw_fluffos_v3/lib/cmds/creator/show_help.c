#include <playerinfo.h>
inherit "/cmds/base";
#define WHO(n) globals[n]
private nosave mapping globals = ([]);
mixed show_help(object *player, string helpname) {
   player[0]->set_finish_func("who_did_it", this_object());
   WHO(player[0]) = capitalize(this_player()->query_name());
   if (!player[0]->eventForce("help "+ helpname)) {
      map_delete(globals, player[0]);
      return notify_fail("The help command failed ... Did you specify the "
              "correct help subject ?\n");
   }
   event(users(), "inform", capitalize(this_player()->query_name())+
         " showed help on \"" + helpname + "\" to " + player[0]->the_short(),
         "help");
   write("Okay, showed help on \"" + helpname + "\" to " +
         player[0]->query_cap_name() + ".\n");
   PLAYERINFO_HANDLER->add_entry(this_player(),
                                 player[0]->query_name(),
                                 "showhelp",
                                 "Showed help on " + helpname,
                                 0);
   return 1;
}
int who_did_it() {
   tell_object(previous_object(), WHO(previous_object()) +
         " wanted you to read this help file.\n");
   map_delete(globals, previous_object());
   return 1;
}
mixed *query_patterns() {
   return ({ "<indirect:player> <string'help file'>",
             (: show_help($1, $4[1]) :) });
}