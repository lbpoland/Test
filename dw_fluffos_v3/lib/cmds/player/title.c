inherit "/cmds/base";
#include <player.h>
mixed cmd_list() {
   string* titles;
   if (this_player()->query_player_title()) {
      write("Your player title is currently set to: " +
            this_player()->query_player_title() + ".\n");
   } else {
      write("Your player title is currently not set.\n");
   }
   titles = this_player()->query_all_player_titles();
   write("You can set your player title to one of " +
         query_multiple_short(map(titles, (: capitalize($1) :))) + ".\n");
   return 1;
}
int cmd_set(string title) {
    mixed mess;
   title = lower_case(title);
   if (strlen(title) > 20) {
      add_failed_mess("Your title is too long.\n");
   }
   if (member_array(title,
                    this_player()->query_all_player_titles()) == -1) {
      add_failed_mess("The title '" + title + "' is not valid.\n");
      return 0;
   }
   if (this_player()->query_player_title() &&
       lower_case(this_player()->query_player_title()) == title) {
      add_failed_mess("You already have your player title set to '" + title +
                      "'.\n");
      return 0;
   }
   this_player()->set_player_title(title);
   if ( sizeof( this_player()->query_hide_invis() ) ) {
       mess = ({ "$N set$s $p player title to " + capitalize(title) +
           ".\n", "" });
   }
   else {
       mess = "$N set$s $p player title to " + capitalize(title) +  ".\n";
   }
   add_succeeded_mess(mess);
   return 1;
}
int cmd_reset() {
   if (!this_player()->query_player_title()) {
      add_failed_mess("Your player title is already unset.\n");
      return 0;
   }
   this_player()->set_player_title(0);
   add_succeeded_mess("$N reset$s $p player title.\n");
   return 1;
}
mixed *query_patterns() {
   return ({ "", (: cmd_list :),
             "<string'title'>", (: cmd_set($4[0]) :),
             "none", (: cmd_reset() :) });
}