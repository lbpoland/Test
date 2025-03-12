#include <move_failures.h>
#include <player.h>
inherit "/global/auto_load";
#define SAVE_TIME 10
#if 0
#undef AUTO_LOAD_OB
#define AUTO_LOAD_OB "/global/auto_load_debug"
#endif
varargs void set_save_file( string file, object thing );
varargs void do_load(object thing);
mapping query_dynamic_auto_load();
void init_dynamic_arg(mapping bing);
private mapping details;
private nosave string _save_file, _ram_file;
private nosave object _effects;
private nosave int _inventory_loaded;
private nosave int _last_saved;
private nosave int _door_opened, _door_unlocked;
#ifdef DEBUG_SAVE
void debug_log(string fmt, mixed args ...) {
    debug_printf(fmt + "\n", args ...);
#ifdef DISABLED
  if(base_name(this_object()) == "/d/cwc/Bes_Pelargic/Shoo_Li/roads/pang_ho_street/housing/03flat") {
    log_file("HOUSING_DEBUG", "%s (%s): " + fmt + "\n",
             ctime(time())[4..18], base_name(this_object()), args ...);
  }
#endif
}
#endif
void create() {
   _save_file = "";
   details = ([ ]);
   _last_saved = time();
}
void set_save_file( string file) {
#ifdef USE_RAMDISK
  string *bits, fname;
  int i;
#endif
  _save_file = file;
#ifdef USE_RAMDISK
  if(strsrch(_save_file, "/save/player_housing") != -1) {
    _ram_file = replace_string(_save_file, "/save/player_housing",
                               "/save/ramdisk/player_housing");
    fname = "";
    bits = explode(_ram_file, "/");
    for(i=0; i<sizeof(bits)-1; i++) {
      fname += "/" + bits[i];
      if(file_size(fname) == -1) {
        debug_printf("Creating %s", fname);
        mkdir(fname);
      }
    }
  }
#endif
  do_load();
}
int test_save(object ob) { return 1; }
string query_save_file() {
   return _save_file;
}
void event_save(object thing) {
  if(!thing || !_inventory_loaded || !_save_file || _save_file == "") {
    if(find_call_out("do_save") != -1)
      remove_call_out("do_save");
    return;
  }
  if(thing == this_object() || base_name(thing) == "/std/room/basic/door" ||
     test_save(thing)) {
    if (find_call_out("do_save") == -1)
      call_out("do_save", SAVE_TIME);
  }
}
void door_action() {
  if(_door_opened || _door_unlocked) {
    event_save(this_object());
#ifdef DEBUG_SAVE
    debug_log("saving opened %d unlocked %d", _door_opened,
        _door_unlocked);
  } else {
    debug_log("not saving %s door has returned "
        "to original state.\n", base_name(this_object()));
#endif
  }
  _door_opened = 0;
  _door_unlocked = 0;
}
void event_open(object door, object opener) {
  _door_opened++;
  if(find_call_out("door_action") != -1)
    remove_call_out("door_action");
  call_out("door_action", 5);
}
void event_close(object door, object closer) {
  _door_opened--;
  if(find_call_out("door_action") != -1)
    remove_call_out("door_action");
  call_out("door_action", 5);
}
void event_unlock(object door, object unlocker) {
  debug_printf("Event unlock called %O", door);
  _door_unlocked++;
  if(find_call_out("door_action") != -1)
    remove_call_out("door_action");
  call_out("door_action", 5);
}
void event_lock(object door, object locker) {
  debug_printf("Event lock called %O", door);
  _door_unlocked--;
  if(find_call_out("door_action") != -1)
    remove_call_out("door_action");
  call_out("door_action", 5);
}
void do_save() {
  int saved;
#ifdef DEBUG_SAVE
  object ob;
#endif
  remove_call_out("do_save");
  if(!_save_file || _save_file == "") {
#ifdef DEBUG_SAVE
    log_file("ROOM_SAVE", "%s no save file for %s\n", ctime(time())[4..18],
             base_name(this_object()));
#endif
    return;
  }
  details = ([ ]);
  details = query_dynamic_auto_load();
#ifdef USE_RAMDISK
  if(_ram_file)
    saved = unguarded((: save_object, _ram_file, 3 :));
  else
#endif
    saved = unguarded((: save_object, _save_file, 3 :));
#ifdef DEBUG_SAVE
  if (saved) {
    log_file("HOUSING_DEBUG",
             "%s %s saved.\n", ctime(time())[4..18],
             base_name(this_object()));
  } else {
    log_file("HOUSING_DEBUG",
             "%s %s failed to save.\n", ctime(time())[4..18],
             base_name(this_object()));
  }
#endif
#ifdef DEBUG_INVENTORY
  foreach(ob in all_inventory(this_object())) {
    if(test_save(ob))
      log_file(base_name(this_object()) + ".log",
               "%s %s contained %d items.\n", ctime(time())[4..18],
               ob->query_short(), sizeof(deep_inventory(ob)));
  }
#endif
  _last_saved = time();
}
void do_load( object thing ) {
  mapping tmp;
  string fname;
  if(_save_file) {
    if(_ram_file &&
       (file_size(_ram_file + ".o.gz") > 0 || file_size(_ram_file + ".o") > 0))
      fname = _ram_file;
    else
      fname = _save_file;
    if(file_size(fname + ".o.gz") > 0 || file_size(fname + ".o") > 0) {
      tmp = this_object()->query_properties();
      unguarded((: restore_object, fname :));
      this_object()->set_properties(tmp);
      if ( sizeof( details ) ) {
        init_dynamic_arg( details );
      } else {
        _inventory_loaded = 1;
      }
    } else {
      _inventory_loaded = 1;
    }
  }
  _last_saved = time();
  remove_call_out("do_save");
  remove_call_out("door_action");
  _door_opened = 0;
  _door_unlocked = 0;
}
int test_remove(object thing, int flag, mixed dest) {
  if(test_save(thing))
    event(this_object(), "save", thing);
  return 1;
}
int test_add( object ob, int flag) {
  if(!query_auto_loading() && test_save(ob))
    event(this_object(), "save", ob);
  return 1;
}
int query_prevent_insert() { return 1; }
mapping query_dynamic_auto_load() {
  mapping map;
  string *obs;
  map = ([ ]);
#ifdef DISABLED
  if ( _effects ) {
    if ( sizeof( (mixed *)_effects->query_effs() ) ) {
      _effects->effect_freeze();
      _effects->effects_saving();
      map += ([
               "effects" : ({
                 (mixed *)_effects->query_effs(),
                 (int *)_effects->query_eeq()
               })
      ]);
      _effects->effect_unfreeze();
    }
  }
#endif
  obs = filter(all_inventory(this_object()), "test_save");
  catch(obs = AUTO_LOAD_OB->create_auto_load( obs, 0 ) );
  map["inv"] = obs;
  return map;
}
private int move_to_dest(object ob) {
   if (base_name(ob) == PLAYER_RECEIPT) {
      ob->reset_get();
   }
   return ob->move(this_object());
}
void init_dynamic_arg( mapping bing ) {
#ifdef DEBUG_INVENTORY
  object ob;
  log_file(base_name(this_object()) + ".log",
           "%s Loading.\n", ctime(time())[4..18]);
#endif
  if ( !mapp( bing ) ) {
#ifdef DEBUG_INVENTORY
  log_file(base_name(this_object()) + ".log",
           "%s no mapping to load.\n", ctime(time())[4..18]);
#endif
    return;
  }
  if ( bing[ "effects" ] ) {
    _effects->set_effs( bing[ "effects" ][ 0 ] );
    _effects->set_eeq( bing[ "effects" ][ 1 ] );
    if ( environment() && shadow( this_object(), 0 ) )
       move_object( environment() );
    _effects->init_after_save();
  }
#ifdef DEBUG_INVENTORY
  log_file(base_name(this_object()) + ".log",
           "%s done effects.\n", ctime(time())[4..18]);
#endif
  if ( bing[ "inv" ] && !_inventory_loaded) {
#ifdef DEBUG_INVENTORY
  log_file(base_name(this_object()) + ".log",
           "%s starting inventory.\n", ctime(time())[4..18]);
#endif
    AUTO_LOAD_OB->load_auto_load_to_inventory( bing["inv"], this_object(),
                                               this_player(),
                                               (: move_to_dest($1) :) );
    _inventory_loaded = 1;
  } else {
#ifdef DEBUG_INVENTORY
  log_file(base_name(this_object()) + ".log",
           "%s inventory_loaded already set.\n", ctime(time())[4..18]);
#endif
  }
#ifdef DEBUG_INVENTORY
  log_file(base_name(this_object()) + ".log",
           "%s done inventory.\n", ctime(time())[4..18]);
  foreach(ob in all_inventory(this_object())) {
    if(test_save(ob))
      log_file(base_name(this_object()) + ".log",
               "%s %s contains %d items.\n", ctime(time())[4..18],
               ob->query_short(), sizeof(deep_inventory(ob)));
  }
  if(!sizeof(all_inventory(this_object())))
    log_file(base_name(this_object()) + ".log",
             "%s room has no inventory.\n", ctime(time())[4..18]);
#endif
}
void check_euid() {
  if ( previous_object() ) {
    seteuid( geteuid( previous_object() ) );
  }
}
int query_keep_room_loaded() { return 1; }
void dest_me() {
  if(find_call_out("do_save") != -1)
    do_save();
}
int query_inventory_loaded() { return _inventory_loaded; }