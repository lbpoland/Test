inherit "/std/room/furniture/commercial";
inherit "/std/shops/inherit/player_craft_shop_base";
#define SAVE_TIME 1
private int _save_call;
private int _last_saved;
private string _counter_short;
#define OBJECT_TAG "shop base"
void create() {
   player_craft_shop_base::create();
   set_shop_use_types(({ "use", "buy" }));
   commercial::create();
   set_commercial_name("craft shop");
}
int query_player_craft_shop() {
   return 1;
}
int disallow_sale_here(object room) {
   object* obs;
   obs = room->find_commercial_items(query_commercial_name());
   return sizeof(obs);
}
int query_royalty(string person) {
   return commercial::query_royalty(person);
}
string query_craft_shop_save_dir() {
   return environment()->query_save_dir() + "craft_shop";
}
void adjust_royalty(string person, int amount) {
   commercial::adjust_royalty(person, amount);
}
string query_parcel_post() {
   return commercial::query_parcel_post();
}
void reset_weekly_status() {
   player_craft_shop_base::reset_weekly_status();
}
string query_weekly_status_string() {
   return player_craft_shop_base::query_weekly_status_string();
}
void load_me() {
  string fname, tmp;
#ifdef USE_RAMDISK
  tmp = replace_string(query_save_dir() + "craft_shop_file", "/save/",
                       "/save/ramdisk/");
  if(unguarded((: file_size($(tmp) = ".o.gz") :)) > 0 ||
     unguarded((: file_size($(tmp) = ".o") :)) > 0) {
    fname = tmp;
  }
#endif
  if(!fname) {
    fname = query_save_dir() + "craft_shop_file";
  }
   unguarded( (: restore_object($(fname)) :));
#ifdef USE_RAMDISK
   tmp = replace_string(query_craft_shop_save_dir(), "/save/",
                        "/save/ramdisk/");
   unguarded( (: mkdir($(tmp)) :));
#endif
   unguarded( (: mkdir(query_craft_shop_save_dir()) :));
   reload_shop();
   add_property("place", environment()->query_property("place"));
}
void init() {
   player_craft_shop_base::init();
   commercial::init();
}
void do_save() {
  string fname;
  string dir;
   _save_call = 0;
   if (environment() && query_save_dir()) {
#ifdef USE_RAMDISK
     dir = replace_string(query_save_dir(), "/save/",
                            "/save/ramdisk/");
     if (file_size(dir) == -2) {
        fname = dir + "craft_shop_file";
     }
#endif
     if(!fname) {
       fname = query_save_dir() + "craft_shop_file";
     }
     debug_printf("Saving to %O\n", fname);
     unguarded( (: save_object($(fname), 2) :));
   }
}
void dest_me() {
   do_save();
   player_craft_shop_base::dest_me();
   commercial::dest_me();
}
string query_commercial_information() {
   return "This shop can have a maximum of " + query_maximum_inventory_size() +
          " items for sale.  "
          "You can only have "
          "one shop counter in any room, more than one will not be "
          "able to be bought.";
}
void event_save(object ob) {
   if (!_save_call) {
      if(_last_saved > time() - SAVE_TIME) {
         _save_call = call_out("do_save", SAVE_TIME - (time() - _last_saved));
      } else {
         _save_call = call_out("do_save", SAVE_TIME);
      }
#ifdef DEBUG
      debug_printf("Adding call_out");
#endif
   }
}
mapping query_commercial_options() {
   return ([
    "counter type" : ([
       "polished hardwood counter" : 500000,
       "shiny polished counter" : 150000,
       "unfinished pine counter" : 0,
      ]),
   "stockroom size" : ([
       "50" : 0,
       "100" : 1000000,
       "150" : 2500000,
      ]),
   ]);
}
void set_commercial_option(string type, string name) {
   string* bits;
   int size;
   switch (type) {
   case "counter type" :
      _counter_short = name;
      set_short(_counter_short);
      bits = explode(lower_case(_counter_short), " ");
      add_adjective(bits[0..<2]);
      add_alias(bits[<1]);
      break;
   case "stockroom size" :
      sscanf(name, "%d", size);
      set_maximum_waiting_queue_size(size);
      break;
   }
}
mapping query_dynamic_auto_load() {
   mapping map;
   map = ::query_dynamic_auto_load();
   add_auto_load_value(map, OBJECT_TAG, "stocksize", query_maximum_waiting_queue_size());
   add_auto_load_value(map, OBJECT_TAG, "counter short", _counter_short);
}
void init_dynamic_arg(mapping map, object player) {
   string* bits;
   int size;
   commercial::init_dynamic_arg(map, player);
   size = query_auto_load_value(map, OBJECT_TAG, "stocksize");
   _counter_short = query_auto_load_value(map, OBJECT_TAG, "counter short");
   if (size) {
      set_maximum_waiting_queue_size(size);
   }
   if (_counter_short) {
      bits = explode(lower_case(_counter_short), " ");
      add_adjective(bits[0..<2]);
      add_alias(bits[<1]);
   }
}