# File: /lib/std/room/furniture/commercial.c

#include <move_failures.h>
#include <position.h>
#include <money.h>
inherit "/std/object";
inherit "/std/basic/item_chat";
inherit "/std/room/furniture/inherit/furniture_base";
string query_main_status(int hints);
private nosave int _commercial_size;
private nosave string _commercial_type;
private nosave string _commercial_name;
private nosave string* _use_types;
private nosave string _info;
private int _revenue;
private int _weekly_revenue;
private int _commercial_id;
private int _weekly_upkeep_cost;
#define OBJECT_TAG "commercial inh"
void create() {
   _commercial_size = 100;
   if (!_use_types) {
      _use_types = ({ });
   }
   do_setup++;
   object::create();
   furniture_base::create();
   add_alias( "furniture" );
   add_plural( "furniture" );
   add_property("talisman", "no one");
   set_opaque();
   if ( !query_property( "shop type" ) ) {
      add_property( "shop type", "furniture" );
   }
   do_setup--;
   if ( !do_setup ) {
     this_object()->setup();
   }
   set_no_all(1);
   reset_get();
}
void set_weekly_upkeep_cost(int cost) {
   _weekly_upkeep_cost = cost;
}
int query_weekly_upkeep_cost() {
   return _weekly_upkeep_cost;
}
int query_revenue() {
   return _revenue;
}
void set_revenue(int revenue) {
   _revenue = revenue;
}
string query_save_dir() {
   return environment()->query_save_dir();
}
string query_owner() {
  return environment()->query_owner();
}
string query_language() {
  return environment()->query_language();
}
string query_money_place() {
   if (!environment()) {
      return "default";
   }
   return environment()->query_property("place");
}
int is_allowed(string person) {
   return environment()->is_allowed(person);
}
string query_allowed() {
   return environment()->query_allowed();
}
int query_float() {
   return environment()->query_royalty(query_owner());
}
int query_royalty(string person) {
   return environment()->query_royalty(person);
}
int adjust_royalty(string person, int amount) {
   if (person == query_owner()) {
      _revenue += amount;
      _weekly_revenue += amount;
   }
   environment()->adjust_royalty(person, amount);
}
int adjust_float(int amt) {
   adjust_royalty(query_owner(), amt);
}
int is_open_for(string type, string person) {
   if (!environment()->query_commercial_property()) {
      return 0;
   }
   return environment()->is_open_for(type, person);
}
void set_commercial_size(int size) {
   _commercial_size = size;
}
string query_commercial_type() {
   return _commercial_type;
}
void set_commercial_type(string type) {
   _commercial_type = type;
}
void set_commercial_information(string info) {
   _info = info;
}
string query_commercial_information() {
   return _info;
}
void set_commercial_name(string name) {
   _commercial_name = name;
}
string query_commercial_name() {
   return _commercial_name;
}
int query_commercial_size() {
   return _commercial_size;
}
int query_commercial_id() {
   return _commercial_id;
}
void setup_new_commercial_id() {
   _commercial_id = environment()->find_next_commercial_id();
}
void set_commercial_id(int id) {
   _commercial_id = id;
}
string query_parcel_post() {
   return environment()->query_parcel_post();
}
void set_shop_use_types(string* types) {
   _use_types = types;
}
string* query_shop_use_types() {
   return _use_types;
}
void reset_weekly_status() {
   _weekly_revenue = 0;
}
string query_weekly_status_string() {
   string ret;
   string place;
   place = query_money_place();
   if (query_weekly_upkeep_cost()) {
      ret = "Weekly Upkeep : " +
            MONEY_HAND->money_value_string(_weekly_upkeep_cost, place) + "\n" +
            "Weekly Revenue: " +
            MONEY_HAND->money_value_string(_weekly_revenue, place) + "\n" +
            "Profit        : " +
            MONEY_HAND->money_value_string(_weekly_revenue - _weekly_upkeep_cost, place) + "\n";
   } else {
      ret = "Weekly Revenue: " +
            MONEY_HAND->money_value_string(_weekly_revenue, place) + "\n";
   }
   return ret;
}
int can_trash_furniture() {
   return 1;
}
int query_commercial_furniture() {
   return 1;
}
varargs int move( mixed dest, string messin, string messout ) {
   int i;
   int t;
   int f;
   object from;
   if(stringp(dest)) {
      dest = find_object(dest);
   }
   if (!move_check(dest)) {
      write(the_short() + " resists being picked up and shocks you slightly.\n");
      return MOVE_INVALID_DEST;
   }
   if(!dest) {
      return MOVE_INVALID_DEST;
   }
   if(living(dest)) {
      t = (int)this_object()->query_complete_weight() * 5;
      if(!(dest->add_weight(t))) {
         return MOVE_TOO_HEAVY;
      }
      debug_printf("Added %d", t);
   }
   from = environment();
   i = ::move(dest, messin, messout);
   if(i != MOVE_OK) {
      dest->add_weight(-t);
      return i;
   }
   if(from && living(from)) {
      f = (int)this_object()->query_complete_weight() * 5;
      from->add_weight(-f);
   }
   if (from) {
      from->remove_commercial_thing(this_object());
   }
   dest->add_commercial_thing(this_object());
   dest->register_use_types(_use_types);
   return i;
}
int get(mixed dest) {
   if(!move_check(dest)) {
      write("You feel it would be wrong to take " + the_short() + ".\n");
      return 2;
   }
   return ::get(dest);
}
int do_status(int hint) {
   string ret;
   ret = query_main_status(hint);
   write("$P$Status$P$" + ret);
   add_succeeded_mess("$N get$s the status of $D.\n");
   return 1;
}
int do_reset() {
   string place;
   int old_revenue;
   place = query_money_place();
   old_revenue = _revenue;
   _revenue = 0;
   add_succeeded_mess("$N clear$s the revenue of " +
                      MONEY_HAND->money_value_string(old_revenue, place) +
                      " on $D.\n");
   return 1;
}
void init() {
   ::init();
   if (is_allowed(this_player()->query_name())) {
      add_command("status", "<direct:object>", (: do_status, 0 :));
      add_command("status", "hints <direct:object>", (: do_status, 1 :));
      add_command("status", "hint <direct:object>", (: do_status, 1 :));
      add_command("reset", "revenue on <direct:object>", (: do_reset :));
   }
}
mixed query_static_auto_load() {
  if ( base_name(this_object()) + ".c" == __FILE__ ) {
    return int_query_static_auto_load();
  }
  return ([ ]);
}
mixed query_dynamic_auto_load() {
   mapping junk;
   junk = object::query_dynamic_auto_load();
   if (!junk) {
      junk = ([ ]);
   }
   junk["bonded"] = query_bonded();
   add_auto_load_value(junk, OBJECT_TAG, "revenue", query_revenue());
   add_auto_load_value(junk, OBJECT_TAG, "commercial id", query_commercial_id());
   return junk;
}
void init_dynamic_arg(mapping map) {
   object::init_dynamic_arg(map);
   if (map) {
      set_bonded(map["bonded"]);
      set_revenue(query_auto_load_value(map, OBJECT_TAG, "revenue"));
      if (query_auto_load_value(map, OBJECT_TAG, "commercial id")) {
         set_commercial_id(query_auto_load_value(map, OBJECT_TAG, "commercial id"));
      }
   }
}
string query_help_file_directory() {
   return "/doc/furniture/";
}
mixed *stats() {
   return ::stats() +
          ({ ({ "revenue", query_revenue() }),
             ({ "bonded", query_bonded() }),
             ({ "commercial id", query_commercial_id() }) });
}