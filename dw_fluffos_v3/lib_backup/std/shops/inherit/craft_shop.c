#include <money.h>
#include <shops/craft_shop.h>
inherit "/std/shops/inherit/open_shop";
private nosave object _controller;
private nosave string _save_dir_name;
private nosave function _allowed_to_sell;
private nosave function _when_sold_func;
private nosave int _max_sell_per_person;
private nosave int _cut;
private nosave int _minimum_cost;
private nosave function _extra_sell_check;
private nosave int _always_ask_price;
private nosave int _use_name;
private nosave int _no_royalty_commands;
int do_sell(object *obs);
void set_controller(string name);
int do_buy(object *obs, int force);
int do_delete(string id);
int do_browse(object *obs);
int do_change(object *obs, string str);
int do_change_name(object *obs, string str);
void set_allowed_to_sell(function f);
void set_minimum_cost(int i);
protected void sell_name(string name, object *sellable);
protected void sell_choice(string choice, object *sellable, string *names);
protected void determine_cost(string cost, string name, object *sellable);
protected void confirm_sale(string answer, int value, string name,
                            object *sellable, string category);
protected void confirm_sell_name_choice(string answer, string name,
                                        object *sellable);
protected void complete_sale(int value, string name, object *sellable, string category);
protected void do_confirm_sale(int value, string name, object *sellable);
void set_cut(int value);
int query_cut();
int check_open(object player, string command);
mixed query_property(string name);
string the_short();
string query_craft_shop_save_dir();
void create() {
   if (!_allowed_to_sell) {
      set_allowed_to_sell((: 1 :));
   }
   if (!_cut) {
      set_cut(10);
   }
   if (!_minimum_cost) {
      set_minimum_cost(12 * 4);
   }
   if (!_controller && _save_dir_name) {
      set_controller("/std/shops/controllers/craft_shop_controller");
      _controller->load_it();
   }
}
int value_from_string(string str, string place) {
   return MONEY_HAND->value_from_string(str, place);
}
protected void do_save_file(int type, mixed value, string fname) {
   string tmp, file;
   string dir;
   switch (type) {
   case CRAFT_SHOP_MAIN_SAVE_FILE :
     debug_printf("attempting to write main");
#ifdef USE_RAMDISK
     tmp = replace_string(query_craft_shop_save_dir(), "/save/",
                          "/save/ramdisk/");
     file = tmp + ".o";
#endif
     if(!file) {
       file = query_craft_shop_save_dir() + ".o";
     }
     debug_printf("writing main %s", file);
     tmp = save_variable(value);
     if (file_size(query_craft_shop_save_dir() + ".o") != -1) {
       unguarded( (: rename(query_craft_shop_save_dir() + ".o",
                            query_craft_shop_save_dir() + ".o.bak") :));
     }
     if(unguarded( (: write_file($(file), $(tmp), 1) :) )) {
       unguarded( (: rm($(file) + ".bak") :));
     } else {
       unguarded( (: rename($(file) + ".bak", $(file)) :));
     }
     break;
   case CRAFT_SHOP_DATA_SAVE_FILE :
#ifdef USE_RAMDISK
     dir = replace_string(query_craft_shop_save_dir(), "/save/", "/save/ramdisk/");
     if (file_size(dir) == -2) {
        file = dir + "/" + fname;
     }
#endif
     if(!file) {
       file = query_craft_shop_save_dir() + "/" + fname;
     }
     debug_printf("writing data %s", file);
     tmp = save_variable(value);
     if (!unguarded( (: write_file($(file), $(tmp), 1) :))) {
        debug_printf("failed to write data to %s", file);
     }
     break;
   case CRAFT_SHOP_REMOVE_DATA_SAVE_FILE :
#ifdef USE_RAMDISK
     file = replace_string(query_craft_shop_save_dir() + "/" + fname, "/save/",
                          "/save/ramdisk/");
     unguarded( (: rm($(file)) :) );
#endif
     unguarded((: rm(query_craft_shop_save_dir() + "/" + $(fname)) :));
     break;
   default :
     printf("Unknown file type to write in %O, of %O\n", __FILE__, type);
     break;
   }
}
protected string do_read_file(int type, string fname) {
   string tmp, file;
   switch (type) {
   case CRAFT_SHOP_MAIN_SAVE_FILE :
#ifdef USE_RAMDISK
     tmp = replace_string(query_craft_shop_save_dir(), "/save/",
                          "/save/ramdisk/");
     if(unguarded((: file_size($(tmp) + ".o") :)) > 0) {
       file = tmp + ".o";
     }
#endif
     if(!file) {
       tmp = query_craft_shop_save_dir();
       if(unguarded((: file_size($(tmp) + ".o") :)) > 0) {
         file = tmp + ".o";
       }
       if(unguarded((: file_size($(tmp) + ".o.bak") :)) > 0) {
         file = tmp + ".o.bak";
       }
     }
     if (!file) {
        debug_printf("No file found at %s or %s\n", tmp + ".o", tmp + ".o.bak");
        return 0;
     }
     tmp = unguarded( (: read_file($(file)) :) );
     if(tmp)
       return restore_variable(tmp);
     return 0;
   case CRAFT_SHOP_DATA_SAVE_FILE :
#ifdef USE_RAMDISK
     tmp = replace_string(query_craft_shop_save_dir() + "/" + fname,
                           "/save/", "/save/ramdisk/");
     if(unguarded((: file_size($(tmp)) :)) > 0)
       file = tmp;
#endif
     if(!file)
       file = query_craft_shop_save_dir() + "/" + fname;
     debug_printf("reading %s", file);
     tmp = unguarded( (: read_file($(file)) :) );
     if (tmp) {
       return restore_variable(tmp);
     }
     return 0;
   default :
     printf("Unknown file type to read in %O, of %O\n", __FILE__, type);
     break;
   }
}
void reload_shop() {
   set_controller("/std/shops/controllers/craft_shop_controller");
   _controller->load_it();
}
void set_controller(string name) {
   if (_controller) {
      _controller->dest_me();
   }
   _controller = clone_object(name);
   _controller->set_save_function((: do_save_file($1, $2, $3) :));
   _controller->set_load_function((: do_read_file($1, $2) :) );
}
object query_controller() {
   return _controller;
}
void set_save_dir(string fname) {
   _save_dir_name = fname;
}
string query_craft_shop_save_dir() {
   return _save_dir_name;
}
void set_allowed_to_sell(function func) {
   _allowed_to_sell = func;
}
function query_allowed_to_sell() {
   return _allowed_to_sell;
}
void set_max_sell_per_person(int num) {
   _max_sell_per_person = num;
}
int query_max_sell_per_person() {
   return _max_sell_per_person;
}
void set_always_ask_price(int ask_price) {
   _always_ask_price = ask_price;
}
int query_always_ask_price() {
   return _always_ask_price;
}
void set_use_name(int flag) {
   _use_name = flag;
}
int query_use_name() {
   return _use_name;
}
int query_maximum_sale_value(string person, object *obs) {
   return 0;
}
string query_extra_price_information(string person, object *obs) {
   return "";
}
int query_shop() {
   return 1;
}
object *query_shop_lift_items(string str, object player) {
   object *stuff;
   object *pk_ok;
   object ob;
   stuff = match_objects_for_existence(str, ({ _controller->query_sell_list() }));
   pk_ok = ({ });
   foreach (ob in stuff) {
      if (!pk_check(_controller->query_owner_of_shop_object(ob),
                      player, 1)) {
         pk_ok += ({ ob });
      }
   }
   if (sizeof(pk_ok) != sizeof(stuff)) {
      player->add_failed_mess(previous_object(),
                      "You cannot shoplift $I since you cannot "
                      "shoplift from non-player killers.\n", stuff);
   }
   return pk_ok;
}
void inform_of_buy(int value, object *obs, object player, string *sellers,
                   string *names, string *cats, int *values) {
}
int query_no_steal() {
   return 1;
}
int is_able_to_change(object ob) {
   return _controller->query_owner_of_shop_object(ob) ==
       this_player()->query_name();
}
int is_allowed_to_sell(object* obs, string name, string *sellable_names) {
   if ((sizeof(sellable_names)+sizeof(obs)) > query_max_sell_per_person() &&
       query_max_sell_per_person()) {
      add_failed_mess("Cannot sell $I, since you already have " +
                      number_as_string(sizeof(sellable_names)) +
                      " items listed with a maximum of " +
                      number_as_string(query_max_sell_per_person()) +
                      ".\n", obs);
      return 0;
   }
   return 1;
}
void init() {
   string storeroom;
   add_command("sell", "<indirect:object:me>");
   add_command("list", "");
   if (query_controller()) {
      storeroom = file_name(_controller->query_sell_list());
      add_command("buy", "<indirect:object:" + storeroom + ">",
                  (: do_buy($1, 0) :));
      add_command("browse", "<indirect:object:" + storeroom + ">",
                  (: do_browse($1) :));
      add_command("change", "price of <indirect:object:" + storeroom +
                            "> to <string>", (: do_change($1, $4[1]) :));
      add_command("change", "name of <indirect:object:" + storeroom +
                            "> to <string>", (: do_change_name($1, $4[1]) :));
   }
   if (!_no_royalty_commands) {
      add_command("collect", "royalties");
      add_command("royalties", "");
   }
   add_command("delete", "<string'sell id'>",
               (: do_delete($4[0]) :));
}
int do_sell_id(object* obs, string id, int force) {
   object *sellable;
   object *cannot;
   object *worn;
   string name;
   string *sellable_names;
   if (!check_open(this_player(), "sell")) {
      return 0;
   }
   sellable = filter(obs, query_allowed_to_sell());
   if (!sizeof(sellable)) {
      add_failed_mess("This shop does not deal in $I.\n", obs);
      return 0;
   }
   worn = this_player()->query_holding() + this_player()->query_armours();
   cannot = filter(sellable, (: member_array($1, $2) != -1 :), worn);
   if (sizeof(cannot)) {
       sellable -= cannot;
       tell_object(this_player(), "You decide not to sell " +
         query_multiple_short(cannot, "the") + ", because "
         "you are wearing or holding $V$0=it,them$V$.\n");
      if (!sizeof(sellable))  return 0;
   }
   name = this_player()->query_name();
   if (!is_allowed_to_sell(sellable, name, sellable_names)) {
      return 0;
   }
   if (query_cut() != 100) {
      write("Selling an item to this shop does not automatically give you the "
            "money.  You will get a cut of " + (100 - query_cut()) +
            "% of the sale price once the item has been sold by the shop.\n");   }
}
int do_sell(object *obs) {
   object *sellable;
   object *cannot;
   object *worn;
   string name;
   string *sellable_names;
   int i;
   int cost;
   string place;
   if (!check_open(this_player(), "sell")) {
      return 0;
   }
   sellable = filter(obs, query_allowed_to_sell());
   if (!sizeof(sellable)) {
      add_failed_mess("This shop does not deal in $I.\n", obs);
      return 0;
   }
   worn = this_player()->query_holding() + this_player()->query_armours();
   cannot = filter(sellable, (: member_array($1, $2) != -1 :), worn);
   if (sizeof(cannot)) {
       sellable -= cannot;
       tell_object(this_player(), "You decide not to sell " +
         query_multiple_short(cannot, "the") + ", because "
         "you are wearing or holding $V$0=it,them$V$.\n");
      if (!sizeof(sellable))  return 0;
   }
   name = this_player()->query_name();
   if (!is_allowed_to_sell(sellable, name, sellable_names)) {
      return 0;
   }
   if (query_cut() != 100) {
      write("Selling an item to this shop does not automatically give you the "
            "money.  You will get a cut of " + (100 - query_cut()) +
            "% of the sale price once the item has been sold by the shop.\n");
   }
   if (_use_name) {
      sell_name(query_multiple_short(sellable, 0, 1), sellable);
      add_succeeded_mess(({ "", "$N starts to sell $I to the shop.\n" }),
                         sellable);
      return 1;
   }
   obs->set_no_join();
   sellable_names = _controller->query_owner_sellables(name);
   sellable_names = uniq_array(sellable_names);
   if (!sizeof(sellable_names)) {
      write("You are not currently selling any items.  What item name "
            "would you like to list " + query_multiple_short(sellable) +
            " under?  (Blank line to quit)\nList name: ");
      input_to((: sell_name :), 0, sellable);
   } else {
      place = query_property("place");
      if (!place) {
         place = "default";
      }
      write("You currently have the following listed for sale:\n");
      for (i = 0; i < sizeof(sellable_names); i++) {
         cost = _controller->query_list_object_cost(sellable_names[i],
                                   this_player()->query_name());
         write(sprintf("  %c) %s (%s)\n", 'a' + i, sellable_names[i],
                       MONEY_HAND->money_value_string(cost, place)));
      }
      write("Select the letter of the choice to add to the item, or type "
            "'create' to create a new listing name.\n"
            "Your choice ([a-" + sprintf("%c", 'a' + sizeof(sellable_names) -1) +
            "],create) ? ");
      input_to((: sell_choice :), 0, sellable, sellable_names);
   }
   add_succeeded_mess(({ "", "$N starts to sell $I to the shop.\n" }),
                      sellable);
   return 1;
}
protected int check_sell_name( string name ) {
   if (strlen(name) > CRAFT_SHOP_MAX_NAME_LENGTH) {
      write("Sorry, that name is too long.  It can be a maximum of " +
            CRAFT_SHOP_MAX_NAME_LENGTH + " characters.\n");
      return 0;
   }
   if (strsrch(name, "%^") != -1) {
      write("Sorry, you cannot use colour sequences in names.\n");
      return 0;
   }
   return 1;
}
protected void sell_name(string name, object *sellable) {
   if (name == "" || name == 0) {
      write("Ok, cancelling the sale of " + query_multiple_short(sellable) +
            ".\n");
      return ;
   }
   if ( !check_sell_name( name ) ) {
      input_to((: sell_name :), 0, sellable);
      write("What name would you like to list " +
            query_multiple_short(sellable) + " under? ");
      return;
   }
   write("You wish to sell " + query_multiple_short(sellable) +
         " as '" + name + "' (y/n)? ");
   input_to((: confirm_sell_name_choice :), 0, name, sellable);
}
protected void confirm_sell_name_choice(string answer, string name,
                                        object *sellable) {
   answer = lower_case(answer);
   if (strlen(answer) > 0 && ( answer[0] == 'n' || answer[0] == 'q' ) ) {
      write("Ok, cancelling the sale of " + query_multiple_short(sellable) +
            ".\n");
      return ;
   }
   if (!strlen(answer) || answer[0] != 'y') {
      write("Unknown selection.\n");
      write("You wish to sell " + query_multiple_short(sellable) +
            " as '" + name + "' (y/n)? ");
      input_to( (: confirm_sell_name_choice :), 0, name, sellable);
      return ;
   }
   write(query_extra_price_information(this_player()->query_name(), sellable));
   write("How much money do you wish to sell the item '" + name + "' for? ");
   input_to((: determine_cost :), 0, name, sellable);
}
protected void sell_choice(string answer, object *sellables, string *names) {
   int cost;
   string place;
   int pos;
   if (sizeof(names) >= 17) {
      if (answer == "" || answer[0..1] == "qu") {
         write("Ok, cancelling the sale of " + query_multiple_short(sellables) +
             ".\n");
         return 0;
      }
   } else if (answer == "" || answer[0] == 'q') {
      write("Ok, cancelling the sale of " + query_multiple_short(sellables) +
            ".\n");
      return ;
   }
   answer = lower_case(answer);
   if (answer == "create") {
      write("Please enter the name you wish to list " +
            query_multiple_short(sellables) + " as.\nList name: ");
      input_to((: sell_name :), 0, sellables);
      return ;
   }
   if (strlen(answer) > 1 ||
       (answer[0] < 'a' || answer[0] >= 'a' + sizeof(names))) {
      write(sprintf("Your response must be between 'a' and '%c' or "
                    "'create'.\nChoice? ", 'a' + sizeof(names) - 1));
      input_to((: sell_choice :), 0, sellables, names);
      return ;
   }
   pos = answer[0] - 'a';
   cost = _controller->query_list_object_cost(names[pos],
                                              this_player()->query_name());
   if (!cost || _always_ask_price) {
      write("How much money do you wish to list the item '" + names[pos] +
            "' for? ");
      write(query_extra_price_information(this_player()->query_name(),
                                          sellables));
      input_to((: determine_cost :), 0, names[pos], sellables);
   } else {
      place = query_property("place");
      if (!place) {
         place = "default";
      }
      do_confirm_sale(cost, names[pos], sellables);
   }
}
protected void determine_cost(string cost, string name, object *sellable) {
   int max;
   int value;
   string place;
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   value = value_from_string(cost, place);
   if (value < _minimum_cost) {
      if (!strlen(cost) ||
          lower_case(cost)[0] == 'q') {
         write("Aborting.\n");
         return ;
      }
      write("You must list your item as costing more than " +
            MONEY_HAND->money_value_string(_minimum_cost, place) + ".\n");
      write(query_extra_price_information(this_player()->query_name(),
                                          sellable));
      write("What do you wish to list " + name + " for? ");
      input_to("determine_cost", 0, name, sellable);
      return ;
   }
   max = query_maximum_sale_value(this_player()->query_name(), sellable);
   if (value > max && max) {
      write("You must list your item as costing less than " +
            MONEY_HAND->money_value_string(max, place) + ".\n");
      write(query_extra_price_information(this_player()->query_name(),
                                          sellable));
      write("What do you wish to list " + name + " for? ");
      input_to("determine_cost", 0, name, sellable);
      return ;
   }
   do_confirm_sale(value, name, sellable);
}
private void confirm_sale_question(int value,
                                   string name,
                                   object *sellables,
                                   string category) {
   string place;
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   write("Confirming your sale of " + query_multiple_short(sellables) +
         " as '" + name +
         "' " + (category?"in category " + category + " ":"") +
         "for " + MONEY_HAND->money_value_string(value, place) + " (y/n)? ");
   input_to((: confirm_sale :), 0, value, name, sellables, category);
}
protected void do_confirm_sale(int value, string name, object *sellables) {
   if (_extra_sell_check) {
      evaluate(_extra_sell_check,
               (: confirm_sale_question :),
               value, name, sellables);
   } else {
      confirm_sale_question(value, name, sellables, 0);
   }
}
protected void confirm_sale(string answer, int value, string name,
                            object *sellable,
                            string category) {
   if (answer == "" || answer[0] == 'q' || answer[0] == 'Q' ||
       answer[0] == 'n' || answer[0] == 'N') {
      write("Ok, aborting sale of " + query_multiple_short(sellable) + ".\n");
      return 0;
   }
   if (answer[0] != 'y' && answer[0] != 'Y') {
      write("Please answer yes or no.\n");
      confirm_sale_question(value, name, sellable, category);
      return 0;
   }
   complete_sale(value, name, sellable, category);
}
protected void complete_sale(int value, string name, object *sellable,
                             string category) {
   object *bought;
   string place;
   object ob;
   if (_when_sold_func) {
      foreach (ob in sellable) {
         evaluate(_when_sold_func, ob);
      }
   }
   bought = _controller->buy_objects(sellable, name, value,
                                   this_player()->query_cap_name(), category);
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   if (sizeof(bought)) {
      write("Sold " + query_multiple_short(bought) + ", listed as '" +
            name + "' " + (category?"in category " + category + " ":"") +
            "for " + MONEY_HAND->money_value_string(value, place) +
            ".\nYou will need to come back later to pick up your royalties "
            "for the sale.\n");
      say(this_player()->query_cap_name() + " sold " +
          query_multiple_short(bought) + " to " + the_short() + ".\n");
   } else {
      write("Unable to sell " + query_multiple_short(sellable) + ".\n");
   }
}
int do_list() {
   string place;
   object *obs;
   object ob;
   mixed *stuff;
   string ret;
   if (!check_open(this_player(), "list")) {
      return 0;
   }
   obs = _controller->query_sell_list_obs();
   if (!sizeof(obs)) {
      add_failed_mess("The shop is empty.\n", ({ }));
      return 0;
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   stuff = unique_array(obs, (: _controller->query_id_of_shop_object($1) :) );
   stuff = sort_array(stuff, (:
                strcmp(_controller->query_id_of_shop_object($1[0]),
                       _controller->query_id_of_shop_object($2[0])) :) );
   ret = "";
   foreach (obs in stuff) {
      ob = obs[0];
      ret += "$I$9=$C$" + _controller->query_id_of_shop_object(ob) +
            ") $C$" + ob->short() + " for " +
            MONEY_HAND->money_value_string(ob->query_value(), place) + "; " +
            query_num(sizeof(obs)) + " left.\n";
   }
   write("$P$Shop list$P$" + ret);
   add_succeeded_mess( ({ "", "$N browses through the inventory.\n" }) );
   return 1;
}
int do_buy(object *obs, int force) {
   int value;
   string place;
   int player_money;
   object *bought;
   string *sellers;
   string *names;
   string *cats;
   int *values;
   if (!check_open(this_player(), "buy")) {
      return 0;
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   player_money = this_player()->query_value_in(place);
   value = _controller->value_of_objects(obs);
   if (value > player_money) {
      add_failed_mess("You cannot buy $I as "+
                      ( sizeof( obs ) > 1 ? "they cost ":"it costs " )+
                      MONEY_HAND->money_value_string(value, place) +
                      " and you do not have that much money.\n", obs );
      return 0;
   }
   sellers = map(obs, (: _controller->query_owner_of_shop_object($1) :));
   names = map(obs, (: _controller->query_name_of_shop_object($1) :));
   cats = map(obs, (: _controller->query_category_of_shop_object($1) :));
   values = map(obs, (: $1->query_value() :));
   bought = _controller->sell_objects(obs, place, this_player(),
                                     query_cut(), force, ref value);
   if (!sizeof(bought)) {
      if (sizeof(bought) > 1) {
         add_failed_mess("Cannot move any of $I into your inventory, nothing "
                         "bought.\n", obs);
      } else {
         add_failed_mess("Unable to find any objects to buy, the shop "
                         "seems to have some stock problems.\n");
      }
      return 0;
   }
   inform_of_buy(value, bought, this_player(), sellers, names, cats, values);
   add_succeeded_mess(({ "You buy $I for " +
                       MONEY_HAND->money_value_string(value, place) + ".\n",
                         "$N buys $I.\n" }), bought);
   return 1;
}
int do_delete(string id ) {
   if( !this_player()->query_director() ) {
      add_failed_mess( "This command is reserved for directors.\n", ({ }) );
      return 0;
   }
   if( !id || id == "" ) {
      add_failed_mess( "You have to choose a valid sell id.\n", ({ }) );
      return 0;
   }
   _controller->delete_objects(id);
   add_succeeded_mess( "$N $V some things.\n", ({ }) );
   return 1;
}
int do_browse(object *obs) {
   object *real_obs;
   object ob;
   string mess;
   string read;
   if (!check_open(this_player(), "browse")) {
      return 0;
   }
   if (sizeof(obs) > 10) {
      add_failed_mess("You cannot browse more than 10 things at once.\n");
      return 0;
   }
   real_obs = _controller->create_all_real_objects(this_player(), obs);
   mess = "$P$Browse$P$";
   foreach (ob in real_obs) {
      mess += ob->the_short() + ":\n" + ob->long();
      read = ob->query_readable_message();
      if (read) {
         mess += "You read " +
                 replace(ob->query_read_short(this_player()), "$name$",
                         ob->a_short()) + ":\n" +
                 ob->query_readable_message();
      }
   }
   real_obs->move("/room/rubbish");
   add_succeeded_mess(({ mess, "$N $V $I.\n" }), obs);
   return 1;
}
int do_change(object *obs, string change) {
   object *frog;
   int value;
   string place;
   if (!check_open(this_player(), "change")) {
      return 0;
   }
   frog = filter(obs, (: $1->short() == $2->short() :), obs[0]);
   if (sizeof(frog) != sizeof(obs)) {
      add_failed_mess("You cannot change the value of more than one "
                      "type of object at once.\n", obs);
      return 0;
   }
   if (!is_able_to_change(obs[0])) {
      add_failed_mess("You do not own $I.\n", obs);
      return 0;
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   value = value_from_string(change, place);
   if (value < _minimum_cost) {
      add_failed_mess("You cannot set $I to a value less than " +
                 MONEY_HAND->money_value_string(_minimum_cost, place) + ".\n",
                 obs);
      return 0;
   }
   _controller->change_value_of_shop_object(obs[0], value);
   add_succeeded_mess( ({ "You change the value of $I to " +
         MONEY_HAND->money_value_string(value, place) + ".\n",
         "$N changes the value of $I.\n" }), obs[0..0]);
   return 1;
}
int do_change_name(object *obs, string new_name) {
   object *frog;
   if (!check_open(this_player(), "change")) {
      return 0;
   }
   frog = filter(obs, (: $1->short() == $2->short() :), obs[0]);
   if (sizeof(frog) != sizeof(obs)) {
      add_failed_mess("You cannot change the value of more than one "
                      "type of object at once.\n", obs);
      return 0;
   }
   if (!is_able_to_change(obs[0])) {
      add_failed_mess("You do not own $I.\n", obs);
      return 0;
   }
   if( !check_sell_name( new_name ) ) {
      add_failed_mess( "Try another name.\n", ({ }) );
      return 0;
   }
   if (_controller->change_name_of_shop_object(obs[0], new_name,
                               _controller->query_dont_use_name())) {
      add_succeeded_mess(({ "You change the name of $I to " +
                               new_name + ".\n",
                               "$N changes the name of $I.\n" }),
                         ({ obs[0] }) );
   } else {
      add_failed_mess("The name " + new_name + " is already in use.\n", obs);
   }
   return 1;
}
int do_collect() {
   string name;
   string place;
   int value;
   if (!check_open(this_player(), "collect")) {
      return 0;
   }
   name = this_player()->query_name();
   value = _controller->query_royalty(name);
   if (!value) {
      add_failed_mess("You have no money owed to you here.\n");
      return 0;
   }
   if (value < 0) {
      add_failed_mess("You owe money to " + the_short() + ".\n");
      return 0;
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   _controller->pay_out_royalty(name, place);
   log_file(__FILE__ + ".log",
            name + " collects " +
                      MONEY_HAND->money_value_string(value, place) +
                      " in royalties.\n");
   add_succeeded_mess(({ "You collect " +
                      MONEY_HAND->money_value_string(value, place) +
                      " in royalties.\n",
                      "$N collects some money in royalties.\n" }));
   return 1;
}
int do_royalties() {
   string name;
   string place;
   int value;
   if (!check_open(this_player(), "royalties")) {
      return 0;
   }
   name = this_player()->query_name();
   value = _controller->query_royalty(name);
   if (!value) {
      add_failed_mess("You have no money owed to you here.\n");
      return 0;
   }
   if (value < 0) {
      add_failed_mess("You owe money to " + the_short() + ".\n");
      return 0;
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   add_succeeded_mess(({ "You have " +
                      MONEY_HAND->money_value_string(value, place) +
                      " in royalties currently.\n",
                      "$N checks $p royalties.\n" }));
   return 1;
}
void set_cut(int new_cut) {
   _cut = new_cut;
}
int query_cut() {
   return _cut;
}
void set_minimum_cost(int cost) {
   _minimum_cost = cost;
}
int query_minimum_cost() {
   return _minimum_cost;
}
void set_when_sold_function(function func) {
   _when_sold_func = func;
}
function query_when_sold_function() {
   return _when_sold_func;
}
int check_open(object player, string type) {
   if (!is_open(player, 0)) {
      add_failed_mess("The shop is not open.\n");
      return 0;
   }
   return 1;
}
void set_extra_sell_check(function func) {
   _extra_sell_check = func;
}
function query_extra_sell_check() {
   return _extra_sell_check;
}
void set_no_royalty_commands(int flag) {
   _no_royalty_commands = flag;
}
int query_no_royalty_commands() {
   return _no_royalty_commands;
}
void dest_me() {
  if(_controller) {
     _controller->dest_me();
  }
}