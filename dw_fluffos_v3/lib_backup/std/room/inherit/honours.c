#include <player_handler.h>
#include <player.h>
class honour {
   int time_added;
   string reason;
   string cap_name;
   string added_by;
}
private nosave string* _titles;
mapping _honours;
int is_allowed_to_change(string person);
void save_me();
void create() {
   _honours = ([ ]);
   _titles = ({ });
}
void inform_of_honour_change(string type, string person,
                      string reason, string changed_by) {
}
void set_controlled_titles(string* title) {
   _titles = title;
}
string* query_controlled_titles() {
   return _titles;
}
void add_to_honour_roll(string person, string reason, string added_by) {
   string title;
   if (_honours[person]) {
      return ;
   }
   if (!PLAYER_HANDLER->test_user(person)) {
      return ;
   }
   _honours[person] = new(class honour);
   _honours[person]->time_added = time();
   _honours[person]->reason = reason;
   _honours[person]->added_by = added_by;
   _honours[person]->cap_name = PLAYER_HANDLER->query_cap_name(person);
   foreach (title in _titles) {
      PLAYER_TITLE_HANDLER->add_title_to_player(person, title);
   }
   save_me();
}
void remove_from_honour_roll(string person) {
   string title;
   if (!_honours[person]) {
      return ;
   }
   map_delete(_honours, person);
   if (find_player(person)) {
      foreach (title in _titles) {
         find_player(person)->remove_player_title(title);
      }
   }
   save_me();
}
int is_on_honour_roll(string person) {
   return classp(_honours[person]);
}
int do_list_honour() {
   string person;
   class honour roll;
   string ret;
   string* people;
   if (!_honours) {
      _honours = ([ ]);
   }
   if (!sizeof(_honours)) {
      add_failed_mess("There is no one on the honour roll.\n");
      return 0;
   }
   ret = "";
   people = sort_array(keys(_honours), (: _honours[$1]->time_added - _honours[$2]->time_added :));
   foreach (person in people) {
      roll = _honours[person];
      ret += "$I$3=%^YELLOW%^" + roll->cap_name + "%^RESET%^ at " +
             amtime(roll->time_added) +
             " for " + roll->reason + " by " + roll->added_by + "\n";
   }
   write("$P$Honour Roll$P$" + ret);
   return 1;
}
int do_honour_add(string person) {
   if (!is_allowed_to_change(this_player()->query_name())) {
      add_failed_mess("You are not allowed to add people to the honour "
                      "roll.\n");
      return 0;
   }
   if (is_on_honour_roll(person)) {
      add_failed_mess("They are already on the honour roll.\n");
      return 0;
   }
   if (!PLAYER_HANDLER->test_user(person)) {
      add_failed_mess("The person " + person + " does not exist.\n");
      return 0;
   }
   write("Enter the reason for adding " + person + " to the honour roll:\n");
   this_player()->do_edit("", "end_honour_add", this_object(), 0, person);
   add_succeeded_mess("");
   return 1;
}
void end_honour_add(string reason, string person, string bing) {
   if (reason == "" || !reason) {
      write("Aborting.\n");
      return ;
   }
   write("Adding the person " + person + " to the honour roll with a reason "
         "of:\n" + reason + "\nAre you sure? ");
   input_to("honour_roll_confirm", 0, person, reason);
}
void honour_roll_confirm(string response, string person, string reason) {
   response = lower_case(response);
   if (!strlen(response) || response[0] != 'y') {
      write("Aborting.\n");
      return ;
   }
   add_to_honour_roll(person, reason, this_player()->query_cap_name());
   inform_of_honour_change("add", person, reason,
                           this_player()->query_name());
   add_succeeded_mess("$N add$s " + person + " to the honour roll.\n");
   return ;
}
int do_honour_remove(string person, string reason) {
   if (!is_allowed_to_change(this_player()->query_name())) {
      add_failed_mess("You are not allowed to add people to the honour "
                      "roll.\n");
      return 0;
   }
   if (!is_on_honour_roll(person)) {
      add_failed_mess("They are not on the honour roll.\n");
      return 0;
   }
   remove_from_honour_roll(person);
   inform_of_honour_change("remove", person, reason,
                           this_player()->query_cap_name());
   add_succeeded_mess("$N remove$s " + person + " to the honour roll.\n");
   return 1;
}
void readd_all_titles() {
   string person;
   class honour roll;
   foreach (person, roll in _honours) {
      foreach (string title in _titles) {
         PLAYER_TITLE_HANDLER->add_title_to_player(person, title);
      }
   }
}
void init() {
   if (!sizeof(_titles)) {
      return 0;
   }
   add_command("list", "honour [roll]", (: do_list_honour() :));
   if (is_allowed_to_change(this_player()->query_name())) {
      add_command("add",
                  "<string'person'> to honours",
                  (: do_honour_add($4[0]) :));
      add_command("remove",
                  "<string'person'> from honours because <string'reason'>",
                  (: do_honour_remove($4[0], $4[1]) :));
   }
}