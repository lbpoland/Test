#include <cmr.h>
inherit "/std/basic/extra_look";
inherit "/std/basic/enchant";
inherit "/std/basic/id";
inherit "/std/basic/misc";
inherit "/std/basic/property";
inherit "/std/basic/read_desc";
inherit "/std/basic/auto_load";
inherit "/std/basic/help_files";
inherit "/std/basic/theft_callback";
inherit "/std/basic/effects";
#define AUTO_LOAD_TAG "basic.object";
nosave int do_setup;
nosave string create_me;
nosave string colour;
private string* _materials;
nosave object player;
void create() {
  _materials = ({ });
  extra_look::create();
  id::create();
  misc::create();
  property::create();
  read_desc::create();
  effects::create();
  seteuid( (string)"/secure/master"->
      creator_file( file_name( this_object() ) ) );
  if ( this_player() ) {
    create_me = (string)this_player()->query_name();
  } else {
    create_me = "who knows";
  }
  if ( !do_setup ) {
    this_object()->setup();
  }
}
void set_name( string word ) {
  if ( query_name() && ( query_name() != "object" ) ) {
    ::set_name(word);
    return;
  }
  ::set_name(word);
  if ( !short_d ) {
    short_d = word;
  }
  add_plural( pluralize( word ) );
}
string query_long_details(string arg, int dark, object looker) {
   string stuff;
   stuff = "";
   if ( this_player()->query_see_octarine() ) {
      stuff += enchant_string();
   }
   if ( sizeof( query_read_mess() ) ) {
      stuff += "It appears to have something written on it.\n";
   }
   return stuff;
}
string replace_long_dollars(object player, string text) {
   if ( colour ) {
      text = replace( text, "$colour$",
          (string)CMR_HANDLER->identify_colour( colour, player ) );
   }
   if ( sizeof(_materials) ) {
      text = replace( text, "$material$",
          (string)CMR_HANDLER->identify_material( _materials[0], player, 1 ) );
   }
   return text;
}
string long( string word, int dark ) {
   string stuff;
   stuff = ::long( word, dark );
   stuff += calc_extra_look();
   stuff += query_long_details(word, dark, this_player());
   stuff = replace_long_dollars( this_player(), stuff );
   return stuff;
}
string query_colour() { return colour; }
void set_colour( string word ) { colour = word; }
string query_material() {
   if (sizeof(_materials)) {
      return _materials[0];
   }
   return 0;
}
string* query_materials() {
    string *new_materials;
    new_materials = ({ });
     if(!_materials) _materials=({ });
    foreach( mixed bit in _materials ) {
        if ( stringp( bit ) ) {
            new_materials += ({ bit });
        }
        else {
            if ( arrayp( bit ) ) {
                foreach( mixed inner_bit in bit ) {
                    if( stringp( inner_bit ) ) {
                        new_materials += ({ inner_bit });
                    }
                }
            }
        }
    }
   return new_materials;
}
void set_material( mixed word ) {
   if (!arrayp(word)) {
      word = ({ word });
   }
   if (sizeof (word)) {
      _materials = word + _materials;
      add_adjective(word);
   }
}
void add_material(mixed material) {
   if (pointerp(material)) {
      _materials |= material;
   } else if (stringp(material)) {
      _materials += ({ material });
   }
   add_adjective(material);
}
string query_pronoun() { return "it"; }
string query_possessive() { return "its"; }
string query_objective() { return "it"; }
string query_cloned_by() { return create_me; }
void set_quality(int quality) {
   add_property("quality", quality);
}
int query_quality() {
   return query_property("quality");
}
mixed *stats() {
  if(!_materials) _materials=({ });
  return ({
    ({ "name" , query_name(), }),
    ({ "short", short( 0 ), }),
    ({ "plural", query_plural(0), }),
    ({ "weight", (int)this_object()->query_weight(), }),
    ({ "enchantment", query_enchant(), }),
    ({ "colour", colour, }),
    ({ "material", query_multiple_short(_materials), }),
    ({ "cloned by", create_me, }),
    ({ "length", (int)this_object()->query_length(), }),
    ({ "width", (int)this_object()->query_width(), }),
   }) + property::stats() + misc::stats() + effects::stats();
}
mapping int_query_static_auto_load() {
  return ([
    "name" : query_name(),
    "short" : short_d,
    "main plural" : plural_d,
    "long" : long_d,
    "alias" : query_alias(1),
    "adjective" : query_adjectives(1),
    "plural adjective" : query_plural_adjectives(),
    "plural" : query_plurals(),
    "value" : value,
    "value info" : value_info + ([ ]),
    "weight" : weight,
    "colour" : colour,
    "length" : length,
    "width" : width,
  ]);
}
mapping query_static_auto_load() {
  if ( !query_name() || ( query_name() == "object" ) ) {
    return 0;
  }
  if ( explode( file_name( this_object() ), "#" )[ 0 ] != "/std/object" ) {
    return ([ ]);
  }
  return int_query_static_auto_load();
}
mapping query_dynamic_auto_load() {
   mapping map;
   if ( !query_name() || ( query_name() == "object" ) ) {
      return 0;
   }
   if ( query_enchant() > this_object()->query_max_enchant() ) {
      set_enchant(this_object()->query_max_enchant());
   }
   map = ([
      "read mess" : ::query_read_mess(),
      "degrade enchantment" : query_degrade_enchant(),
      "enchantment" : query_real_enchant(),
      "enchantment time" : query_enchant_set_time(),
      "light" : query_my_light(),
      "materials" : query_materials(),
      "cloned by" : create_me,
   ]);
   if ( map_prop ) {
      map[ "properties" ] = copy( map_prop );
   }
   if ( timed_properties ) {
      save_player_properties();
      map[ "timed properties" ] = copy(timed_properties);
   }
   if ( sizeof(query_effs() ) ) {
     effect_freeze();
     effects_saving();
     map += ([
              "effects" : ({
                (mixed *)query_effs(),
                  (int *)query_eeq()
                  })
              ]);
     effect_unfreeze();
   }
   if ( this_object()->query_special() ) {
      map[ "special" ] =  (mapping)this_object()->query_special_info();
   }
   if ( query_deity() ) {
     map[ "consecrated" ] = query_deity();
   }
   return map;
}
void init_static_arg( mapping map ) {
   if ( !mapp( map ) ) {
      return;
   }
   if ( !undefinedp( map[ "name" ] ) ) {
      set_name(map[ "name" ]);
   }
   if ( !undefinedp( map[ "short" ] ) ) {
      set_short( map[ "short" ] );
   }
   if ( !undefinedp( map[ "main plural" ] ) ) {
      set_main_plural( map[ "main plural" ] );
   }
   if ( !undefinedp( map[ "long" ] ) ) {
      set_long( map[ "long" ] );
   }
   if ( map[ "alias" ] ) {
      set_aliases( map[ "alias" ] );
   }
   if ( map[ "adjective" ] ) {
      set_adjectives( map[ "adjective" ] );
   }
   if ( map[ "plural adjective" ] ) {
      set_plural_adjectives( map[ "plural adjective" ] );
   }
   if ( map[ "plural" ] ) {
      set_plurals( map[ "plural" ] );
   }
   if ( !undefinedp( map[ "value" ] ) ) {
      set_value( map[ "value" ] );
   }
   if ( !undefinedp( map[ "value info" ] ) ) {
      value_info = map[ "value info" ];
   }
   if ( !undefinedp( map[ "weight" ] ) ) {
      set_weight( map[ "weight" ] );
   }
   if ( !undefinedp( map[ "colour" ] ) ) {
      set_colour( map[ "colour" ] );
   }
   if ( !undefinedp( map[ "material" ] ) ) {
      set_material( map[ "material" ] );
   }
   if ( !undefinedp( map[ "length" ] ) ) {
      set_length( map[ "length" ] );
   }
   if ( !undefinedp( map[ "width" ] ) ) {
      set_width( map[ "width" ] );
   }
}
void set_player( object thing ) { player = thing; }
void init_dynamic_arg( mapping map, object ) {
   int recycle;
   if ( !mapp( map ) )
      return;
   recycle = query_property("no recycling");
   if ( map[ "properties" ] )
      map_prop = map[ "properties" ];
   if (recycle)
      add_property("no recycling", recycle);
   if ( map[ "timed properties" ] ) {
      timed_properties = map[ "timed properties" ];
      reload_player_properties();
   }
   if ( sizeof( map[ "read mess" ] ) )
      set_read_mess( map[ "read mess" ] );
   if ( !undefinedp( map[ "materials" ] ) ) {
      _materials = map["materials"];
   }
   set_enchant(map["enchantment"]);
   set_degrade_enchant(map["degrade enchantment"]);
   if (map["enchantment time"]) {
      set_enchant_set_time(map["enchantment time"]);
   }
   set_light( map[ "light" ] );
   create_me = map[ "cloned by" ];
   if( map[ "effects" ] ) {
     set_effs( map[ "effects" ][ 0 ] );
     set_eeq( map[ "effects" ][ 1 ] );
     if ( environment() && shadow( this_object(), 0 ) )
       move_object( environment() );
   }
   init_after_save();
   if ( map[ "special" ] ) {
      clone_object( "/std/shadows/object/special_item" )->
            setup_shadow( this_object(), player );
      this_object()->set_special_info( map[ "special" ] );
   }
   if ( map[ "consecrated" ] ) {
     set_deity( map[ "consecrated" ] );
   }
}
string query_readable_message(object player, int ignore_labels) {
   string ret;
   string bing;
   object *labels;
   object ob;
   int *enums;
   object store;
   ret = ::query_readable_message(player);
   if (!ignore_labels) {
      enums = (int *)this_object()->effects_matching( "object.label" );
      if ( !sizeof( enums ) ) {
         labels = ({ });
      } else {
         store = (object)this_object()->arg_of( enums[ 0 ] )[ 0 ];
         if ( !objectp( store ) ) {
            labels = ({ });
         } else {
            labels = (object *)store->find_inv_match( "" );
         }
      }
      if (sizeof(labels) && !ret) {
         ret = "";
      }
      foreach (ob in labels) {
         ret += "On " + ob->the_short() + " is written:\n";
         bing = ob->query_readable_message(player, 0);
         if (bing) {
            ret += bing;
         } else {
            ret += "Nothing.\n";
         }
      }
   }
   return ret;
}
string query_read_short(object player, int ignore_labels) {
   string ret;
   object *labels;
   int *enums;
   object store;
   ret = ::query_read_short(player);
   if (!ignore_labels) {
      enums = (int *)this_object()->effects_matching( "object.label" );
      if ( !sizeof( enums ) ) {
         labels = ({ });
      } else {
         store = (object)this_object()->arg_of( enums[ 0 ] );
         if ( !objectp( store ) ) {
            labels = ({ });
         } else {
            labels = (object *)store->find_inv_match( "" );
         }
      }
      if (sizeof(labels)) {
         if (ret) {
            ret += " and " + query_multiple_short(labels, "the") +
                   " stuck on $name$";
         } else {
            ret = query_multiple_short(labels, "the") +
                   " stuck on $name$";
         }
      }
   }
   return ret;
}
string query_help_file_directory() {
   return "/doc/object/";
}
int clean_up(int inherited) {
  if(inherited) {
    log_file("CLEANUP", "%s %s cleaned up.\n", ctime(time()),
             file_name(this_object()));
    move("/room/rubbish");
  }
  return 1;
}
void dest_me() {
  effects_desting();
  ::dest_me();
}