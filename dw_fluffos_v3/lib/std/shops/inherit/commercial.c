#include <player.h>
#include <move_failures.h>
#include <expressions.h>
#include <money.h>
#include <player_handler.h>
#include <mail.h>
inherit "/std/room/player_housing";
inherit "/std/shops/inherit/expression_util";
inherit "/std/shops/inherit/person_expressions";
#define COMMERCIAL_WEEKLY_STATS_TIME (7 * 24 * 60 * 60)
#define COMMERCIAL_ROYALTY_TIMEOUT_PERIOD (7 * 24 * 60 * 60)
class float_withdrawls {
   string person;
   int amount;
   int withdrawl_time;
}
class weekly_status {
   int total_incoming;
   int total_outgoing;
   class float_withdrawls* withdrawls;
}
class royalty_data {
   int value;
   int last_withdrawl;
}
private string* _auto_load_sign_str;
private int _broken_sign;
private string _property_name;
private mapping _royalties;
private class parse_node* _use_expression;
private class parse_node* _entry_cost;
private int _entry_time_limit;
private mapping _use_type_expressions;
private string* _black_list;
private int _last_stats;
private class weekly_status _weekly_status;
private int _commercial_id;
private nosave object _sign_ob;
private nosave string _parcel_post;
private nosave object* _commercial_things;
private nosave string _use_type;
private nosave string _commercial_type;
private nosave string _save_dir;
private nosave int _property_size;
private nosave string _language;
#define COMMERCIAL_SALESPERSON "/obj/monster/commercial"
private string variable_use_type(string seller);
void create() {
    _commercial_things = ({ });
    _royalties = ([ ]);
    _use_type_expressions = ([ ]);
    _property_size = 25;
    _black_list = ({ });
    _last_stats = time();
    _weekly_status = new(class weekly_status);
    _weekly_status->withdrawls = ({ });
    _language = "common";
    expression_util::create();
    player_housing::create();
    person_expressions::create();
    add_allowed_variable("type", EXPRESSION_TYPE_STRING,
                        (: variable_use_type :));
    set_expression_type("room");
    add_help_file("commercial");
    if (!_use_expression) {
        _use_expression = parse_boolean_string("false");
    }
    if (!_black_list) {
        _black_list = ({ });
    }
    if (!_last_stats) {
        _last_stats = time();
    }
    if (_last_stats + COMMERCIAL_WEEKLY_STATS_TIME - time() < 0) {
        call_out("mail_weekly_status", 0);
    }
    else {
        call_out("mail_weekly_status", _last_stats +
            COMMERCIAL_WEEKLY_STATS_TIME - time());
    }
}
string short() {
    if (_property_name) {
        set_short(_property_name);
        add_property("determinate", "");
    }
    return ::short();
}
string long(string word, int dark) {
    if (_property_name) {
        set_short(_property_name);
        add_property("determinate", "");
    }
    return ::long(word, dark);
}
int is_open_for(string type, string person) {
   class parse_node ret;
   if (is_allowed(person)) {
      return 1;
   }
   if (member_array(person, _black_list) != -1) {
      return 0;
   }
   _use_type = type;
   ret = evaluate_expression(_use_expression, this_player()->query_name());
   if (ret->value) {
      if (_use_type_expressions[type]) {
         ret = evaluate_expression(_use_type_expressions[type],
                                   this_player()->query_name());
      }
   }
   return ret->value;
}
object query_main_room() {
   return this_object();
}
void add_commercial_thing(object ob) {
   _commercial_things += ({ ob });
   ob->load_me();
}
void remove_commercial_thing(object thing) {
   thing->save_me();
   _commercial_things -= ({ thing });
}
object* query_commercial_things() {
   return _commercial_things;
}
int query_owners_money() {
   if (classp(_royalties[query_owner()])) {
      return ((class royalty_data)_royalties[query_owner()])->value;
   }
   return 0;
}
void adjust_royalty(string person, int amount) {
   if (is_allowed(person)) {
      if (!_weekly_status) {
         _weekly_status = new(class weekly_status);
         _weekly_status->withdrawls = ({ });
      }
      if (amount > 0) {
         _weekly_status->total_incoming += amount;
      } else {
         _weekly_status->total_outgoing += -amount;
      }
      if (!classp(_royalties[query_owner()])) {
         _royalties[query_owner()] = new(class royalty_data,
                      value : amount + _royalties[query_owner()],
                      last_withdrawl : time());
      } else {
         if (((class royalty_data)_royalties[query_owner()])->value == 0) {
            ((class royalty_data)_royalties[query_owner()])->last_withdrawl = time();
         }
         ((class royalty_data)_royalties[query_owner()])->value += amount;
      }
   } else {
      if (!classp(_royalties[person])) {
         _royalties[person] = new(class royalty_data,
                      value : amount + _royalties[person],
                      last_withdrawl : time());
      } else {
         if (((class royalty_data)_royalties[person])->value == 0) {
            ((class royalty_data)_royalties[person])->last_withdrawl = time();
         }
         ((class royalty_data)_royalties[person])->value += amount;
      }
   }
   event_save(this_object());
}
int query_royalty(string person) {
   if (classp(_royalties[person])) {
      return ((class royalty_data)_royalties[person])->value;
   }
   return 0;
}
int query_float() {
   return query_owners_money();
}
int query_commercial_property() {
   return 1;
}
void set_parcel_post(string parcel) {
   _parcel_post = parcel;
}
string query_parcel_post() {
   return _parcel_post;
}
void set_language(string language) {
   _language = language;
}
string query_language() {
   return _language;
}
void set_commercial_type(string name) {
   _commercial_type = name;
}
string query_commercial_type() {
   return _commercial_type;
}
void set_property_name(string name) {
  if(strsrch(name, "%^") != -1)
    return 0;
   _property_name = name;
   add_property("determinate", "");
   set_short(_property_name);
}
string query_property_name() {
   return _property_name;
}
void event_dest_me(object ob) {
   if (_sign_ob) {
      _sign_ob->dest_me();
   }
}
object query_sign_object() {
   object* obs;
   if (!_sign_ob && _auto_load_sign_str && !_broken_sign) {
      if (catch(obs = (PLAYER_OB)->load_auto_load_to_array(_auto_load_sign_str))) {
         _broken_sign = 1;
      } else {
         if (sizeof(obs)) {
            _sign_ob = obs[0];
            _sign_ob->reset_get();
         } else {
            _broken_sign = 1;
         }
      }
   }
   return _sign_ob;
}
void set_sign_object(object ob) {
   if (ob) {
      _auto_load_sign_str = (PLAYER_OB)->create_auto_load(({ ob }));
      ob->reset_get();
   } else {
      _auto_load_sign_str = 0;
   }
   _sign_ob = ob;
   event_save(this_object());
}
void set_save_file(string str) {
   printf("ERROR!  Do not use set_save_file.\n");
}
void set_save_dir(string dir) {
   if (dir[<1] != '/') {
      dir += "/";
   }
   _save_dir = dir;
   ::set_save_file(dir + "_main");
}
string query_save_dir() {
   return _save_dir;
}
int find_next_commercial_id() {
   object *obs;
   obs = all_inventory();
   while (file_size(query_save_dir() + _commercial_id) >= 0 ||
          file_size(query_save_dir() + _commercial_id + ".o") >= 0 ||
          file_size(query_save_dir() + _commercial_id + ".o.gz") >= 0 ||
          sizeof(filter(obs,
                        (: $1->query_commercial_id() == _commercial_id :)))) {
      _commercial_id++;
   }
   event_save(this_object());
   return _commercial_id;
}
void set_property_size(int size) {
   _property_size = size;
}
int query_property_size() {
   return _property_size;
}
void reset_weekly_status() {
   object ob;
   _weekly_status = new(class weekly_status);
   _weekly_status->withdrawls = ({ });
   foreach (ob in _commercial_things) {
      if (ob) {
         ob->reset_weekly_status();
      }
   }
}
string query_weekly_status_string() {
   string place;
   string ret;
   string str;
   object ob;
   class float_withdrawls withdrawl;
   place = query_property("place");
   if (!_weekly_status) {
      _weekly_status = new(class weekly_status);
      _weekly_status->withdrawls = ({ });
   }
   ret = "";
   ret += "\n$I$0=---=== " + the_short() + " ===---\n";
   ret += "Total outgoing   : " +
          MONEY_HAND->money_value_string(_weekly_status->total_outgoing, place) + "\n";
   ret += "Total incoming   : " +
          MONEY_HAND->money_value_string(_weekly_status->total_incoming, place) + "\n";
   if (sizeof(_weekly_status->withdrawls)) {
      ret += "Float withdrawls:\n";
      foreach (withdrawl in _weekly_status->withdrawls) {
         ret += "$I$6=   " + ctime(withdrawl->withdrawl_time)[0..11] + " " +
                withdrawl->person + " for " +
                MONEY_HAND->money_value_string(withdrawl->amount, place) + "\n";
      }
   } else {
      ret += "No withdrawls from the float.\n";
   }
   foreach (ob in _commercial_things) {
      if (ob) {
         str = ob->query_weekly_status_string();
         if (str) {
            ret += "\n$I$0=---=== " + ob->the_short() + " ===---\n";
            ret += str;
         }
      }
   }
   return ret;
}
protected void mail_weekly_status() {
   string str;
   string ret;
   class royalty_data data;
   string person;
   if(!query_owner()) {
      return;
   }
   foreach (person, data in _royalties) {
      if (classp(data)) {
         if (person != query_owner() &&
             data->value > 0 &&
             data->last_withdrawl +
                  COMMERCIAL_ROYALTY_TIMEOUT_PERIOD - time() < 0) {
            AUTO_MAILER->auto_mail(person,
                                   the_short(),
                                   "Lost royalties.",
                                   0,
                                   "You took too long to collect your "
                                   "royalties and they vanished.\n\n"
                                   "Good luck!\n"
                                   "Administrator.");
            map_delete(_royalties, person);
         }
      }
   }
   ret = catch(str = query_weekly_status_string());
   if (ret) {
      AUTO_MAILER->auto_mail(query_owner(),
                        the_short(),
                        "Weekly Statistics " + ctime(time()),
                        implode(query_allowed(), ","),
                        "The weekly stats generated an error: " + ret + "\n");
      AUTO_MAILER->auto_mail("pinkfish",
                        the_short(),
                        "Weekly Statistics " + ctime(time()),
                        0,
                        "The weekly stats generated an error: " +
                        ret + "\nin room: " + file_name(this_object()) + "\n");
   } else {
      str = PLAYER_OB->convert_message(str);
      AUTO_MAILER->auto_mail(query_owner(),
                        the_short(),
                        "Weekly Statistics " + ctime(time()),
                        implode(query_allowed(), ","),
                        str);
   }
   _last_stats = time();
   foreach (object ob in _commercial_things) {
      adjust_royalty(query_owner(), -ob->query_weekly_upkeep_cost());
   }
   event_save(this_object());
   reset_weekly_status();
   event_save(this_object());
}
object* find_commercial_items(string type) {
   object* obs;
   obs = filter(all_inventory(this_object()),
                (: $1->query_commercial_name() == $2 :), type);
   return obs;
}
void register_use_types(string* types) {
   string bing;
   if (!_use_type_expressions) {
      _use_type_expressions = ([ ]);
   }
   foreach (bing in types) {
      if (!_use_type_expressions[bing]) {
         _use_type_expressions[bing] = parse_boolean_string("true");
      }
   }
}
int do_name_property(string name) {
   if (!is_allowed(this_player()->query_name())) {
      add_failed_mess("You cannot set the name of " + the_short() + ".\n");
      return 0;
   }
   set_property_name(name);
   add_succeeded_mess("$N set$s the property name to '" + name + "'.\n");
   return 1;
}
int do_set_sign(object* obs) {
   object ob;
   if (!is_allowed(this_player()->query_name())) {
      add_failed_mess("You cannot set the sign for the property.\n");
      return 0;
   }
   if (sizeof(obs) > 1) {
      add_failed_mess("You must only specifiy one sign.\n");
      return 0;
   }
   if (living(obs[0])) {
      add_failed_mess("You have to wait till " + obs[0]->the_short() +
                      " dies first.\n");
      return 0;
   }
   if (obs[0]->get()) {
      add_failed_mess("Cannot set something as a sign that you cannot get.\n");
      return 0;
   }
   ob = query_sign_object();
   if (obs[0]->move("/room/rubbish") == MOVE_OK) {
      set_sign_object(obs[0]);
   } else {
      add_failed_mess("Unable to move $I off you.\n", obs[0..0]);
      return 0;
   }
   if (query_sign_object() != ob) {
      if (ob) {
         ob->set_get();
         if (ob->move(this_player()) != MOVE_OK) {
            ob->move(this_object());
         }
         add_succeeded_mess(({ "You remove the sign " +ob->the_short() +
                               " and set " + obs[0]->the_short() +
                               " as your property sign.\n",
                               "$N sets the sign for outside " + the_short() +
                               ".\n" }));
      } else {
         add_succeeded_mess(({ "You set " + obs[0]->the_short() +
                               " as your property sign.\n",
                               "$N sets the sign for outside " + the_short() +
                               ".\n" }));
      }
      return 1;
   } else {
      obs[0]->move(this_player());
      add_failed_mess("You cannot set the sign for some reason.\n");
      return 0;
   }
}
int do_remove_sign() {
   object ob;
   if (!is_allowed(this_player()->query_name())) {
      add_failed_mess("You cannot set the sign for the property.\n");
      return 0;
   }
   if (!query_sign_object()) {
      add_failed_mess("You cannot remove the sign since there is no sign.\n");
      return 0;
   }
   ob = query_sign_object();
   ob->set_get();
   if (ob->move(this_player()) == MOVE_OK) {
      add_succeeded_mess("$N $V $I from " + the_short() +
                         ".\n", ({ ob }));
      set_sign_object(0);
      return 1;
   } else {
      ob->reset_get();
      add_failed_mess("You cannot remove the sign, unable to hold it?\n");
      return 0;
   }
}
int do_status(int hint) {
   string ret;
   object ob;
   string str;
   string place;
   string fluff;
   class parse_node* expr;
   if (!is_allowed(this_player()->query_name())) {
      add_failed_mess("You are not allowed to see the status of this store.\n");
      return 0;
   }
   place = query_property("place");
   ret = "";
   ret += "$I$5=The owner of the property is " + query_owner() + ".\n";
   ret += "$I$5=The name of the property is " + _property_name + ".\n";
   if (hint) {
      ret += "$I$0=       Hint: name property <name>\n";
   }
   if (sizeof(_black_list)) {
      ret += "$I$5=The black list is " +
             query_multiple_short(_black_list) + ".\n";
   } else {
      ret += "$I$5=The black list is empty.\n";
   }
   if (hint) {
      ret += "$I$0=       Hint: blacklist add <name>\n";
      ret += "$I$0=       Hint: blacklist add ignore\n";
      ret += "$I$0=       Hint: blacklist remove <name>\n";
   }
   if (query_sign_object()) {
      ret += "$I$5=The property currently has a sign set.\n";
   } else {
      ret += "$I$5=The property does not currently have a sign set.\n";
   }
   if (hint) {
      ret += "$I$0=       Hint: set sign <object>\n";
      ret += "$I$0=       Hint: remove sign\n";
   }
   if (sizeof(query_allowed())) {
      ret += "$I$5=People allowed to change the property are " +
             query_multiple_short(sort_array(query_allowed(), 0)) + ".\n";
   } else if (hint) {
      ret += "$I$5=Only the owner can change the property.\n";
   }
   ret += "$I$5=Current float is " +
          MONEY_HAND->money_value_string(query_float(), place) + ".\n";
   if (sizeof(_use_expression)) {
      ret += "$I$5=Use condition: " + query_expression_string(_use_expression, 0) +
             ".\n";
   } else {
      ret += "$I$5=Anyone can use the shop.\n";
   }
   foreach (fluff, expr in _use_type_expressions) {
      ret += "$I$5=  Use " + fluff + " condition: " +
             query_expression_string(expr, 0) + ".\n";
   }
   ret += "$I$0=\n";
   foreach (ob in _commercial_things) {
      if (ob) {
         str = ob->query_main_status(hint);
         if (str) {
            ret += str;
         }
      }
   }
   write("$P$Status$P$" + ret);
   return 1;
}
int do_weekly_status() {
   if (!is_allowed(this_player()->query_name())) {
      add_failed_mess("You are not allowed to see the status of this store.\n");
      return 0;
   }
   write("$P$Weekly Status$P$" + query_weekly_status_string());
   return 1;
}
int do_use_expression(string str) {
   class parse_node* expr;
   if (!is_allowed(this_player()->query_name())) {
      add_failed_mess("You are not allowed to add restrictions to the property.\n");
      return 0;
   }
   if (str == "disable")  {
      _use_expression = ({ });
      add_succeeded_mess(({ "You disable checking to see if "
         "someone can use the property.\n",
         "$N fiddle$s about with " + the_short() + " a bit.\n" }));
      return 1;
   }
   expr = parse_boolean_string(str);
   if (!sizeof(expr)) {
      add_failed_mess(query_last_expression_error() + ".\n");
      return 0;
   } else {
      _use_expression = expr;
      add_succeeded_mess(({ "You set the expression to use when checking "
                            "to see if someone can use the property to " +
                            query_expression_string(expr, 1) +
                            ".\n",
                            "$N fiddle$s about with " + the_short() +
                                " a bit.\n" }));
      event_save(this_object());
   }
   return 1;
}
int do_use_expression_type(string type, string str) {
   class parse_node* expr;
   if (!is_allowed(this_player()->query_name())) {
      add_failed_mess("You are not allowed to add restrictions to the property.\n");
      return 0;
   }
   if (!_use_type_expressions[type]) {
      add_failed_mess("The type '" + type + "' is invalid, must be one "
                      "of " +
                      query_multiple_short(keys(_use_type_expressions)) +
                      ".\n");
      return 0;
   }
   if (str == "disable")  {
      _use_type_expressions[type] = ({ });
      add_succeeded_mess(({ "You disable checking to see if "
         "someone can use the property for " + type + ".\n",
         "$N fiddle$s about with " + the_short() + " a bit.\n" }));
      return 1;
   }
   expr = parse_boolean_string(str);
   if (!sizeof(expr)) {
      add_failed_mess(query_last_expression_error() + ".\n");
      return 0;
   } else {
      _use_type_expressions[type] = expr;
      add_succeeded_mess(({ "You set the expression to use when checking "
                            "to see if someone can use the property for " +
                            type + " to " +
                            query_expression_string(expr, 1) +
                            ".\n",
                            "$N fiddle$s about with " + the_short() +
                                " a bit.\n" }));
      event_save(this_object());
   }
   return 1;
}
int do_royalties() {
   string place;
   class royalty_data data;
   if (!is_open_for("royalty", this_player()->query_name())) {
      add_failed_mess(the_short() + " is not currently open for "
                      "customers.\n");
      return 0;
   }
   if (!classp(_royalties[this_player()->query_name()]) &&
       _royalties[this_player()->query_name()] != 0) {
      data = new(class royalty_data,
                 value : _royalties[this_player()->query_name()],
                 last_withdrawl : time());
     _royalties[this_player()->query_name()] = data;
   }
   data = _royalties[this_player()->query_name()];
   if (!data) {
      add_failed_mess("You have no money owed to you here.\n");
      return 0;
   }
   if (this_player()->query_name() != query_owner() && data->value > 0) {
      if (data->last_withdrawl + COMMERCIAL_ROYALTY_TIMEOUT_PERIOD - time() < 0) {
         write("Your royalties timed out before you could claim them.\n");
         map_delete(_royalties, this_player()->query_name());
      }
   }
   if (data->value < 0) {
      add_failed_mess("You owe money to " + the_short() + ".\n");
      return 0;
   }
   if (data->value == 0) {
      map_delete(_royalties, this_player()->query_name());
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   add_succeeded_mess(({ "You have " +
                      MONEY_HAND->money_value_string(data->value, place) +
                      " in royalties currently which will timeout in " +
                      query_time_string(data->last_withdrawl + COMMERCIAL_ROYALTY_TIMEOUT_PERIOD - time(), 2) + ".\n",
                      "$N checks $p royalties.\n" }));
   return 1;
}
int do_royalty_list() {
   string place;
   mixed value;
   class royalty_data data;
   string person;
   string ret;
   if (!is_allowed(this_player()->query_name())) {
      add_failed_mess("Only the property owners can do this.\n");
      return 0;
   }
   if (!sizeof(_royalties)) {
      add_failed_mess("No one has royalties here currently.\n");
      return 0;
   }
   place = query_property("place");
   ret = "";
   foreach (person in sort_array(keys(_royalties), 0)) {
      value = _royalties[person];
      if (!classp(value)) {
         data = new(class royalty_data, value : value, last_withdrawl : time());
      } else {
         data = value;
      }
      if (PLAYER_HANDLER->test_user(person)) {
         ret += capitalize(person) + " " +
                MONEY_HAND->money_value_string(data->value, place);
         if (person != query_owner()) {
            ret += " (Timeout: " + query_time_string(data->last_withdrawl +
                     COMMERCIAL_ROYALTY_TIMEOUT_PERIOD - time(), 2) + ")\n";
         } else {
            ret += "\n";
         }
      } else {
         map_delete(_royalties, person);
      }
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   write("$P$Royalties$P$" + ret);
   return 1;
}
int do_collect() {
   string place;
   string name;
   class royalty_data data;
   if (!is_open_for("royalty", this_player()->query_name())) {
      add_failed_mess(the_short() + " is not currently open for "
                      "customers.\n");
      return 0;
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   name = this_player()->query_name();
   if (!classp(_royalties[this_player()->query_name()]) &&
       _royalties[this_player()->query_name()] != 0) {
      data = new(class royalty_data,
                 value : _royalties[this_player()->query_name()],
                 last_withdrawl : time());
     _royalties[this_player()->query_name()] = data;
   }
   data = _royalties[name];
   if (!data) {
      add_failed_mess("You have no royalties to collect.\n");
      return 0;
   }
   if (name != query_owner() && data->value > 0) {
      if (data->last_withdrawl + COMMERCIAL_ROYALTY_TIMEOUT_PERIOD - time() < 0) {
         write("Your royalties timed out before you could claim them.\n");
         map_delete(_royalties, name);
         return 1;
      }
   }
   if (data->value == 0) {
      map_delete(_royalties, this_player()->query_name());
   }
   if (this_player()->query_refresh_time() &&
       this_player()->query_refresh_time() > data->last_withdrawl) {
      add_failed_mess("You have refreshed since your last collection.\n");
      map_delete(_royalties, name);
      return 0;
   }
   if ((!data || !data->value) && is_allowed(this_player()->query_name())) {
      name = query_owner();
      data = _royalties[name];
   }
   if (data->value > 0) {
      this_player()->adjust_money(MONEY_HAND->create_money_array(data->value, place));
      if (name == query_owner()) {
         _weekly_status->withdrawls += ({ new(class float_withdrawls, amount : data->value,
                               person : name,
                               withdrawl_time : time() ) });
      }
      event_save(this_object());
      add_succeeded_mess(({ "You collect " +
                            MONEY_HAND->money_value_string(data->value, place) +
                            " in royalties.\n",
                            "$N collects some royalties.\n" }));
      data->value = 0;
      if (!data->value && name != query_owner()) {
         map_delete(_royalties, name);
      }
      return 1;
   } else if (!data->value) {
      add_failed_mess("You have no royalties to collect.\n");
   } else {
      if (this_player()->query_value_in(place) < -data->value) {
         add_failed_mess("You do not have enough money to pay off "
                         "your debts.\n");
         return 0;
      }
      this_player()->pay_money(MONEY_HAND->create_money_array(-data->value, place),
                               place);
      add_succeeded_mess(({ "You pay off " +
                            MONEY_HAND->money_value_string(data->value, place) +
                            " in debt.\n",
                            "$N pays off some debt.\n" }));
      if (name != query_owner()) {
         map_delete(_royalties, name);
      } else {
         data->value = 0;
      }
      return 1;
   }
}
int do_collect_partial_royalties(string amount) {
   int amt;
   string place;
   if (!is_allowed(this_player()->query_name())) {
      add_failed_mess("Only the owners can do this.\n");
      return 0;
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   amt = MONEY_HAND->value_from_string(amount, place);
   if (!amt) {
      add_failed_mess("The value " + amount + " is not a valid money "
                      "amount.\n");
      return 0;
   }
   if (amt > query_owners_money()) {
      add_failed_mess("You cannot collect more money than you have.\n");
      return 0;
   }
   this_player()->adjust_money(MONEY_HAND->create_money_array(amt, place));
   ((class royalty_data)_royalties[query_owner()])->value -= amt;
   if (!((class royalty_data)_royalties[query_owner()])->value) {
      map_delete(_royalties, query_owner());
   }
   if (!_weekly_status) {
      _weekly_status = new(class weekly_status);
      _weekly_status->withdrawls = ({ });
   }
   _weekly_status->withdrawls += ({ new(class float_withdrawls, amount : amt,
                                        person : this_player()->query_name(),
                                        withdrawl_time : time() ) });
   event_save(this_object());
   add_succeeded_mess(({ "You collect " +
                      MONEY_HAND->money_value_string(amt, place) +
                      " in royalties.\n",
                      "$N collects some money in royalties.\n" }));
   return 1;
}
int do_pay_entry() {
   string place;
   class parse_node ret;
   if (!_entry_cost) {
      add_failed_mess("Entry into " + the_short() + " is free.\n");
      return 0;
   }
   if (!is_open_for("entry", this_player()->query_name())) {
      add_failed_mess(the_short() + " is not currently open for "
                      "customers.\n");
      return 0;
   }
   ret = evaluate_expression(_entry_cost, this_player()->query_name());
   if (this_player()->query_value_in(place) < ret->value) {
      add_failed_mess("You do not have the " +
                      MONEY_HAND->money_value_string(ret->value, place) +
                      " needed to enter.\n");
      return 0;
   }
   this_player()->pay_money(MONEY_HAND->create_money_array(ret->value, place),
                            place);
   this_player()->add_property(file_name(this_object()),
                               _entry_time_limit * 60 * 60);
   add_succeeded_mess("$N pay$s " +
                      MONEY_HAND->money_value_string(ret->value, place) +
                      " for entry into " + the_short() + ".\n");
   return 1;
}
int do_add_royalties(string amount) {
   int amt;
   string place;
   if (!is_allowed(this_player()->query_name())) {
      add_failed_mess("You cannot add to the float.\n");
      return 0;
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   amt = MONEY_HAND->value_from_string(amount, place);
   if (!amt) {
      add_failed_mess("The value " + amount + " is not a valid money "
                      "amount.\n");
      return 0;
   }
   if (this_player()->query_value_in(place) < amt) {
      add_failed_mess("You do not have " +
                      MONEY_HAND->money_value_string(amt, place) +
                      " to add to the float.\n");
      return 0;
   }
   this_player()->pay_money(MONEY_HAND->create_money_array(amt, place),
                            place);
   if (!classp(_royalties[query_owner()])) {
       int value;
       value = _royalties[query_owner()];
       _royalties[query_owner()] = new(class royalty_data,
            value : value,
            last_withdrawl : time());
   }
   ((class royalty_data)_royalties[query_owner()])->value += amt;
   add_succeeded_mess(({ "You add " +
                      MONEY_HAND->money_value_string(amt, place) +
                      " to " + poss_short() + " float.\n",
                      "$N fiddles about in " + the_short() + ".\n" }));
   return 1;
}
int do_purchase() {
   object ob;
   ob = clone_object(COMMERCIAL_SALESPERSON);
   ob->move(this_object(), "$N arrives in a flash.\n");
   ob->set_commercial_type(query_commercial_type());
   ob->do_start_speil(this_player());
   return 1;
}
int do_deposit(object* obs) {
   object* monies;
   object money;
   string place;
   monies = filter(obs, (: $1->id(MONEY_ALIAS) :));
   if (!sizeof(monies)) {
      add_failed_mess("YOu cannot deposit any of $I.\n", obs);
      return 0;
   }
   money = monies[0];
   place = query_property("place");
   monies = MONEY_HAND->filter_legal_tender(money, place);
   if (monies[1]) {
      monies[1]->move(this_player());
   }
   if (!monies[0]) {
      add_failed_mess("You must use legal tender.\n");
      return 0;
   }
   adjust_royalty(query_owner(), monies[0]->query_value_in(place));
   monies[0]->move("/room/rubbish");
   add_succeeded_mess(({ "$N $V $I into " + the_short() + ".\n",
                         "$N $V some money into " + the_short() + ".\n" }),
                      monies[0..0]);
   event_save(this_object());
   return 1;
}
int do_black_list_add(string name) {
   if (!is_allowed(this_player()->query_name())) {
      add_failed_mess("You are not allowed to add people to the black list.\n");
      return 0;
   }
   name = lower_case(name);
   if (!PLAYER_HANDLER->test_user(name)) {
      add_failed_mess("Sorry, " + name + " does not play here.\n");
      return 0;
   }
   if (is_allowed(name)) {
      add_failed_mess("This person is in the list of people allowed to use "
                      "the shop.  They cannot be put on a black list.\n");
      return 0;
   }
   if (member_array(name, _black_list) != -1) {
      add_failed_mess("The person " + name + " is already in the "
                      "black list.\n");
      return 0;
   }
   _black_list += ({ name });
   event_save(this_object());
   add_succeeded_mess(({ "You add " + name + " to the black list.\n",
                         "$N fiddle$s with something in the shop.\n" }) );
   return 1;
}
int do_black_list_add_ignore() {
   string *people;
   string *bad;
   string *ok;
   string name;
   if (!is_allowed(this_player()->query_name())) {
      add_failed_mess("You are not allowed to add people to the black list.\n");
      return 0;
   }
   people = this_player()->query_property("ignoring");
   if (!people) {
      add_failed_mess("You are not ignoring anyone.\n");
      return 0;
   }
   bad = ({ });
   ok = ({ });
   foreach (name in people) {
      name = lower_case(name);
      if (!PLAYER_HANDLER->test_user(name)) {
         bad += ({ name });
      } else if (member_array(name, _black_list) != -1) {
         bad += ({ name });
      } else {
         _black_list += ({ name });
         ok += ({ name });
      }
   }
   event_save(this_object());
   if (!sizeof(ok)) {
      add_failed_mess("Your ignore list is already added to the black list.\n");
      return 0;
   }
   add_succeeded_mess(({ "You add " + query_multiple_short(ok) + " to the "
                         "black list.\n",
                         "$N fiddle$s with something in the shop.\n" }) );
   return 1;
}
int do_black_list_remove(string name) {
   if (!is_allowed(this_player()->query_name())) {
      add_failed_mess("You are not allowed to remove people from "
                      "the black list.\n");
      return 0;
   }
   name = lower_case(name);
   if (member_array(name, _black_list) == -1) {
      add_failed_mess("The person " + name + " is not in the black list.\n");
      return 0;
   }
   _black_list -= ({ name });
   event_save(this_object());
   add_succeeded_mess(({ "You remove " + name + " from the black list.\n",
                         "$N fiddle$s with something in the shop.\n" }) );
   return 1;
}
private string variable_use_type(string seller) {
   return _use_type;
}
int do_measure() {
    this_player()->add_succeeded_mess( this_object(),
        ({
            "$N $V up the size of the property and calculate that it is "
            "about " + query_num(query_property_size()) + " square yards.\n",
            "$N $V up the size of the property.\n"
        }), ({ }) );
    return 1;
}
void init() {
   if (!_royalties) {
      _royalties = ([ ]);
   }
   player_housing::init();
   expression_util::init();
   add_command("collect", "royalties", (: do_collect() :));
   add_command("royalties", "", (: do_royalties() :));
   add_command("royalty", "", (: do_royalties() :));
   add_command("measure", "property", (: do_measure() :) );
   if (!is_allowed(this_player()->query_name())) {
      return ;
   }
   add_command("royalty", "list", (: do_royalty_list() :));
   add_command("royalties", "list", (: do_royalty_list() :));
   add_command("collect", "royalties of <string'amount'>",
               (: do_collect_partial_royalties($4[0]) :));
   add_command("royalty", "add <string'amount'> to float",
               (: do_add_royalties($4[0]) :));
   add_command("deposit", "[to] float <indirect:object>",
               (: do_deposit :));
   add_command("status", "room",
               (: do_status(0) :));
   add_command("status", "room {hint|hints}",
               (: do_status(1) :));
   add_command("status", "room weekly",
               (: do_weekly_status() :));
   add_command("name", "property <string'property name'>",
               (: do_name_property($4[0]) :));
   add_command("set", "use expression <string'expression'>",
               (: do_use_expression($4[0]) :));
   add_command("set",
               "use expression for <string'type'> as <string'expression'>",
               (: do_use_expression_type($4[0], $4[1]) :));
   add_command("set", "sign <indirect:object'sign'>",
               (: do_set_sign($1) :) );
   add_command("remove", "sign",
               (: do_remove_sign() :) );
   add_command("blacklist", "add <string'person'>",
               (: do_black_list_add($4[0]) :));
   add_command("blacklist", "add ignore",
               (: do_black_list_add_ignore() :));
   add_command("blacklist", "remove <string'person'>",
               (: do_black_list_remove($4[0]) :));
   add_command("purchase", "stuff", (: do_purchase() :));
}