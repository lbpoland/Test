#include <clothing.h>
mapping _types;
mapping _equivilants;
mapping _zones;
string *_zone_level;
protected void add_clothing_type(string name,
                                 string *not_remove,
                                 string *hiding);
protected void add_clothing_zone(string zone, string *types);
private int fixup_types(string type, string *types);
protected void add_equivilant_type(string name, string equiv);
private void check_clothing_types();
string *query_clothing_zone(string zone);
string *query_clothing_cannot_remove(string type);
string can_wear_or_remove(object thing, object player);
void create() {
   _types = ([ ]);
   _equivilants = ([ ]);
   _zones = ([ ]);
   _zone_level = ({ });
   add_clothing_type("bandaid", ({ }), ({ }));
   add_clothing_type("wig",
       ({ "hood", "helmet", "coif", "hat", "all covering" }),
       ({ "hood", "helmet", "coif", "hat", "all covering" }));
   add_clothing_type("hat",
       ({ "hood", "helmet", "all covering" }),
       ({ "hood", "helmet", "all covering" }));
   add_clothing_type("helmet",
       ({ "hood", "all covering" }),
       ({ "hood", "all covering" }));
   add_clothing_type("hood",
       ({ "all covering" }),
       ({ "all covering" }));
   add_clothing_type("earring",
       ({ "coif", "all covering" }),
       ({ "hood", "coif", "all covering" }));
   add_clothing_type("moustache",
       ({ "coif", "mask", "all covering" }),
       ({ "coif", "mask", "all covering" }));
   add_clothing_type("glasses",
       ({ "all covering" }),
       ({ "all covering" }));
   add_clothing_type("nosering",
       ({ "mask", "coif", "all covering" }),
       ({ "mask", "coif", "all covering" }));
   add_clothing_type("mask",
       ({ "all covering" }),
       ({ "all covering" }));
   add_clothing_type("headband",
       ({ "hat", "hood", "helmet", "coif", "all covering" }),
       ({ "hat", "hood", "helmet", "coif", "all covering" }));
   add_clothing_type("scarf",
       ({ "hood", "all covering" }),
       ({ "hood", "all covering"}));
   add_clothing_type("necklace",
       ({ "coif", "all covering" }),
       ({ "cloak", "coif", "all covering" }));
   add_clothing_type("collar",
       ({ "hood", "all covering" }),
       ({ "hood", "all covering"}));
   add_clothing_type( "shoulder",
       ({ "cloak", "cape", "sash", "robe",  "tabard", "breastplate",
          "hauberk", "haubergon", "byrnie", "jacket","jumper", "waistcoat",
          "shirt", "undershirt", "all covering" }),
       ({ "cloak", "robe", "tabard", "breastplate", "hauberk", "haubergon",
          "byrnie", "jacket", "jumper", "waistcoat", "shirt", "undershirt",
          "all covering" }));
   add_clothing_type( "bra",
       ({ "cloak", "cape", "sash", "robe",  "tabard", "breastplate",
          "hauberk", "haubergon", "byrnie", "jacket","jumper", "waistcoat",
          "shirt", "undershirt", "all covering", "long dress", "mini dress" }),
       ({ "cloak", "robe", "tabard", "breastplate", "hauberk", "haubergon",
           "byrnie", "jacket", "jumper", "waistcoat", "shirt", "undershirt",
           "all covering", "long dress", "mini dress" }));
   add_clothing_type("undershirt",
       ({ "cloak", "cape", "sash", "robe", "tabard", "breastplate",
          "haubergon", "hauberk", "byrnie", "jacket", "jumper", "waistcoat",
          "shirt", "harness", "all covering" }),
       ({ "cloak", "robe", "tabard", "breastplate", "haubergon", "hauberk",
          "byrnie", "jacket", "jumper", "shirt", "long dress", "mini dress",
          "all covering" }));
   add_clothing_type("shirt",
       ({ "cloak", "cape", "sash", "robe", "tabard", "breastplate",
          "haubergon", "hauberk", "byrnie", "jacket",  "jumper", "waistcoat",
          "harness", "all covering" }),
       ({ "cloak", "robe", "haubergon", "hauberk", "byrnie", "jacket",
          "jumper", "all covering" }));
   add_clothing_type("waistcoat",
       ({ "cloak", "cape", "sash", "robe", "tabard", "breastplate",
          "haubergon", "hauberk", "byrnie", "jacket", "jumper", "harness",
          "all covering" }),
       ({ "cloak", "robe", "haubergon", "hauberk", "byrnie", "jacket",
          "jumper", "all covering" }));
   add_clothing_type("harness",
       ({ "all covering" }),
       ({ "cloak", "all covering" }));
   add_clothing_type("jumper",
       ({ "cloak", "cape", "sash", "robe", "breastplate", "haubergon",
          "hauberk", "byrnie", "tabard", "jacket",  "all covering" }),
       ({ "cloak", "robe", "haubergon", "hauberk", "jacket",
          "all covering" }));
   add_clothing_type("jacket",
       ({ "cloak", "cape", "sash", "robe", "tabard", "breastplate",
          "haubergon", "hauberk", "byrnie", "all covering" }),
       ({ "cloak", "robe", "hauberk", "all covering" }));
   add_clothing_type("tabard",
       ({ "cloak", "cape", "sash", "robe", "all covering" }),
       ({ "cloak", "robe", "all covering" }));
   add_clothing_type("robe",
       ({ "cloak", "cape", "sash", "all covering" }),
       ({ "cloak", "all covering" }));
   add_clothing_type("cloak",
       ({ "all covering" }),
       ({ "all covering" }));
   add_clothing_type("sash",
       ({ "cloak", "cape", "all covering" }),
       ({ "cloak", "all covering" }));
   add_clothing_type("cape",
       ({ "all covering" }),
       ({ "all covering" }));
   add_clothing_type("armband",
       ({ "all covering" }),
       ({ "cloak", "robe", "all covering" }));
   add_clothing_type("glove",
       ({ "all covering" }),
       ({ "all covering" }));
   add_clothing_type("bracelet",
       ({ "glove", "all covering" }),
       ({ "cloak", "glove", "all covering" }));
   add_clothing_type("ring",
       ({ "glove", "all covering" }),
       ({ "glove", "all covering" }));
   add_clothing_type("box",
       ({ "cloak", "robe", "all covering" }),
       ({ "cloak", "robe", "skirt", "all covering" }));
   add_clothing_type("apron",
       ({ "cloak", "all covering" }),
       ({ "cloak", "all covering" }));
   add_clothing_type("underwear",
       ({ "harness", "trousers", "greave", "hauberk", "haubergon",
          "byrnie", "belt", "trousers", "all covering" }),
       ({ "cloak", "robe", "skirt", "trousers", "all covering",
          "long dress", "mini dress" }));
   add_clothing_type("garter",
       ({ "greave", "hauberk", "trousers", "all covering"}),
       ({ "cloak", "robe", "greave", "hauberk", "trousers", "skirt",
          "all covering", "long dress", "mini dress"}));
   add_clothing_type("skirt",
       ({ "belt", "all covering" }),
       ({ "cloak", "robe", "all covering" }));
   add_clothing_type("trousers",
       ({ "greave", "hauberk", "belt" }),
       ({ "cloak", "hauberk", "robe", "all covering" }));
   add_clothing_type("belt",
       ({"hauberk", "haubergon", "byrnie", "all covering" }),
       ({ "cloak", "robe", "hauberk", "haubergon", "byrnie", "all covering" }));
   add_clothing_type("sock",
       ({ "overshoe", "boot", "chausse", "all covering" }),
       ({ "cloak", "overshoe", "boot", "chausse", "all covering",
          "long dress", "trousers" }));
   add_clothing_type("anklet",
       ({ }),
       ({ "cloak", "overshoe", "chausse", "all covering" }));
   add_clothing_type("boot",
       ({ "overshoe" }),
       ({ "overshoe", "all covering" }));
   add_clothing_type("overshoe",
       ({ }),
       ({ "all covering" }));
   add_clothing_type("long dress",
       ({ "cloak", "cape", "sash", "robe", "tabard", "breastplate",
          "haubergon", "hauberk", "byrnie", "jacket",  "jumper", "harness",
          "all covering","belt" }),
       ({ "cloak", "robe", "haubergon", "hauberk", "byrnie", "jacket",
          "jumper", "all covering" }));
   add_clothing_type("mini dress",
       ({ "cloak", "cape", "sash", "robe", "tabard", "breastplate",
          "haubergon", "hauberk", "byrnie", "jacket",  "jumper", "harness",
          "all covering","belt" }),
       ({ "cloak", "robe", "haubergon", "hauberk", "byrnie", "jacket",
          "jumper", "all covering" }));
   add_clothing_type("small shield",
       ({"all covering" }),
       ({ "all covering" }));
   add_clothing_type("shield",
       ({"all covering" }),
       ({ "all covering" }));
   add_clothing_type("large shield",
       ({"all covering" }),
       ({ "all covering" }));
   add_clothing_type("badge",
       ({ "all covering" }),
       ({ "cloak", "all covering" }));
   add_clothing_type("scabbard",
       ({ "all covering" }),
       ({ "cloak", "all covering" }));
   add_clothing_type("small scabbard",
       ({ "all covering" }),
       ({ "cloak", "robe", "all covering" }));
   add_clothing_type("belt scabbard",
       ({ "all covering" }),
       ({ "cloak", "robe", "all covering" }));
   add_clothing_type("coif",
       ({ "hood", "scarf", "mask", "helmet", "hat", "all covering"}),
       ({ "hood", "all covering"}));
   add_clothing_type("byrnie",
       ({ "cloak", "breastplate", "backplate", "tabard", "small scabbard",
          "belt scabbard", "robe", "cape", "sash", "all covering" }),
       ({ "cloak", "robe", "all covering" }));
   add_clothing_type("haubergon",
       ({ "cloak", "breastplate", "backplate", "tabard", "vambrace",
          "small scabbard", "belt scabbard", "robe", "cape", "sash",
          "all covering"}),
       ({ "cloak", "robe", "all covering"}));
   add_clothing_type("hauberk",
       ({ "cloak", "tabard", "vambrace", "greave", "breastplate", "backplate",
          "small scabbard", "belt scabbard", "robe", "cape", "sash",
          "all covering"}),
       ({ "cloak", "robe", "all covering" }));
   add_clothing_type("chausse",
       ({ "boot", "overshoe", "all covering"}),
       ({ "boot", "overshoe", "all covering"}));
   add_clothing_type("breastplate",
       ({ "cloak", "small scabbard", "belt scabbard", "robe", "tabard",
          "cape", "sash", "all covering" }),
       ({ "cloak", "robe", "all covering" }));
   add_clothing_type("backplate",
       ({ "cloak", "cape", "sash", "robe", "tabard", "all covering"}),
       ({ "cloak", "cape", "sash", "robe", "all covering"}));
   add_clothing_type("vambrace",
       ({ "glove", "all covering" }),
       ({ "cloak", "robe", "all covering" }));
   add_clothing_type("greave",
       ({ "all covering" }),
       ({ "cloak", "robe", "all covering" }));
   add_clothing_type("all covering", ({}), ({}));
   add_clothing_zone("head",
       ({ "hood", "helmet", "coif", "hat", "wig", "headband", "moustache",
          "glasses", "mask" }));
   add_clothing_zone("neck",
       ({ "cloak", "hood", "coif", "cape", "scarf", "collar" }));
   add_clothing_zone("chest",
       ({ "cloak", "sash", "robe", "breastplate", "haubergon", "hauberk",
          "byrnie", "tabard", "jacket","jumper", "shirt", "undershirt",
          "shoulder", "bra","shield", "large shield", "long dress",
          "mini dress", "apron", "waistcoat" }));
   add_clothing_zone("back",
       ({ "cloak", "cape", "sash", "robe", "hauberk", "haubergon", "byrnie",
          "jacket", "jumper", "shirt", "undershirt", "backplate",
          "long dress", "mini dress", "waistcoat" }));
   add_clothing_zone("abdomen",
       ({ "large shield", "robe", "breastplate", "byrnie", "hauberk",
          "skirt", "box", "trousers", "underwear", "long dress",
          "mini dress", "apron", "waistcoat" }));
   add_clothing_zone("arms",
       ({ "cloak", "small shield", "shield", "large shield", "robe",
          "vambrace", "hauberk", "haubergon", "jacket", "armband",
          "jumper", "shirt", "long dress" }));
   add_clothing_zone("hands",
       ({ "glove", "small shield", "shield", "large shield" }));
   add_clothing_zone("legs",
       ({ "cloak", "robe", "greave", "hauberk", "skirt", "trousers",
          "long dress" }));
   add_clothing_zone("feet",
       ({ "overshoe", "boot", "chausse", "sock", "anklet" }));
   add_equivilant_type("shoe", "boot");
   add_equivilant_type("sandal", "boot");
   add_equivilant_type("clog", "boot");
   add_equivilant_type("sabaton", "boot");
   add_equivilant_type("turban", "helmet");
   add_equivilant_type("gorget", "collar");
   add_equivilant_type("stocking", "sock");
   add_equivilant_type("coat", "cloak");
   add_equivilant_type("overall", "long dress");
   call_out((: check_clothing_types() :), 2);
}
object* query_items_blocking(object thing, object player) {
   int i;
   int j;
   int k;
   string *stuff;
   object *blocking;
   mixed junk;
   mixed main_types;
   object *wearing;
   main_types = thing->query_type();
   if (stringp(main_types)) {
      main_types = ({ main_types });
   }
   wearing = player->query_wearing() - ({ thing });
   blocking = ({ });
   for (k=0;k<sizeof(main_types);k++) {
      stuff = query_clothing_cannot_remove(main_types[k]);
      if (!sizeof(wearing) || !stuff) {
         return ({ });
      }
      for (i = 0; i < sizeof(wearing); i++) {
         junk = wearing[i]->query_type();
         if (stringp(junk)) {
            junk = ({ junk });
         }
         for (j = 0; j < sizeof(junk); j++) {
            if (member_array(junk[j], stuff) != -1 &&
                 member_array(wearing[i], blocking) == -1) {
               blocking += ({ wearing[i] });
               break;
            }
         }
      }
   }
   return blocking;
}
string can_wear_or_remove( object thing, object player ) {
   object *blocking;
   blocking = query_items_blocking(thing, player);
   if (sizeof(blocking)) {
     return "when you are wearing "+ query_multiple_short(blocking);
   }
   return 0;
}
protected void add_clothing_type(string name,
                                 string *not_remove,
                                 string *hiding) {
   _types[name] = new (class clothing_type, _hiding : hiding,
                                           _not_remove : not_remove);
}
class clothing_type query_clothing_type(string name) {
   return _types[name];
}
string *query_clothing_cannot_remove(string type) {
   class clothing_type bing;
   bing = _types[type];
   if (bing) {
      return bing->_not_remove;
   }
   return 0;
}
string *query_clothing_hiding(string type) {
   class clothing_type bing;
   bing = _types[type];
   if (bing) {
      return bing->_hiding;
   }
   return ({ });
}
int query_clothing_depth(mixed type) {
   class clothing_type bing;
   int depth;
   string str;
   int min_depth;
   if (stringp(type)) {
      bing = _types[type];
      if (bing) {
         return bing->_depth;
      }
   } else if (pointerp(type)) {
      min_depth = 100000;
      foreach (str in type) {
         depth = query_clothing_depth(str);
         if (depth < min_depth && depth > 0) {
            min_depth = depth;
         }
      }
      return min_depth;
   }
   return 0;
}
int query_clothing_maximum_depth(mixed type) {
   class clothing_type bing;
   int depth;
   string str;
   int max_depth;
   if (stringp(type)) {
      bing = _types[type];
      if (bing) {
         return bing->_depth;
      }
   } else if (pointerp(type)) {
      max_depth = 0;
      foreach (str in type) {
         depth = query_clothing_depth(str);
         if (depth > max_depth) {
            max_depth = depth;
         }
      }
      return max_depth;
   }
   return 0;
}
mapping query_all_clothing_types() {
   return _types;
}
private void check_clothing_types() {
   string ty;
   class clothing_type bits;
   string *stuff;
   string bing;
   string type;
   int rank;
tell_creator("presto", "called check_clothing_types\n");
   foreach (ty, bits in _types) {
      foreach (bing in bits->_not_remove) {
         if (!query_clothing_type(bing)) {
            write("Unknown clothing type " + bing + " in the not remove "
                  " for " + ty + ".\n");
         }
      }
      foreach (bing in bits->_hiding) {
         if (!query_clothing_type(bing)) {
            write("Unknown clothing type " + bing + " in the hiding "
                  " for " + ty + ".\n");
         }
      }
   }
   rank = 1;
   foreach (bing in _zone_level) {
      stuff = query_clothing_zone(bing);
      foreach (type in stuff) {
         bits = _types[type];
         if (!bits->_depth &&
             (sizeof(bits->_not_remove) == 0  ||
             bits->_not_remove[0] == "all covering")) {
            bits->_depth = rank;
            rank = fixup_types(type, stuff);
         }
      }
      foreach (type in stuff) {
         bits = _types[type];
         if (!bits->_depth) {
tell_creator("presto", "setting depth of %O to %d\n", type, rank + 1);
            bits->_depth = rank++;
         }
      }
   }
}
private int fixup_types(string type, string *types) {
   string bing;
   class clothing_type base;
   class clothing_type bits;
   int depth;
   base = _types[type];
   depth = base->_depth + 1;
   foreach (bing in types) {
      bits = _types[bing];
      if (!bits->_depth &&
          member_array(type, bits->_not_remove) != -1) {
         bits->_depth = depth;
         depth = fixup_types(bing, types);
      }
   }
   return depth;
}
protected void add_clothing_zone(string zone, string *types) {
   string ty;
   foreach (ty in types) {
      if (!query_clothing_type(ty)) {
         write("Incorrect clothing type " + ty + " in zone " + zone + ".\n");
      }
   }
   _zones[zone] = types;
   _zone_level += ({ zone });
}
protected void add_zone_coverage(string type, string *zones) {
  string zone;
  if(!query_clothing_type(type))
    write("Incorrect clothing type " + type + "\n");
  foreach(zone in zones)
    if(member_array(type, zones) != -1)
      _zones[zone] += ({ type });
}
mapping query_all_clothing_zones() {
   return _zones;
}
string *query_clothing_zone(string zone) {
   return _zones[zone];
}
string query_zone_name(string type) {
   string zone;
   string *stuff;
   foreach (zone, stuff in _zones) {
      if (member_array(type, stuff) != -1) {
         return zone;
      }
   }
   return 0;
}
string *query_zone_names(string type) {
   string zone;
   string *stuff;
   string *zones;
   if(_equivilants[type])
     type = _equivilants[type];
   zones = ({ });
   foreach (zone, stuff in _zones) {
     if (member_array(type, stuff) != -1 && zone) {
       zones += ({ zone });
     }
   }
   return zones;
}
int query_zone_level(string zone) {
   int i;
   i = member_array(zone, _zone_level);
   return i * 100;
}
protected void add_equivilant_type(string name, string equiv) {
   if (!query_clothing_type(equiv)) {
      write("Incorrect clothing type " + equiv + " in equivilant listing.\n");
   }
   _equivilants[name] = equiv;
}
mapping query_all_equivilant_types() {
   return _equivilants;
}
string query_equivilant_type(string type) {
   return _equivilants[type];
}
int query_valid_type(string type) {
   if (query_clothing_type(type) ||
       query_equivilant_type(type)) {
      return 1;
   }
   return 0;
}