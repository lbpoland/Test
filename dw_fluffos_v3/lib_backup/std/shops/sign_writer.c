inherit "/std/room/basic_room";
#include <money.h>
#include <move_failures.h>
#define SIGN_MAKING_PICK_UP_TIME (24 * 60 * 60)
class sign_type {
   string short;
   string long;
   int cost;
   int weight;
   int max_letters;
   int max_lines;
}
class sign_making {
   int type;
   string mess;
   string colour;
   int pick_up;
}
private nosave class sign_type* _signtypes;
private nosave mapping _paintcolours;
private nosave string _save_file;
private nosave string _language;
private nosave function _open_func;
private mapping _signs;
void do_load();
void create() {
   _signtypes = ({ });
   _paintcolours = ([ ]);
   _signs = ([ ]);
   ::create();
   do_load();
   add_help_file("sign_writer");
}
int is_open() {
   if (_open_func) {
      return evaluate(_open_func);
   }
   return 1;
}
void set_open_func(function func) {
   _open_func = func;
}
function query_open_func() {
   return _open_func;
}
void set_language(string lang) {
   _language = lang;
}
string query_language() {
   return _language;
}
void set_save_file_name(string save) {
   _save_file = save;
}
string query_save_file_name() {
   return _save_file;
}
void do_save() {
   if (_save_file) {
      save_object(_save_file);
   }
}
void do_load() {
   if (_save_file) {
      restore_object(_save_file);
   }
}
void add_paint_colour(string colour, int cost) {
   _paintcolours[colour] = cost;
}
void add_sign_type(string short, string long, int cost,
                   int weight, int max_letters, int max_lines) {
   class sign_type bing;
   bing = new(class sign_type);
   bing->short = short;
   bing->long = long;
   bing->cost = cost;
   bing->weight = weight;
   bing->max_letters = max_letters;
   bing->max_lines = max_lines;
   _signtypes += ({ bing });
}
void add_sign_making(string owner, int type, string mess,
                     string colour, int pick_up) {
   class sign_making bing;
   bing = new(class sign_making);
   bing->type = type;
   bing->mess = mess;
   bing->colour = colour;
   bing->pick_up = pick_up;
   if (!_signs[owner]) {
      _signs[owner] = ({ });
   }
   _signs[owner] += ({ bing });
   do_save();
}
int do_order(string type) {
   int pos;
   int cost;
   string place;
   if (!is_open()) {
      add_failed_mess(the_short() + " is not currently open.\n");
      return 0;
   }
   if (strlen(type) == 1) {
      pos = lower_case(type)[0] - 'a';
      if (pos < 0 || pos > sizeof(_signtypes)) {
         add_failed_mess("The id must be between 'a' and '" +
               sprintf("%c", 'a' + sizeof(_signtypes) - 1) + "'.\n");
         return 0;
      }
   } else {
      add_failed_mess("The id must be between 'a' and '" +
            sprintf("%c", 'a' + sizeof(_signtypes) - 1) + "'.\n");
      return 0;
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   cost = _signtypes[pos]->cost;
   if (cost > this_player()->query_value_in(place)) {
      add_failed_mess("You do not have enough money to pay for this "
            "sign.  You "
            "need " + MONEY_HAND->money_value_string(cost, place) +
            ".\n");
      return 0;
   }
   write("Using a sign of type " + _signtypes[pos]->short +
         ".  What message would "
         "you like on your sign?\n");
   this_player()->do_edit("", "finish_editing_message", this_object(),
                          0, pos);
   add_succeeded_mess(({ "",
                         "$N looks into getting a sign made up.\n" }));
   return 1;
}
void finish_editing_message(string mess, int type) {
   string colour;
   int cost;
   string place;
   class sign_type bing;
   if (!mess) {
      write("Aborting sign writing process.\n");
      return ;
   }
   bing = _signtypes[type];
   if (strlen(replace(mess, ({ "\n", "", }))) > bing->max_letters) {
      write("The message " + mess + " has too many letters for the "
            "sign " + bing->short + ", the most allowed is " +
            bing->max_letters + ", you have " +
            strlen(replace(mess, ({ "\n", "", }))) +
            ".\n");
      return ;
   }
   if (sizeof(explode(mess, "\n")) > bing->max_lines) {
      write("The message " + mess + " has too many lines for the "
            "sign " + bing->short + ", the most allowed is " +
            bing->max_lines + ", you have " +
            sizeof(explode(mess, "\n")) +
            ".\n");
      return ;
   }
   write("You have selected a sign of type " + bing->short + " and have "
         "decided to put the message:\n" + mess + "\nonto the sign.\n"
         "Paint colours are:\n");
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   foreach (colour, cost in _paintcolours) {
      write(sprintf("%-20s %s per letter\n", colour,
            MONEY_HAND->money_value_string(cost, place)));
   }
   write("What colour paint would you like? ");
   input_to("finish_sign", 0, type, mess);
}
void finish_sign(string colour, int type, string mess) {
   int cost;
   string place;
   class sign_type bing;
   colour = lower_case(colour);
   bing = _signtypes[type];
   if (!strlen(colour)) {
      write("Aborting the sign process.\n");
      return ;
   }
   if (!_paintcolours[colour]) {
      write("I am sorry, we do not stock " + colour + ".\n");
      write("Try one of " +
            query_multiple_short(keys(_paintcolours)) + ".\n");
      write("What colour paint would you like? ");
      input_to("finish_sign", 0, type, mess);
      return ;
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   cost = _paintcolours[colour] *
          strlen(replace(mess, ({ "\n", "", " ", "" })));
   cost += bing->cost;
   if (cost > this_player()->query_value_in(place)) {
      write("You do not have enough money to pay for this sign.  You "
            "need " + MONEY_HAND->money_value_string(cost, place) +
            ".\n");
      return ;
   }
   write("Making a sign of type " + bing->short + " with a message of:\n" +
         mess + "\nWill cost " +
         MONEY_HAND->money_value_string(cost, place) +
         ".\nDo you wish to make this sign? ");
   input_to("validate_sign", 0, type, mess, colour, cost);
}
void validate_sign(string choice, int type, string mess,
                   string colour, int cost) {
   int pick_up;
   string place;
   class sign_type bing;
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   if (cost > this_player()->query_value_in(place)) {
      write("You do not have enough money to pay for this sign.  You "
            "need " + MONEY_HAND->money_value_string(cost, place) +
            ".\n");
      return ;
   }
   bing = _signtypes[type];
   choice = lower_case(choice);
   if (!strlen(choice) || (choice[0] != 'n' && choice[0] != 'y')) {
      write("You did not enter 'yes' or 'no'.  Please try again.\n");
      write("Making a sign of type " + bing->short + " with a message of:\n" +
            mess + "\nWill cost " +
            MONEY_HAND->money_value_string(cost, place) +
            ".\nDo you wish to make this sign? ");
      input_to("validate_sign", 0, type, mess, colour);
      return 0;
   }
   this_player()->pay_money( (mixed *)MONEY_HAND->create_money_array(
               cost, place ), place );
   pick_up = time() + SIGN_MAKING_PICK_UP_TIME;
   add_sign_making(this_player()->query_name(), type, mess, colour,
                   pick_up);
   write("Ok, we will start making your sign.  Please come "
         "back tomorrow (after " + ctime(pick_up) +
         ") to pick up your sign.\n");
}
int do_collect() {
   class sign_making sign;
   class sign_type type;
   object* ok;
   string* not_yet;
   string* bits;
   object ob;
   if (!is_open()) {
      add_failed_mess(the_short() + " is not currently open.\n");
      return 0;
   }
   if (!_signs[this_player()->query_name()]) {
      add_failed_mess("You have no signs to pick up.\n");
      return 0;
   }
   ok = ({ });
   not_yet = ({ });
   foreach (sign in _signs[this_player()->query_name()]) {
      if (time() > sign->pick_up) {
         type = _signtypes[sign->type];
         ob = clone_object("/std/room/furniture/basic");
         bits = explode(type->short, " ");
         ob->set_name(bits[<1]);
         ob->add_adjective(bits[0..<2]);
         ob->set_short(type->short);
         ob->set_long(type->long);
         ob->set_weight(type->weight);
         ob->add_read_mess(sign->mess, sign->colour + " paint",
                           query_language(), 1);
         ob->add_property("sign");
         if (ob->move(this_player()) != MOVE_OK) {
            ob->move(this_object());
         }
         ok += ({ ob });
      } else {
         not_yet += ({ _signtypes[sign->type]->short + " with " +
                       sign->colour + " letters" });
      }
   }
   if (sizeof(ok)) {
      add_succeeded_mess("$N pick$s up $I.\n", ok);
      return 1;
   }
   if (sizeof(not_yet) == 1) {
      add_failed_mess("The sign " + query_multiple_short(not_yet) +
                      " is not ready to be picked up yet.\n");
   } else {
      add_failed_mess("The signs " + query_multiple_short(not_yet) +
                      " are not ready to be picked up yet.\n");
   }
   return 0;
}
int do_browse(string type) {
   class sign_type bing;
   string place;
   int pos;
   if (!is_open()) {
      add_failed_mess(the_short() + " is not currently open.\n");
      return 0;
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   if (strlen(type) == 1) {
      pos = lower_case(type)[0] - 'a';
      if (pos < 0 || pos > sizeof(_signtypes)) {
         add_failed_mess("The id must be between 'a' and '" +
               sprintf("%c", 'a' + sizeof(_signtypes) - 1) + "'.\n");
         return 0;
      }
   } else {
      add_failed_mess("The id must be between 'a' and '" +
            sprintf("%c", 'a' + sizeof(_signtypes) - 1) + "'.\n");
      return 0;
   }
   bing = _signtypes[pos];
   write("The sign of type " + type + " has a short description of '" +
         bing->short + "' and a long description:\n" + bing->long +
         "\nIt will cost " +
         MONEY_HAND->money_value_string(bing->cost, place) +
         " and will take a maximum of " + bing->max_letters +
         " letters and a maximum number of lines of " +
         bing->max_lines + ".\n");
   add_succeeded_mess(({ "", "$N browses a sign in " + the_short() +
                             ".\n" }));
   return 1;
}
int do_list() {
   class sign_type bing;
   int i;
   string ret;
   string place;
   string colour;
   int cost;
   if (!is_open()) {
      add_failed_mess(the_short() + " is not currently open.\n");
      return 0;
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   ret = "Signs availabe:\n";
   for (i = 0; i < sizeof(_signtypes); i++) {
      bing = _signtypes[i];
      ret += "$I$7=   " + sprintf("%c", 'a' + i) +
             ") " + bing->short + " costs " +
         MONEY_HAND->money_value_string(bing->cost, place) +
         " with " + bing->max_letters + " characters and " +
         bing->max_lines + " lines.\n";
   }
   ret += "\n$I$0=Colours available:\n";
   foreach (colour, cost in _paintcolours) {
      ret += sprintf("$I$7=   %-20s %s per letter\n", colour,
            MONEY_HAND->money_value_string(cost, place));
   }
   write("$P$Sign browse$P$" + ret);
   add_succeeded_mess(({ "", "$N lists the signs in " +
                             the_short() + ".\n" }) );
   return 1;
}
void init() {
   add_command("list", "", (: do_list() :));
   add_command("browse", "<string'sign'>", (: do_browse($4[0]) :));
   add_command("collect", "sign", (: do_collect() :));
   add_command("buy", "<string'sign'>", (: do_order($4[0]) :));
   add_command("order", "<string'sign'>", (: do_order($4[0]) :));
}