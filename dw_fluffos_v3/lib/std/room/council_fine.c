#include <money.h>
#include <nomic_system.h>
#include <player_handler.h>
inherit "/std/room/basic_room";
inherit "/std/room/inherit/council_base";
private string _fine_handler;
void create() {
   ::create();
   add_help_file("fines");
}
void set_fine_handler(string fine) {
   _fine_handler = fine;
}
string query_fine_handler() {
   return _fine_handler;
}
int do_pay() {
   string place;
   mixed* m_array;
   int fine;
   int value;
   fine = _fine_handler->query_current_fine(this_player()->query_name());
   if (!fine) {
      add_failed_mess("You do not have any fines due here.\n");
      return 0;
   }
   place = query_property("place");
   value = this_player()->query_value_in(place);
   if (value >= fine) {
      m_array = MONEY_HAND->create_money_array(fine, place);
      this_player()->pay_money(m_array, place);
      _fine_handler->pay_fine(this_player()->query_name(), fine);
      write("You pay off all of your fine of " +
            MONEY_HAND->money_value_string(fine, place) + ".\n");
   } else {
      m_array = MONEY_HAND->create_money_array(value, place);
      this_player()->pay_money(m_array, place);
      _fine_handler->pay_fine(this_player()->query_name(), value);
      write("You pay off " +
            MONEY_HAND->money_value_string(value, place) +
            " of your fine of " +
            MONEY_HAND->money_value_string(fine, place) + ".\n");
   }
   add_succeeded_mess(({ "", "$N $V $p fine.\n" }));
   return 1;
}
string query_fine_information(string person) {
   string ret;
   int fine;
   string place;
   place = query_property("place");
   ret = "";
   fine = _fine_handler->query_current_fine(person);
   if (!fine) {
      ret += "No current fine.\n";
   } else {
      ret += "Current fine of " +
            MONEY_HAND->money_value_string(fine, place) + ".\n";
   }
   fine = _fine_handler->query_total_fine(person);
   if (!fine) {
      ret += "No fines ever.\n";
   } else {
      ret += "Total fines of " +
            MONEY_HAND->money_value_string(fine, place) + ".\n";
   }
   fine = _fine_handler->query_total_payments(person);
   if (!fine) {
   } else {
      ret += "Total fine payments of " +
            MONEY_HAND->money_value_string(fine, place) + ".\n";
   }
   return ret;
}
int do_fine() {
   write(query_fine_information(this_player()->query_name()));
   add_succeeded_mess(({ "", "$N look$s up a fine.\n" }));
   return 1;
}
int do_show_fine(string person) {
   if (!PLAYER_HANDLER->test_user(person)) {
      add_failed_mess("You must find a fine for an existing person.\n");
      return 0;
   }
   write(person + ":\n" + query_fine_information(person));
   add_succeeded_mess(({ "", "$N look$s up a fine.\n" }));
   return 1;
}
int do_show_all_fines() {
   string ret;
   int fine;
   ret = "";
   foreach (string person in _fine_handler->query_people_with_fines()) {
      fine = _fine_handler->query_current_fine(person);
      if (fine) {
         ret += person + " " + query_fine_information(person) + "\n";
      }
   }
   write("$P$Fines$P$" + ret);
}
void init() {
   add_command("pay", "fine", (: do_pay() :));
   add_command("fine", "", (: do_fine() :));
   if (NOMIC_HANDLER->is_magistrate_of(query_council_area(),
                                       this_player()->query_name())) {
      add_command("fine", "<string'player'>", (: do_show_fine($4[0]) :));
      add_command("fine", "all", (: do_show_all_fines :));
      add_command("list", "fines", (: do_show_all_fines :));
   }
}