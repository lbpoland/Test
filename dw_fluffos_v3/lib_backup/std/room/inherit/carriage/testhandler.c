#include <room.h>
#include <data.h>
#include <room/carriage.h>
#define CARRIAGE ITEMS "carriage"
private mapping _routedetails = ([ ]);
private mapping _routesactual = ([ ]);
private nosave mapping _carriages = ([ ]);
private nosave string _base_dir;
private nosave string _carriage;
private nosave string _pole;
private nosave string _data_dir;
private nosave string _save_file;
private mapping _file_modified_time;
private void load_data();
private void map_carriages();
private void save_file() {
   unguarded((: save_object(_save_file) :));
}
void create() {
   seteuid(getuid());
   _file_modified_time = ([ ]);
   this_object()->setup();
}
void setup_carriage(string dir, string base_dir,
                    string carriage, string pole, string save_file) {
   _data_dir = dir;
   _base_dir = base_dir;
   _carriage = carriage;
   _pole = pole;
   _save_file = save_file;
   unguarded((: restore_object(_save_file) :));
   if (!_file_modified_time) {
      _file_modified_time = ([ ]);
   }
   load_data();
   map_carriages();
}
mapping query_route_details() { return _routedetails; }
mapping query_route_actual() { return _routesactual; }
string* query_route_names() { return keys(_routesactual); }
string query_stop_location(string name) {
   if (_routedetails[name]) {
     return _routedetails[name]->path;
   }
   return "bad stop " + name;
}
string query_stop_name(string name) {
   if (_routedetails[name]) {
      return _routedetails[name]->name;
   }
   return "Broken Position " + name;
}
int query_stop_delay(string name) {
   if (_routedetails[name]) {
      return _routedetails[name]->delay;
   }
   return 60;
}
class stop_list_details* query_route_stops(string route) {
   return _routesactual[route]->stops;
}
object query_carriage_on_route(string route) {
   return _carriages[route];
}
private void parse_stop(string fname, mapping data) {
   string name;
   class stop_details info;
   if (!data["id"]) {
      debug_printf("No id for stop %O\n", data);
      log_file("COMPILE_ERROR", "No name for npc %O\n", data);
      return 0;
   }
   if (!data["name"]) {
      debug_printf("No name for stop %O\n", data);
      log_file("COMPILE_ERROR", "No name for npc %O\n", data);
      return 0;
   }
   name = data["name"];
   if (!data["path"]) {
      log_file("COMPILE_ERROR", "Required path field not present for stop %s\n", name);
      return 0;
   }
   info = new(class stop_details);
   info->name = data["name"];
   if (data["path"][0] == '/') {
      info->path = data["path"];
   } else {
      info->path = _base_dir + data["path"];
   }
   info->delay = data["delay"];
   _routedetails[data["id"]] = info;
   save_file();
}
private void parse_route(string fname, mapping data) {
   string name;
   class route_details info;
   mixed bing;
   if (!data["name"]) {
      debug_printf("No id for route %O\n", data);
      log_file("COMPILE_ERROR", "No name for npc %O\n", data);
      return 0;
   }
   if (!data["colour"]) {
      debug_printf("No colour for route %O\n", data);
      log_file("COMPILE_ERROR", "No name for stop %O\n", data);
      return 0;
   }
   name = data["name"];
   info = new(class route_details, stops : ({ }));
   info->colour = data["colour"];
   info->return_along = data["samereturnpath"];
   foreach (bing in data["stop"]) {
      if (!mapp(bing) || !stringp(bing["id"]) || !intp(bing["travel"])) {
         debug_printf("Invalid data for zone (%s) %O\n", name, bing);
         log_file("COMPILE_ERROR", "Invalid data for route (%s) %O\n", name,  bing);
      } else {
         info->stops += ({ new(class stop_list_details, id : bing["id"],
                                             travel_time : bing["travel"]) });
      }
   }
   _routesactual[data["name"]] = info;
   save_file();
}
protected void finish_compiling(string fname, mapping data) {
   mixed* bits;
   mapping thing;
   string name;
   foreach (name, bits in data) {
      switch (name) {
      case "stop" :
         foreach (thing in bits) {
            parse_stop(fname, thing);
         }
         break;
      case "route" :
         foreach (thing in bits) {
            parse_route(fname, thing);
         }
         break;
      default :
         debug_printf("Unknown data area %s in %s\n", name, fname);
         log_file("COMPILE_ERROR", "Unknown data area %s in %s\n", name, fname);
         break;
      }
   }
   _file_modified_time[fname] = unguarded( (: stat($(fname)) :))[1];
   save_file();
   map_carriages();
}
void scan_for_new_data() {
   string *files;
   string fname;
   string *bits;
   debug_printf("Scan for new data.");
   if (unguarded( (: stat(__FILE__)[1] :)) !=
       _file_modified_time[__FILE__]) {
      _file_modified_time = ([ ]);
   }
   files = ({ _data_dir });
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
         if (unguarded( (: stat($(fname)) :))[1] != _file_modified_time[fname]) {
            debug_printf("Compiling: %s", fname);
            DATA_HANDLER->compile_file(fname,
                     (: finish_compiling :));
         }
      }
   }
   _file_modified_time[__FILE__] =
                unguarded( (: stat(__FILE__)[1] :));
}
private string trim(string str) {
   while (strlen(str) && str[0] == ' ') {
      str = str[1..];
   }
   while (strlen(str) && str[<1] == ' ') {
      str = str[0..<2];
   }
   return str;
}
void load_data() {
   scan_for_new_data();
}
private void map_carriages() {
  string route;
  int i, j;
  class route_details rods;
  class route_details new_rods;
  string *locshorts;
  object carriage;
  object car;
  object room;
  object pole;
  class stop_list_details loc;
  string str;
  foreach( route, rods in _routesactual) {
    carriage = 0;
    if (!_carriages[route]) {
      foreach( car in children( _carriage ) ) {
        if (clonep(car) && car->query_carriage_name() == route) {
          carriage = car;
          break;
        }
      }
    } else {
      carriage = _carriages[route];
    }
    locshorts = ({ });
    foreach (loc in rods->stops) {
       str = query_stop_name(loc->id);
       if (str) {
          locshorts += ({ str });
       }
    }
    j = 0;
    foreach (loc in rods->stops) {
      str = query_stop_location(loc->id);
      room = load_object(str);
      if(objectp(room)) {
        if( room->query_property("test pole")) {
          pole = room->query_property("test pole");
        } else {
          pole = clone_object(_pole);
          if(objectp(pole)) {
            pole->move(room);
            room->add_property(ROOM_KEEP_PROP);
          }
        }
        if(objectp(pole)) {
          pole->setup_route(
                  locshorts[(j+1)..] + locshorts[0..j],
                  _routesactual[route]->colour,
                  route);
        }
      j++;
      }
    }
    if (rods->return_along) {
       new_rods = copy(rods);
       for (i = sizeof(rods->stops) - 2; i >= 1; i--) {
          new_rods->stops += ({ rods->stops[i] });
       }
    } else {
       new_rods = rods;
    }
    if (!carriage) {
      carriage = clone_object( _carriage );
      carriage->make_carriage( route, new_rods, this_object() );
      carriage->setup();
    } else {
      carriage->update_route( route, new_rods, this_object() );
      carriage->setup();
    }
    if(objectp(carriage)) {
      _carriages[route] = carriage;
    }
  }
}
mixed* stats() {
   mixed* ret;
   string route;
   object ob;
   ret = ({ });
   foreach (route in query_route_names()) {
      ob = query_carriage_on_route(route);
      if (ob) {
         ret += ({ ({ route + "-carriage", file_name(ob) })  });
      }
      ret += ({ ({ route + "-colour", _routesactual[route]->colour }) });
      ret += ({ ({ route + "-current stop", ob->query_current_stop()->name })  });
      ret += ({ ({ route + "-next stop", ob->query_next_stop()->name })  });
      if (ob && ob->query_outside()) {
         ret += ({ ({ route + "-outside", file_name(ob->query_outside()) }) });
      }
   }
   return ret;
}