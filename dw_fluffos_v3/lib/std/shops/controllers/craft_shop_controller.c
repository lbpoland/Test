#include <obj_parser.h>
#include <money.h>
#include <move_failures.h>
#include <player.h>
#include <shops/craft_shop.h>
class craft_object {
   int cost;
   string cap_owner;
   int ob_num;
   string category;
   string short;
}
class craft_sellable {
   mapping objects;
}
class craft_category {
   int state;
   string description;
   string information;
   string* voted;
   int yes;
   int no;
   int abstain;
   int timeout;
}
#define SELL_OBJECT_NAME_PROP "sell name"
#define SELL_OBJECT_OWNER_PROP "sell owner"
#define SELL_OBJECT_CLASS_PROP "sell class"
#define SELL_OBJECT_ID_PROP "sell id"
private nosave mapping _sellables;
private nosave object _sell_list;
private nosave mapping _royalties;
private nosave int _current_save_num;
private nosave mapping _categories;
private nosave int _category_callout;
private nosave int _category_dont_use_name;
private nosave function _save_function;
private nosave function _load_function;
private nosave function _category_function;
private nosave int *_current_ids;
private nosave int _has_loaded;
void load_it();
void save_it();
private void update_sellable(string name);
class craft_object create_craft_object(object ob,
                                       string owner,
                                       int cost,
                                       string category);
void adjust_royalty(string player, int amt);
class craft_sellable create_craft_sellable();
void adjust_royalty(string player, int amt);
class craft_object query_class_of_shop_object(object ob);
object find_shop_object(class craft_object frog);
object *query_sell_list_obs();
string query_id_of_shop_object(object ob);
void remove_shop_id(string id);
private void setup_timeout_call();
object* query_items_with_shop_id(string id);
void create() {
   _sell_list = clone_object("/std/container");
   _current_save_num = 1;
   _current_ids = ({ });
   _categories = ([ ]);
}
void set_dont_use_name(int flag) {
   _category_dont_use_name = flag;
}
int query_dont_use_name() {
   return _category_dont_use_name;
}
protected int create_auto_load_file(mixed ob, int fixed_num) {
   mixed *auto_load;
   mixed tmp;
   if (objectp(ob)) {
      if (this_player()) {
         catch(auto_load = this_player()->create_auto_load(({ ob })));
      }
      if (!auto_load) {
         catch(auto_load = PLAYER_OB->create_auto_load(({ ob })));
      }
      if (!auto_load) {
         auto_load = AUTO_LOAD_OB->create_auto_load(({ ob }));
      }
   } else if (pointerp(ob)) {
      auto_load = ob;
   } else {
      printf("Error!  Dammit!\n");
   }
   if (!fixed_num) {
      do {
         tmp = evaluate(_load_function,
                        CRAFT_SHOP_DATA_SAVE_FILE,
                        "" + _current_save_num);
         if (tmp) {
            _current_save_num++;
         }
      } while (tmp);
      fixed_num = _current_save_num;
   }
   evaluate(_save_function,
            CRAFT_SHOP_DATA_SAVE_FILE,
            auto_load,
            "" + fixed_num);
   return fixed_num;
}
protected object create_real_auto_load_object(int num, object player) {
   mixed *auto_load;
   object *obs;
   auto_load = evaluate(_load_function,
                        CRAFT_SHOP_DATA_SAVE_FILE,
                        "" + num);
   if (userp(player)) {
      obs = player->load_auto_load_to_array(auto_load, player);
   } else if (this_player()) {
      obs = this_player()->load_auto_load_to_array(auto_load, player);
   } else {
      obs = PLAYER_OB->load_auto_load_to_array(auto_load, player);
   }
   if (sizeof(obs)) {
      return obs[0];
   }
   return 0;
}
protected void remove_auto_load_file(int num) {
   evaluate(_save_function,
            CRAFT_SHOP_REMOVE_DATA_SAVE_FILE,
            0,
            "" + num);
}
protected void add_to_sellables(string name,
                                string owner,
                                class craft_object *ob) {
   class craft_sellable craft_sell;
   if (_sellables[name]) {
      craft_sell = (class craft_sellable)_sellables[name];
   } else {
      craft_sell = create_craft_sellable();
      _sellables[name] = craft_sell;
   }
   if (!craft_sell->objects[owner]) {
      craft_sell->objects[owner] = ({ });
   }
   craft_sell->objects[owner] += ob;
   update_sellable(name);
}
int add_list_object(object ob,
                    string name,
                    int cost,
                    string owner,
                    string category,
                    int dont_update_cost) {
   class craft_object craft_ob;
   string cap_owner;
   if (!objectp(ob) || !stringp(name) || !intp(cost)) {
      return 0;
   }
   cap_owner = owner;
   owner = lower_case(owner);
   add_to_sellables(name,
                    owner,
                    ({ create_craft_object(ob, cap_owner, cost, category) }));
   if (!dont_update_cost) {
      foreach (craft_ob in ((class craft_sellable)_sellables[name])->objects[owner]) {
         craft_ob->cost = cost;
         craft_ob->category = category;
      }
   }
   save_it();
   return 1;
}
void remove_list_object(string name, string owner, class craft_object ob) {
   int i;
   object us;
   class craft_object *data;
   if (_sellables[name] &&
       ((class craft_sellable)_sellables[name])->objects[owner]) {
      data = ((class craft_sellable)_sellables[name])->objects[owner];
      for (i = 0; i < sizeof(data); i++) {
         if (data[i] == ob) {
            break;
         }
      }
      if (i < sizeof(data)) {
         ((class craft_sellable)_sellables[name])->objects[owner] -= ({ ob });
         if (!sizeof(((class craft_sellable)_sellables[name])->objects[owner])) {
            map_delete(((class craft_sellable)_sellables[name])->objects, owner);
            if (!sizeof(((class craft_sellable)_sellables[name])->objects)) {
               map_delete(_sellables, name);
               us = find_shop_object(ob);
               remove_shop_id(query_id_of_shop_object(us));
            }
         }
         save_it();
         remove_auto_load_file(ob->ob_num);
         us = find_shop_object(ob);
         us->dest_me();
      } else {
         printf("Unable to find the object to remove? %O, %O\n", name, owner);
      }
   }
}
object create_real_object(object player, class craft_object craft) {
   return create_real_auto_load_object(craft->ob_num, player);
}
object *create_all_real_objects(object player, object *obs) {
   object *ret;
   object ob;
   class craft_object craft;
   object new_ob;
   ret = ({ });
   foreach (ob in obs) {
      craft = query_class_of_shop_object(ob);
      new_ob = create_real_object(player, craft);
      if (!new_ob) {
         ret->move("/room/rubbish");
         return ({ });
      }
      ret += ({ new_ob });
   }
   return ret;
}
class craft_object create_craft_object(object ob,
                                       string owner,
                                       int cost,
                                       string category) {
   class craft_object craft;
   int num;
   craft = new (class craft_object);
   num = create_auto_load_file(ob, 0);
   craft->ob_num = num;
   craft->cost = cost;
   craft->cap_owner = owner;
   craft->category = category;
   craft->short = ob->query_short();
   return craft;
}
class craft_sellable create_craft_sellable() {
   class craft_sellable craft;
   craft = new(class craft_sellable);
   craft->objects = ([ ]);
   return craft;
}
string query_owner_of_shop_object(object ob) {
   return ob->query_property(SELL_OBJECT_OWNER_PROP);
}
string query_name_of_shop_object(object ob) {
   return ob->query_property(SELL_OBJECT_NAME_PROP);
}
string query_id_of_shop_object(object ob) {
   return ob->query_property(SELL_OBJECT_ID_PROP);
}
void set_id_of_shop_objects(object *obs, string id) {
   obs->add_property(SELL_OBJECT_ID_PROP, id);
   obs->add_alias(id);
}
string query_category_of_shop_object(object ob) {
   class craft_object craft;
   craft = query_class_of_shop_object(ob);
   if (craft) {
      return craft->category;
   }
   return 0;
}
string query_short_of_shop_object(object ob) {
   class craft_object craft;
   craft = query_class_of_shop_object(ob);
   if (craft) {
      if (sizeof(craft) == 5) {
         return craft->short;
      }
      return "womble";
   }
   return 0;
}
void update_craft_object(object craft_ob, object replacement_ob) {
   class craft_object craft;
   craft = query_class_of_shop_object(craft_ob);
   if (craft) {
      create_auto_load_file(replacement_ob, craft->ob_num);
   }
}
string query_next_shop_id() {
   int num;
   num = 0;
   while (member_array(num, _current_ids) != -1) {
      num++;
   }
   _current_ids += ({ num });
   return sprintf("%c%c", (num / 26) + 'a',
                          (num % 26) + 'a');
}
void remove_shop_id(string id) {
   int real_id;
   real_id = (id[0] * 26) - 'a' + id[1] - 'a';
   _current_ids -= ({ real_id });
}
class craft_object query_class_of_shop_object(object ob) {
   return ob->query_property(SELL_OBJECT_CLASS_PROP);
}
object find_shop_object(class craft_object frog) {
   object ob;
   foreach (ob in query_sell_list_obs()) {
      if (query_class_of_shop_object(ob) == frog) {
         return ob;
      }
   }
   return 0;
}
void change_value_of_shop_object(object ob, int value) {
   string owner;
   string name;
   class craft_object wombat;
   object* obs;
   obs = query_items_with_shop_id(query_id_of_shop_object(ob));
   foreach (ob in obs) {
      owner = query_owner_of_shop_object(ob);
      name = query_name_of_shop_object(ob);
      wombat = query_class_of_shop_object(ob);
      wombat->cost = value;
      ob->set_value(value);
   }
   save_it();
}
int change_name_of_shop_object(object ob, string new_name,
                               int dont_update_cost) {
   string owner;
   string name;
   object* obs;
   string* names;
   class craft_object wombat;
   int new_cost;
   class craft_object* fluff;
   int i;
   obs = query_items_with_shop_id(query_id_of_shop_object(ob));
   names = ({ });
   foreach (ob in obs) {
      owner = query_owner_of_shop_object(ob);
      name = query_name_of_shop_object(ob);
      wombat = query_class_of_shop_object(ob);
      if (!_sellables[name]) {
tell_creator("pinkfish", "The name %O does not exist.\n", name);
         return 0;
      }
      if (!wombat) {
tell_creator("pinkfish", "Unable to find the class.\n");
         return 0;
      }
      if (!dont_update_cost &&
          _sellables[new_name] &&
          (((class craft_sellable)_sellables[new_name])->objects[owner])) {
         new_cost = (((class craft_sellable)_sellables[new_name])->objects[owner])[0]->cost;
         wombat->cost = new_cost;
      }
      if (!_sellables[new_name]) {
         _sellables[new_name] = create_craft_sellable();
      }
      if (!(((class craft_sellable)_sellables[new_name])->objects[owner])) {
         (((class craft_sellable)_sellables[new_name])->objects[owner]) = ({ });
      }
      (((class craft_sellable)_sellables[new_name])->objects[owner]) += ({ wombat });
      fluff = ((class craft_sellable)_sellables[name])->objects[owner];
      for (i = 0; i < sizeof(fluff); i++) {
         if (fluff[i] == wombat) {
            fluff = fluff[0..i-1] + fluff[i+1..];
         }
      }
      if (sizeof(fluff)) {
         ((class craft_sellable)_sellables[name])->objects[owner] = fluff;
      } else {
         map_delete(((class craft_sellable)_sellables[name])->objects, owner);
      }
      if (!sizeof(((class craft_sellable)_sellables[name])->objects)) {
         map_delete(_sellables, name);
      }
      names |= ({ name });
   }
   if (sizeof(names)) {
      update_sellable(name);
      update_sellable(new_name);
      save_it();
      return 1;
   }
   return 0;
}
int change_category_of_shop_object(object ob, string new_category) {
   string owner;
   string name;
   class craft_object bing;
   object* obs;
   int do_save;
   obs = query_items_with_shop_id(query_id_of_shop_object(ob));
   foreach (ob in obs) {
      owner = query_owner_of_shop_object(ob);
      name = query_name_of_shop_object(ob);
      if (!_sellables[name] ||
          !((class craft_sellable)_sellables[name])->objects[owner]) {
         return 0;
      }
      foreach (bing in ((class craft_sellable)_sellables[name])->objects[owner]) {
         bing->category = new_category;
         do_save = 1;
      }
   }
   if (do_save) {
      save_it();
   }
   return 1;
}
void remove_shop_object(object ob) {
   string name;
   string owner;
   owner = query_owner_of_shop_object(ob);
   name = query_name_of_shop_object(ob);
   remove_list_object(name, owner, query_class_of_shop_object(ob));
}
class obj_match find_matching_objects(string str) {
   class obj_match obs;
   obs = (class obj_match)match_objects_in_environments(str, ({ _sell_list }));
   return obs;
}
int value_of_objects(object *obs) {
   object ob;
   class craft_object craft;
   int value;
   foreach (ob in obs) {
      craft = query_class_of_shop_object(ob);
      if (craft) {
         value += craft->cost;
      }
   }
   return value;
}
object *sell_objects(object *obs, string place, object player, int cut) {
   object ob;
   object this_ob;
   object *sold;
   class craft_object craft;
   sold = ({ });
   if (cut < 0) {
      cut = 0;
   }
   if (cut > 100) {
      cut = 100;
   }
   foreach (ob in obs) {
      craft = query_class_of_shop_object(ob);
      if (craft) {
         if (player->query_value_in(place) >= craft->cost) {
            this_ob = create_real_object(player, craft);
            if (this_ob && this_ob->move(player) == MOVE_OK) {
               sold += ({ this_ob });
               player->pay_money(
                       MONEY_HAND->create_money_array(craft->cost, place),
                       place);
               adjust_royalty(query_owner_of_shop_object(ob),
                              craft->cost - (craft->cost * cut) / 100);
               remove_shop_object(ob);
            }
         }
      }
   }
   return sold;
}
void delete_objects( string id ) {
   object ob, *obs;
   obs = all_inventory( _sell_list );
   obs = filter( obs,
         (: $1->query_property( SELL_OBJECT_ID_PROP ) == $(id) :) );
   foreach( ob in obs ) {
      remove_shop_object( ob );
   }
}
object *buy_objects(object *obs,
                    string name,
                    int cost,
                    string owner,
                    string category,
                    int dont_update_costs) {
   object ob;
   object *bought;
   bought = ({ });
   foreach (ob in obs) {
      if (add_list_object(ob, name, cost, owner, category, dont_update_costs)) {
         ob->move("/room/rubbish");
         bought += ({ ob });
      }
   }
   return bought;
}
protected object create_dummy_object(string owner, string name, int cost,
                                     class craft_object craft) {
   object new_name;
   string *bits;
   new_name = clone_object("/std/object");
   new_name->reset_get();
   bits = explode(lower_case(name), " ");
   if (!sizeof (bits)) {
    new_name->set_name("error");
   }
   else {
    new_name->set_name(bits[<1]);
    new_name->add_adjective(bits[0..<2]);
   }
   if (member_array(lower_case(owner), bits) == -1) {
      new_name->add_adjective(owner);
   }
   if (!_category_dont_use_name &&
       member_array(lower_case(owner) + "'s", bits) == -1) {
      new_name->add_adjective(lower_case(owner) + "'s");
      new_name->set_short(craft->cap_owner + "'s " + name);
   } else {
      new_name->set_short(capitalize(name));
   }
   new_name->add_property(SELL_OBJECT_NAME_PROP, name);
   new_name->add_property(SELL_OBJECT_OWNER_PROP, owner);
   new_name->add_property(SELL_OBJECT_CLASS_PROP, craft);
   new_name->add_property("determinate", "");
   new_name->set_value(cost);
   return new_name;
}
private void add_sell_object(object ob) {
   if (ob->move(_sell_list) != MOVE_OK) {
      printf("Unable to move %O into the sell list (%O).\n", ob, _sell_list);
   }
}
object *query_sell_list_obs() {
   return all_inventory(_sell_list);
}
object query_sell_list() {
   return _sell_list;
}
object* query_items_with_shop_id(string id) {
   return filter(query_sell_list_obs(), (: query_id_of_shop_object($1) == $2 :),
                 id);
}
private void update_sellable(string name) {
   string owner;
   class craft_sellable bing;
   mixed *data;
   class craft_object womble;
   class craft_object craft;
   object shop_ob;
   string id;
   mixed *need_ids;
   int cost;
   mapping costs;
   int pos;
   if (_sellables[name]) {
      bing = _sellables[name];
      costs = ([ ]);
      foreach (owner, data in bing->objects) {
         id = 0;
         data = filter(data, (: $1 :));
         bing->objects[owner] = data;
         pos = 0;
         foreach (womble in data) {
            if (sizeof(womble) == 4) {
               craft = new(class craft_object);
               craft->ob_num = womble->ob_num;
               craft->cost = womble->cost;
               craft->cap_owner = womble->cap_owner;
               craft->category = womble->category;
               craft->short = "womble";
               data[pos] = craft;
            }
            pos++;
            shop_ob = find_shop_object(womble);
            if (!shop_ob ||
                query_name_of_shop_object(shop_ob) != name) {
               if (shop_ob) {
                  shop_ob->move("/room/rubbish");
               }
               add_sell_object(create_dummy_object(owner, name,
                                                   womble->cost, womble));
            }
            shop_ob = find_shop_object(womble);
            if (!costs[womble->cost]) {
               costs[womble->cost] = ({ 0, ({ }) });
            }
            if (!costs[womble->cost][0]) {
               id = query_id_of_shop_object(shop_ob);
               if (id) {
                  costs[womble->cost][0] = id;
               }
            }
            if (!costs[womble->cost][0] ||
                query_id_of_shop_object(shop_ob) != costs[womble->cost][0]) {
               costs[womble->cost][1] += ({ shop_ob });
            }
         }
         if (!_category_dont_use_name) {
            foreach (cost, need_ids in costs) {
               if (!need_ids[0]) {
                  need_ids[0] = query_next_shop_id();
               }
               set_id_of_shop_objects(need_ids[1], need_ids[0]);
            }
         }
      }
      if (_category_dont_use_name) {
         foreach (cost, need_ids in costs) {
            if (!need_ids[0]) {
               need_ids[0] = query_next_shop_id();
            }
            set_id_of_shop_objects(need_ids[1], need_ids[0]);
         }
      }
   }
}
string *query_owner_sellables(string owner) {
   class craft_sellable sell;
   mixed *womble;
   string *ret;
   string name;
   ret = ({ });
   foreach (name, sell in _sellables) {
      if (sell->objects[owner]) {
         womble = sell->objects[owner];
         ret += allocate(sizeof(womble), (: $(name) :) );
      }
   }
   return ret;
}
int query_list_object_cost(string name, string owner) {
   class craft_sellable sell;
   class craft_object wombat;
   owner = lower_case(owner);
   if (_sellables[name]) {
      sell = _sellables[name];
      if (sell->objects[owner]) {
         wombat = sell->objects[owner][0];
         return wombat->cost;
      }
   }
   return 0;
}
void set_save_function(function func) {
   _save_function = func;
}
void set_load_function(function func) {
   _load_function = func;
}
void set_category_function(function func) {
   _category_function = func;
}
void save_it() {
   if (_has_loaded) {
      evaluate(_save_function, CRAFT_SHOP_MAIN_SAVE_FILE,
            ({ _sellables, _royalties, _current_save_num, _categories }) );
   }
}
void load_it() {
   mixed *map;
   string name;
   _has_loaded = 1;
   map = evaluate(_load_function, CRAFT_SHOP_MAIN_SAVE_FILE);
   if (pointerp(map) && sizeof(map) == 3) {
      _sellables = map[0];
      _royalties = map[1];
      _current_save_num = map[2];
      foreach (name in keys(_sellables)) {
         reset_eval_cost();
         update_sellable(name);
      }
   } else if (pointerp(map) && sizeof(map) == 4) {
      _sellables = map[0];
      _royalties = map[1];
      _current_save_num = map[2];
      _categories = map[3];
      foreach (name in keys(_sellables)) {
         reset_eval_cost();
         update_sellable(name);
      }
   } else {
      _sellables = ([ ]);
      _royalties = ([ ]);
   }
   setup_timeout_call();
}
void adjust_royalty(string player, int amt) {
   _royalties[player] += amt;
   save_it();
}
int query_royalty(string player) {
  return _royalties[player];
}
mapping query_all_royalties() {
   return copy(_royalties);
}
void pay_out_royalty(string player, string place, int amount) {
   object pl;
   pl = find_player(player);
   if (pl && _royalties[player]) {
      if (!amount) {
         amount = _royalties[player];
      }
      pl->adjust_money(MONEY_HAND->create_money_array(amount, place));
      _royalties[player] -= amount;
      if (!_royalties[player]) {
         map_delete(_royalties, player);
      }
      save_it();
   }
}
int is_valid_category(string category) {
   if (_categories[category] &&
       (_categories[category]->state == CRAFT_CATEGORY_STATE_ACCEPTED ||
        _categories[category]->state == CRAFT_CATEGORY_STATE_DELETEING)) {
      return 1;
   }
   return 0;
}
int add_category_request(string name,
                         object player,
                         int timeout) {
   if (!_categories[name]) {
      _categories[name] = new(class craft_category);
      _categories[name]->state = CRAFT_CATEGORY_STATE_NOMINATING;
      _categories[name]->voted = ({ player->query_name() });
      _categories[name]->description = 0;
      _categories[name]->yes = 0;
      _categories[name]->no = 0;
      _categories[name]->timeout = time() + timeout;
      save_it();
      return 1;
   }
   return 0;
}
int remove_category_accepted(string category) {
   if (_categories[category]) {
      map_delete(_categories, category);
      save_it();
      return 1;
   }
   return 0;
}
int add_category_accepted(string name) {
   if (!_categories[name]) {
      _categories[name] = new(class craft_category);
      _categories[name]->state = CRAFT_CATEGORY_STATE_ACCEPTED;
      _categories[name]->voted = ({ });
      _categories[name]->description = 0;
      _categories[name]->yes = 0;
      _categories[name]->no = 0;
      _categories[name]->timeout = 0;
      save_it();
      return 1;
   }
   return 0;
}
void set_category_description(string cat, string desc) {
   if (_categories[cat]) {
      _categories[cat]->description = desc;
      save_it();
   }
}
string query_category_description(string cat) {
   if (_categories[cat]) {
      if (stringp(_categories[cat]->description)) {
         return _categories[cat]->description;
      }
   }
   return 0;
}
void set_category_information(string cat, string info) {
   if (_categories[cat]) {
      _categories[cat]->information = info;
      save_it();
   }
}
string query_category_information(string cat) {
   if (_categories[cat]) {
      if (stringp(_categories[cat]->information)) {
         return _categories[cat]->information;
      }
   }
}
string query_category_of(string name, string owner) {
   if (_sellables[name] &&
       sizeof( ((class craft_sellable)_sellables[name])->objects[owner])) {
      return ((class craft_sellable)_sellables[name])->objects[owner][0]->category;
   }
   return 0;
}
int has_voted_for_category(string name,
                           object player) {
   return _categories[name] &&
       member_array(player->query_name(), _categories[name]->voted) != -1;
}
int query_category_timeout(string name) {
   if (_categories[name]) {
      return _categories[name]->timeout;
   }
   return CRAFT_CATEGORY_ERROR;
}
int vote_for_category(string name,
                      object player,
                      int choice) {
   if (_categories[name]) {
      if (!has_voted_for_category(name, player)) {
         if (choice == CRAFT_CATEGORY_CHOICE_YES ||
             choice == CRAFT_CATEGORY_CHOICE_NO ||
             choice == CRAFT_CATEGORY_CHOICE_ABSTAIN) {
            switch (choice) {
            case CRAFT_CATEGORY_CHOICE_YES :
               _categories[name]->yes++;
               break;
            case CRAFT_CATEGORY_CHOICE_NO :
               _categories[name]->no++;
               break;
            case CRAFT_CATEGORY_CHOICE_ABSTAIN :
               _categories[name]->abstain++;
               break;
            }
            _categories[name]->voted += ({ player->query_name() });
            save_it();
         }
      }
   }
   return 0;
}
string* query_categories() {
   return filter(keys(_categories), (: is_valid_category($1) :));
}
private void do_timeout_categories() {
   string name;
   class craft_category cat;
   int timeout;
   foreach (name, cat in _categories) {
      if (cat->state != CRAFT_CATEGORY_STATE_ACCEPTED &&
          cat->timeout &&
          cat->timeout < time()) {
         timeout = evaluate(_category_function,
                            cat->state,
                            cat->voted,
                            cat->yes,
                            cat->no,
                            cat->abstain);
         if (timeout) {
            cat->voted = ({ });
            cat->yes = 0;
            cat->no = 0;
            switch (cat->state) {
            case CRAFT_CATEGORY_STATE_NOMINATING :
               cat->state = CRAFT_CATEGORY_STATE_VOTING;
               cat->timeout = time() + timeout;
               break;
            case CRAFT_CATEGORY_STATE_VOTING :
               cat->state = CRAFT_CATEGORY_STATE_ACCEPTED;
               cat->timeout = 0;
               break;
            case CRAFT_CATEGORY_STATE_DELETEING :
               map_delete(_categories, name);
               break;
            }
         } else {
            switch (cat->state) {
            case CRAFT_CATEGORY_STATE_VOTING :
            case CRAFT_CATEGORY_STATE_NOMINATING :
               map_delete(_categories, name);
               break;
            case CRAFT_CATEGORY_STATE_DELETEING :
               cat->state = CRAFT_CATEGORY_STATE_ACCEPTED;
               cat->timeout = 0;
               cat->voted = ({ });
               cat->yes = 0;
               cat->no = 0;
               break;
            }
         }
      }
   }
   save_it();
   setup_timeout_call();
}
private void setup_timeout_call() {
   string name;
   class craft_category cat;
   int bing;
   foreach (name, cat in _categories) {
      if (cat->state != CRAFT_CATEGORY_STATE_ACCEPTED &&
          cat->timeout != 0 &&
          cat->timeout < bing) {
         bing = cat->timeout;
      }
   }
   if (_category_callout) {
      remove_call_out(_category_callout);
   }
   if (bing) {
      _category_callout = call_out((: do_timeout_categories() :), bing);
   }
}
void dest_me() {
  if(_sell_list) {
    all_inventory(_sell_list)->move("/room/rubbish");
    _sell_list->dest_me();
  }
  destruct(this_object());
}