#include <armoury.h>
#include <data.h>
#include <weather.h>
#include <hospital.h>
#define CREATE_NPCS 1
inherit "/std/room";
inherit HOSPITAL_ALIGNMENT_INHERIT;
public object *load_random_npc(string zone, int wealth, int busy);
protected void load_file();
protected void save_file();
protected void set_save_file(string new_save);
public void hospital_log_file(string file, string format, mixed *args ...);
public int get_item(object destination, string *items);
public string query_save_file();
public int *query_npcs();
public mapping query_hospital_npcs();
public void add_npc_type(string type, string *data);
public void regen_after_death( object dead_npc );
private nosave string _save_file;
private nosave string _hospital_type;
private nosave mixed *_regenerated_npcs;
private nosave int _hospital_call_id;
private nosave mapping _log_file_info;
private nosave string _hospital_log_directory;
private nosave string _data_directory;
private nosave string _npc_path;
private nosave string _domain;
private nosave int _max_cache;
private nosave int _disable_npc_generation;
private mapping _unique_npcs;
private mapping _hospital_npcs;
private mapping _cache_inventory;
private int _last_npc_check;
private int _zone_npcs;
private mapping _group_info;
private mapping _npc_info;
private mapping _zone_info;
private mapping _path_to_npc;
private mapping _file_modified_time;
void create() {
    seteuid(master()->creator_file(file_name(this_object())));
    do_setup++;
    ::create();
    do_setup--;
    if (!_group_info) {
        _group_info = ([ ]);
    }
    if (!_npc_info) {
        _npc_info = ([ ]);
    }
    if (!_zone_info) {
        _zone_info = ([ ]);
    }
    if (!_path_to_npc) {
        _path_to_npc = ([ ]);
    }
    if (!_file_modified_time) {
        _file_modified_time = ([ ]);
    }
    if (!_unique_npcs) {
        _unique_npcs = ([ ]);
    }
    if (!_cache_inventory) {
      _cache_inventory = ([ ]);
    }
    _regenerated_npcs = ({ });
    _log_file_info = ([ ]);
    if(!_max_cache)
      _max_cache = DEFAULT_MAX_CACHE;
    if (!do_setup) {
        set_short( "Un-configured Hospital" );
        set_long("This is an unconfigured hospital.  Find the right one.\n");
        add_property("determinate", "the ");
        set_light(60);
        this_object()->setup();
    }
}
int ok_to_clone() {
   return 1;
}
public string *query_deities() {
   return ({ "fish", "pishe", "sek", "hat", "gapp",
      "gufnork", "sandelfon" });
}
public int get_item(object destination, string *items) {
    int i;
    object item;
    if (!objectp(destination)) {
        return 0;
    }
    while (!item) {
        i = random(sizeof(items));
        item = ARMOURY->request_item(items[i], 80 + random(21), _domain);
        if (!item) {
            item = ARMOURY->request_item(items[i], 80 + random(21) );
            if ( !item ) {
                items = items[0..i-1] + items[i+1..];
                continue;
            }
        }
        if (!sizeof(items)) {
            hospital_log_file("BROKEN_ITEMS", "Unable to select any items "
                "for %s in the Ankh-Morpork hospital.\n",
                previous_object()->short());
            break;
        }
    }
    if (objectp(item)) {
        item->move(destination);
        return 1;
    }
    return 0;
}
protected void load_file() {
    class npc_info npc;
    class group_info group;
    string name;
    if (file_size(_save_file + ".o") > -1) {
        unguarded((: restore_object, _save_file :));
        if (!_group_info) {
            _group_info = ([ ]);
        } else {
            foreach (name, group in _group_info) {
                group->storage = 0;
            }
        }
        if (!_npc_info) {
            _npc_info = ([ ]);
        } else {
            foreach (name, npc in _npc_info) {
                npc->population = ({ });
            }
        }
        if (!_zone_info) {
            _zone_info = ([ ]);
        }
        if (!_path_to_npc) {
            _path_to_npc = ([ ]);
        }
        if (!_file_modified_time) {
            _file_modified_time = ([ ]);
        }
        if (!_unique_npcs) {
            _unique_npcs = ([ ]);
        }
    }
}
protected void save_file() {
    unguarded((: save_object, _save_file :));
}
protected void set_save_file(string new_save) {
    _save_file = new_save;
    load_file();
}
public string query_save_file() {
    return _save_file;
}
void set_data_directory(string dir) {
   _data_directory = dir;
   call_out("scan_for_new_data", 2);
}
string query_data_directory() {
   return _data_directory;
}
void set_npc_path(string path) {
  _npc_path = path;
}
void set_domain(string domain) {
  _domain = domain;
}
void set_max_cache(int num) {
  _max_cache = num;
}
void set_disable_npc_generation(int value) {
   _disable_npc_generation = value;
}
int query_disable_npc_generation() {
   return _disable_npc_generation;
}
public int make_unique(mixed who) {
    int delay;
    if (!_unique_npcs) {
        return 0;
    }
    if (objectp(who)) {
        who = who->query_name();
    }
    if (!_unique_npcs[who]) {
        _unique_npcs[who] = new(class unique_npc);
    }
    if ( _unique_npcs[who]->next_regen_time > time() ) {
        return 0;
    }
    if (_npc_info[who] && _npc_info[who]->delay) {
        delay = _npc_info[who]->delay;
    } else {
        delay = REGEN_TIME;
    }
    _unique_npcs[who]->next_regen_time = time() + delay;
    save_file();
    return 1;
}
public void reset_unique(string who) {
    if (!_unique_npcs[who]) {
        return ;
    }
    _unique_npcs[who]->next_regen_time = 0;
}
#ifdef REGENERATE_AFTER_DEATH
public void regen_after_death( object dead_npc ) {
    object *monsters, destination;
    class regenerated_npc new_npc;
    int i, max;
    if ( !dead_npc )
        return;
    _regenerated_npcs += ({ new( class regenerated_npc,
        type : dead_npc->query_property("monster_type"),
        load_position : previous_object()->query_property("start location") ) });
    if ( !ok_to_clone(_hospital_type) || sizeof(_regenerated_npcs) < MINIMUM_DEATH_REGEN )
        return;
    new_npc = _regenerated_npcs[0];
    if ( !classp( new_npc ) )
        return;
    _regenerated_npcs = _regenerated_npcs[1..];
    if (!new_npc->load_position || !new_npc->type );
        return;
    max = random(5);
    for ( i = 0; i < max; i++ ){
        destination = find_object( new_npc->load_position );
        if ( !objectp( destination ) )
            return;
        monsters = get_monster(new_npc->type);
        destination->replace_monster(previous_object(), monsters);
        call_out((: $1->announce_entry($2) :), 8 + random(6), destination,
            monsters);
    }
}
#endif
string npc_path(string str) {
   return _npc_path + "/" + str;
}
public void hospital_log_file(string file, string format, mixed *args ...) {
    string filename;
    filename = _hospital_log_directory;
    if (file[0] == '/') {
        file = file[ strsrch( file, "/", -1 ) + 1 .. ];
    }
    log_file( _hospital_log_directory + "/" + file, ctime(time()) + ": " + format, args ...);
}
protected void set_log_directory(string new_dir) {
    if (file_size(new_dir) != -2) {
        debug_printf( "%s: Invalid "
            "log directory -- defaulting to %s.\n",
            file_name( this_object() ), DEFAULT_LOG_DIRECTORY );
        new_dir = DEFAULT_LOG_DIRECTORY;
    }
    _hospital_log_directory = new_dir;
}
private void parse_zone(string fname, mapping data) {
   string name;
   class zone_info info;
   mapping bing;
   int chance;
   string* bits;
   if (!data["name"]) {
      debug_printf("No name for zone %O\n", data);
      hospital_log_file("COMPILE_ERROR", "No name for zone %O\n", data);
      return 0;
   }
   name = data["name"];
   if (data["group"] && !arrayp(data["group"])) {
      data["group"] = ({ data["group"] });
   } else if (!arrayp(data["groups"])) {
      data["group"] = ({ });
   }
   if (data["npc"] && !arrayp(data["npc"])) {
      data["npc"] = ({ data["npc"] });
   } else if (!arrayp(data["npc"])) {
      data["npc"] = ({ });
   }
   if (data["zone"] && !arrayp(data["zone"])) {
      data["zone"] = ({ data["zone"] });
   } else if (!arrayp(data["zone"])) {
      data["zone"] = ({ });
   }
   info = new(class zone_info, npcs : ([ ]), groups : ([ ]), zones : ([ ]));
   chance = 0;
   foreach (bing in data["npc"]) {
      if (!mapp(bing) || !stringp(bing["name"]) || !intp(bing["chance"])) {
         debug_printf("Invalid data for zone (%s) %O\n", name, bing);
         hospital_log_file("COMPILE_ERROR", "Invalid data for zone (%s) %O\n", name,  bing);
      } else {
         info->npcs[bing["name"]] = bing["chance"];
         chance += bing["chance"];
      }
   }
   info->npc_chance = chance;
   chance = 0;
   foreach (bing in data["group"]) {
      if (!mapp(bing) || !stringp(bing["name"]) || !intp(bing["chance"])) {
         debug_printf("Invalid data for zone (%s) %O\n", name, bing);
         hospital_log_file("COMPILE_ERROR", "Invalid data for zone (%s) %O\n", name,  bing);
      } else {
         info->groups[bing["name"]] = bing["chance"];
         chance += bing["chance"];
      }
   }
   info->group_chance = chance;
   chance = 0;
   foreach (bing in data["zone"]) {
      if (!mapp(bing) || !stringp(bing["name"]) || !intp(bing["chance"])) {
         debug_printf("Invalid data for zone (%s) %O\n", name, bing);
         hospital_log_file("COMPILE_ERROR", "Invalid data for zone (%s) %O\n", name,  bing);
      } else {
         info->zones[bing["name"]] = bing["chance"];
         chance += bing["chance"];
      }
   }
   info->zone_chance = chance;
   info->busy = data["busy"];
   bits = keys(data) - ({ "zone", "group", "npc", "name", "busy" });
   if (sizeof(bits)) {
      debug_printf("Unknown keys %s in zone %s\n", query_multiple_short(bits),
                   name);
      hospital_log_file("COMPILE_ERROR", "Unknown keys %s in %s\n",
                         query_multiple_short(bits), name);
   }
   _zone_info[name] = info;
   save_file();
}
private void parse_npc(string fname, mapping data) {
   string name;
   class npc_info info;
   string* bits;
   if (!data["name"]) {
      debug_printf("No name for npc %O\n", data);
      hospital_log_file("COMPILE_ERROR", "No name for npc %O\n", data);
      return 0;
   }
   name = data["name"];
   if (!data["path"]) {
      hospital_log_file("COMPILE_ERROR", "Required path field not present for npc %s\n", name);
      return 0;
   }
   if (file_size(npc_path(data["path"]) + ".c") < 0) {
      hospital_log_file("BAD_NPC_PATH", "Bad path for npc %s (%s)\n", name, data["path"]);
   }
   if (data["command"] && !arrayp(data["command"])) {
      data["command"] = ({ data["command"] });
   }
   if (data["move_zone"] && !arrayp(data["move_zone"])) {
      data["move_zone"] = ({ data["move_zone"] });
   }
   info = new(class npc_info, move_zones : ({ }), commands : ({ }));
   info->unique = data["unique"];
   info->path = data["path"];
   info->delay = data["delay"];
   info->max_population = data["population"];
   if(data["transient"])
     info->transient = 1;
   if(data["nocturnal"])
     info->nocturnal = 1;
   if(data["diurnal"])
     info->diurnal = 1;
   if(data["seasonal"]) {
     if(!arrayp(data["group"]))
       info->seasonal = ({ data["seasonal"] });
     else
       info->seasonal = data["seasonal"];
   }
   if (data["move_zone"]) {
      info->move_zones = data["move_zone"];
   }
   if (data["command"]) {
      info->commands = data["commands"];
   }
   bits = keys(data) - ({ "unique", "path", "move_zone", "population", "name", "delay", "transient", "nocturnal" });
   if (sizeof(bits)) {
      debug_printf("Unknown keys %s in npc %s\n", query_multiple_short(bits),
                   name);
      hospital_log_file("COMPILE_ERROR", "Unknown keys %s in npc %s\n",
                         query_multiple_short(bits), name);
   }
   if (_path_to_npc[info->path] && _path_to_npc[info->path] != name) {
      hospital_log_file("NPC_NAME_CLASH", "NPC path %s is used by %s and %s.\n",
                         info->path, name, _path_to_npc[info->path]);
   }
   _path_to_npc[info->path] = name;
   if (_npc_info[name]) {
      info->population = _npc_info[name]->population;
      info->no_created = _npc_info[name]->no_created;
      info->no_reused = _npc_info[name]->no_reused;
      info->no_deaths = _npc_info[name]->no_deaths;
   }
   _npc_info[name] = info;
   save_file();
}
private void parse_group(string fname, mapping data) {
   string name;
   class group_info info;
   mapping bing;
   int chance;
   string* bits;
   if (!data["name"]) {
      debug_printf("No name for group %O\n", data);
      hospital_log_file("COMPILE_ERROR", "No name for group %O\n", data);
      return 0;
   }
   name = data["name"];
   if (data["npc"] && !arrayp(data["npc"])) {
      data["npc"] = ({ data["npc"] });
   } else if (!arrayp(data["npc"])) {
      data["npc"] = ({ });
   }
   info = new(class group_info, npcs : ([ ]), move_zones : ({ }),
                                npc_commands : ([ ]));
   chance = 0;
   foreach (bing in data["npc"]) {
      if (!mapp(bing) || !stringp(bing["name"]) ||
          (!intp(bing["quantity"]) && !classp(bing["quantity"]))) {
         debug_printf("Invalid data for group (%s) %O\n", name, bing);
         hospital_log_file("COMPILE_ERROR", "Invalid data for group (%s) %O\n", name,  bing);
      } else {
         info->npcs[bing["name"]] = bing["quantity"];
         if (bing["command"]) {
            if (arrayp(bing["command"])) {
               info->npc_commands[bing["name"]] = bing["command"];
            } else {
               info->npc_commands[bing["name"]] = ({ bing["command"] });
            }
         }
      }
   }
   if (data["move_zone"]) {
      info->move_zones = data["move_zone"];
   }
   info->max_population = data["population"];
   info->protect = data["protect"];
   info->defend = data["defend"];
   info->transient = data["transient"];
   bits = keys(data) - ({ "npc", "name", "population", "move_zone", "protect", "defend", "transient", });
   if (sizeof(bits)) {
      debug_printf("Unknown keys %s in group %s\n", query_multiple_short(bits),
                   name);
      hospital_log_file("COMPILE_ERROR", "Unknown keys %s in group %s\n",
                         query_multiple_short(bits), name);
   }
   if (_group_info[name]) {
     info->storage = _group_info[name]->storage;
   }
   _group_info[name] = info;
}
protected void finish_compiling(string fname, mapping data) {
   mixed* bits;
   mapping thing;
   string name;
   foreach (name, bits in data) {
      switch (name) {
      case "zone" :
         foreach (thing in bits) {
            parse_zone(fname, thing);
         }
         break;
      case "npc" :
         foreach (thing in bits) {
            parse_npc(fname, thing);
         }
         break;
      case "group" :
         foreach (thing in bits) {
            parse_group(fname, thing);
         }
         break;
      default :
         debug_printf("Unknown data area %s in %s\n", name, fname);
         hospital_log_file("COMPILE_ERROR", "Unknown data area %s in %s\n", name, fname);
         break;
      }
   }
   _file_modified_time[fname] = unguarded( (: stat($(fname)) :))[1];
   save_file();
}
int scan_for_new_data(int force) {
  string *files;
  string fname;
  string *bits;
  debug_printf("Scan for new data.");
  if (unguarded( (: stat(__FILE__)[1] :)) !=
      _file_modified_time[__FILE__]) {
    _file_modified_time = ([ ]);
  }
  if(force) {
    _npc_info = ([ ]);
    _zone_info = ([ ]);
    _group_info = ([ ]);
  }
  files = ({ _data_directory });
  while (sizeof(files)) {
    fname = files[0];
    files = files[1..];
    if (unguarded( (: file_size($(fname)) :)) == -2) {
      bits = get_dir(fname + "/");
      if (bits) {
        bits -= ({ "RCS", ".", ".." });
        bits = filter(bits, (: $1[0] != '.' :));
        files += map(bits, (: $2 + "/" + $1 :), fname);
      }
    } else {
      if(unguarded((: stat($(fname)) :))[1] != _file_modified_time[fname] ||
         force) {
        debug_printf("Compiling %s", fname);
        DATA_HANDLER->compile_file(fname, (: finish_compiling :));
      }
    }
  }
  _file_modified_time[__FILE__] = unguarded( (: stat(__FILE__)[1] :));
  return 1;
}
int roll_dice(mixed die) {
   int result;
   int i;
   if (intp(die)) {
      return die;
   }
   if (classp(die)) {
      for (i = 0; i < die->number; i++) {
         result += random(die->die) + 1;
      }
      result += die->modifier;
      return result;
   }
   return 0;
}
int query_npc_max_population( string npc) {
   if (!_npc_info[npc]) {
      return -1;
   }
   return ((class npc_info)_npc_info[npc])->max_population;
}
int query_npc_current_population( string npc, int clean) {
   class npc_info data;
   if (!_npc_info[npc]) {
      return -1;
   }
   data = _npc_info[npc];
   if (!data->population) {
      data->population = children(npc_path(data->path));
      data->next_update = time() + POPULATION_UPDATE_TIME;
   }
   if (clean || data->next_update < time()) {
      data->population = filter(data->population, (: objectp($1) :));
      data->next_update = time() + POPULATION_UPDATE_TIME;
   }
   return sizeof(data->population);
}
int is_npc_under_max_population(string name) {
    class npc_info info;
    info = _npc_info[name];
    if (!info) {
       return 0;
    }
    if(info->transient)
      return 1;
    if (info->max_population) {
       return query_npc_current_population(name, 1) < info->max_population;
    }
    return 1;
}
int is_group_under_max_population(string name) {
    class group_info group;
    group = _group_info[name];
    if (!group) {
       return 0;
    }
    if (!group->max_population || group->transient) {
       return 1;
    }
    if (!group->storage) {
        group->storage = ({ });
    } else if (group->next_update < time()) {
        group->storage = map(group->storage, (: filter($1, (: objectp($1) :)) :));
        group->storage = filter(group->storage, (: sizeof($1) :));
        group->next_update = time() + POPULATION_UPDATE_TIME;
    }
    if (sizeof(group->storage) >= group->max_population) {
        return 0;
    }
    return 1;
}
public object load_npc_object(string npc_name) {
    class npc_info info;
    object npc;
    string zone;
    string cmd;
    if ( undefinedp(_npc_info[npc_name])) {
        debug_printf("Unable to find npc %O", npc_name);
        return 0;
    }
    info = _npc_info[npc_name];
    if(info->diurnal && !WEATHER->query_day(previous_object()))
      return 0;
    if(info->nocturnal && !WEATHER->query_day(previous_object()))
      return 0;
    if(info->seasonal &&
       member_array(WEATHER->query_season(), info->seasonal) == -1)
      return 0;
    if (stringp(info->path)) {
        if ( info->unique ) {
            npc = find_object( npc_path(info->path) );
            if ((!npc || !environment(npc)) && make_unique(npc_name)) {
               debug_printf("Unique npc %O", info);
               if (catch(npc = load_object( npc_path(info->path) ))) {
                   hospital_log_file("BAD_NPC_PATH", "Error loading %s (%s)\n", npc_name, info->path);
                   return 0;
               }
               if (!objectp(npc) || npc == 0) {
                   hospital_log_file("BAD_NPC_PATH", "Failed to load %s (%s)\n", npc_name, info->path);
                   return 0;
               }
               if ( environment( npc ) ) {
                   debug_printf("NPC unique and already exists %O", npc_name);
                   return 0;
               }
            }
        } else if(info->transient) {
          if(!_cache_inventory)
            _cache_inventory = ([ ]);
          else if(_cache_inventory[npc_name])
            _cache_inventory[npc_name] -= ({ 0 });
          if(sizeof(_cache_inventory[npc_name])) {
            npc = _cache_inventory[npc_name][0];
            _cache_inventory[npc_name] -= ({ npc });
            info->no_reused++;
          } else {
            npc = clone_object( npc_path(info->path) );
            if(npc) {
              npc->add_property("transient", 1);
              npc->add_property("npc_id", npc_name);
              npc->add_property("hospital", base_name(this_object()));
              info->no_created++;
            } else
              debug_printf("Failed to clone %s", npc_path(info->path));
          }
        } else {
            if (is_npc_under_max_population(npc_name)) {
               npc = clone_object( npc_path(info->path) );
               info->no_created++;
               if (!npc) {
                  debug_printf("Npc path does not exist %O (%O)", npc, npc_path(info->path));
               }
            } else {
               debug_printf("NPC over max population %O", npc_name);
            }
        }
    } else {
        debug_printf("Broken npc data %O", info->path);
        return 0;
    }
    if (npc && !info->transient) {
        if( info->population == 0 )
            info->population = ({ });
        info->population += ({ npc });
        npc->add_property("npc_id", npc_name);
        foreach (zone in info->move_zones) {
            npc->add_move_zone(zone);
        }
        foreach (cmd in info->commands) {
            npc->init_command(cmd, 2);
        }
    }
    return npc;
}
public object *load_group_npcs(string group_name) {
    class group_info group;
    int quantity;
    int i;
    object *npcs;
    string npc_name;
    object ob;
    object ob_bing;
    string cmd;
    if ( undefinedp(_group_info[group_name]) ||
         !is_group_under_max_population(group_name)) {
        return 0;
    }
    group = _group_info[group_name];
    npcs = ({ });
    foreach (npc_name, quantity in group->npcs) {
        quantity = roll_dice(quantity);
        for (i = 0; i < quantity; i++) {
            ob = load_npc_object(npc_name);
            if (!ob) {
               npcs->move("/room/rubbish");
               return ({ });
            }
            npcs += ({ ob });
            if (group->npc_commands[npc_name]) {
               foreach (cmd in group->npc_commands[npc_name]) {
                  ob->init_command(cmd, 2);
               }
            }
        }
    }
    if (!group->storage) {
        group->storage = ({ });
    }
    group->storage += ({ npcs });
    npcs->add_property("group_id", group_name);
    foreach (ob in npcs) {
       foreach (ob_bing in npcs) {
          if (ob != ob_bing) {
             ob->add_follower(ob_bing);
             if (group->defend) {
               ob->add_defender(ob_bing);
             }
             if (group->protect) {
                ob->add_protector(ob_bing);
             }
          }
       }
    }
    return npcs;
}
public class npc_info query_npc_info( string npc ) {
    if ( !_npc_info ) {
        return 0;
    }
    return _npc_info[ npc ];
}
mapping query_debug_npc_info() {
   return _npc_info;
}
public class group_info query_group_info( string group ) {
    if ( !_group_info ) {
        return 0;
    }
    return _group_info[ group ];
}
void npc_died(object ob) {
   string npc_id;
   class npc_info info;
   int i;
   mixed* stuff;
   npc_id = ob->query_property("npc_id");
   info = _npc_info[npc_id];
   if (!info || !npc_id) {
      return ;
   }
   info->population -= ({ ob });
   info->no_deaths++;
   npc_id = ob->query_property("group_id");
   stuff = _group_info[npc_id]->storage;
   if (sizeof(stuff)) {
      for (i = 0; i < sizeof(stuff); i++) {
         stuff[i] -= ({ ob, 0 });
      }
      _group_info[npc_id]->storage = filter(_group_info[npc_id]->storage,
                                             (: sizeof($1) :));
   }
}
mapping query_all_npc_info() {
   return _npc_info;
}
mapping query_all_group_info() {
   return _group_info;
}
mapping query_all_zone_info() {
   return _zone_info;
}
private int count_chances_in_zone(string zone) {
    class zone_info info;
    int chance;
    info = _zone_info[zone];
    if (!zone) {
       return 0;
    }
    chance = info->npc_chance + info->group_chance + info->zone_chance;
    return chance;
}
private object* create_npcs_in_zone(string zone, int pos) {
    class zone_info info;
    string extra;
    string npc;
    object ob;
    object* obs;
    int chance;
    info = _zone_info[zone];
    if (!zone) {
       return ({ });
    }
    if (pos < info->npc_chance) {
       foreach (npc, chance in info->npcs) {
          if (pos < chance) {
             ob = load_npc_object(npc);
             if (ob) {
               if(environment(ob) == this_object())
                 debug_printf("Reused %s in %s", npc, zone);
               else
                 debug_printf("Created %s in %s", npc, zone);
                return ({ ob });
             }
          }
          pos -= chance;
       }
    }
    pos -= info->npc_chance;
    if (pos < info->group_chance) {
       foreach (npc, chance in info->groups) {
          if (pos < chance) {
             obs = load_group_npcs(npc);
             if (sizeof(obs)) {
                return obs;
             }
          }
          pos -= chance;
       }
    }
    pos -= info->group_chance;
    foreach (extra, chance in info->zones) {
        if (pos < chance) {
           return load_random_npc(extra, -1, -1);
        }
    }
    return ({ });
}
public object *load_random_npc(string zone, int wealth, int busy) {
    int chance;
    int pos;
    if (_disable_npc_generation) {
        return ({ });
    }
    if (_zone_info[zone + "-w" + wealth + "-b" + busy]) {
       zone = zone + "-w" + wealth + "-b" + busy;
    } else if (_zone_info[zone + "-w" + wealth]) {
       zone = zone + "-w" + wealth;
    } else if (_zone_info[zone + "-b" + busy]) {
       zone = zone + "-b" + busy;
    }
    if (!_zone_info[zone]) {
        return ({ });
    }
    if(_zone_info[zone]->busy &&
       _zone_info[zone]->busy < random(random(100)))
      return ({ });
    chance = count_chances_in_zone(zone);
    if (!chance) {
       return ({ });
    }
    pos = random(chance);
    return create_npcs_in_zone(zone, pos);
}
int do_report() {
    string name;
    class group_info group;
    class npc_info npc;
    string txt;
    int total;
    int max;
    int pop;
    txt = "";
    total = 0;
    txt += "%^WHITE%^NPCs%^RESET%^\n";
    foreach( name, npc in _npc_info ) {
      reset_eval_cost();
      if(stringp(npc->path) && file_size(npc_path(npc->path) + ".c") > 0) {
        pop = query_npc_current_population(name, 0);
      } else {
        pop = 0;
      }
      if(npc->transient)
        txt += sprintf( "$I$5=Name: %s. (%s) (Transient) Reused %d Created %d Died %d\n", name + "",
                        (stringp(npc->path)?npc->path:"Broken!"),
                        npc->no_reused, npc->no_created, npc->no_deaths);
      else
        txt += sprintf( "$I$5=Name: %s. (%s) Population: (%d/%d) Created %d Died %d\n", name + "",
                        (stringp(npc->path)?npc->path:"Broken!"),
            pop, npc->max_population, npc->no_created, npc->no_deaths );
        total += pop;
        max += npc->max_population;
    }
    txt += "$I$0=%^WHITE%^Groups%^RESET%^\n";
    foreach( name, group in _group_info ) {
      if(group->transient)
        txt += sprintf( "$I$5=Name: %s. (%s) (Transient)\n", name,
            query_multiple_short(keys(group->npcs)));
      else
        txt += sprintf( "$I$5=Name: %s. (%s) Population: (%d/%d)\n", name,
            query_multiple_short(keys(group->npcs)),
            sizeof( group->storage ), group->max_population );
    }
    txt += "$I$0=%^WHITE%^Cache%^RESET%^\n";
    foreach(name in keys(_cache_inventory))
      _cache_inventory[name] -= ({ 0 });
    foreach(name, group in _cache_inventory)
      txt += sprintf("$I$5=Name: %s %d\n", name, sizeof(group));
    txt += "\nTotal NPCs in hospital: " + total + "/" +
            max + ".\n";
    write("$P$Report$P$" + txt );
    return 1;
}
void init() {
  object ob;
  ob = this_player();
  add_command("report", "", (: do_report :));
  add_command("scan", "", (: scan_for_new_data :));
  if(ob->query_property("npc_id") && ob->query_property("hospital") &&
     ob->query_property("hospital") == base_name(this_object())) {
    if(!_cache_inventory[ob->query_property("npc_id")])
      _cache_inventory[ob->query_property("npc_id")] = ({ ob });
    else if(sizeof(_cache_inventory[ob->query_property("npc_id")]) >
            _max_cache)
      ob->move("/room/rubbish");
    else
      _cache_inventory[ob->query_property("npc_id")] += ({ ob });
  } else if(base_name(ob) == "/obj/corpse")
    ob->move("/room/rubbish");
}
int no_attack() { return 1; }
mapping query_dynamic_auto_load() {
    string group_name;
    string npc;
    class group_info data;
    class npc_info npc_data;
    mapping tmp;
    mapping tmp2;
    tmp = allocate_mapping( sizeof( _group_info ) );
    foreach( group_name, data in _group_info ) {
        tmp[ group_name ] = data->storage;
    }
    tmp2 = allocate_mapping( sizeof( _npc_info) );
    foreach( npc, npc_data in _npc_info ) {
        tmp2[ npc ] = npc_data->population;
    }
    return ([ file_name( this_object() ) : tmp, "npcs" : tmp2 ]);
}
void init_dynamic_arg( mapping tmp ) {
    string group_name;
    object *npcs;
    if ( tmp[ file_name( this_object() ) ] ) {
        foreach( group_name, npcs in tmp[ file_name( this_object() ) ] ) {
            if (_group_info[group_name]) {
               _group_info[ group_name ]->storage = npcs;
            }
        }
        foreach( group_name, npcs in tmp[ "npcs" ]) {
            if (_npc_info[group_name]) {
               _npc_info[ group_name ]->population = npcs;
            }
        }
    }
}
mixed query_all_npcs() {
    return values( map( _group_info, (: $2->storage :) ) );
}
mapping query_inventory_cache() {
  return copy(_cache_inventory);
}
string* query_registered_npcs() {
    return keys( _npc_info );
}