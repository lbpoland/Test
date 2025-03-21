# File: /lib/std/room/furniture/furniture.c

#include <move_failures.h>
#include <position.h>
#include <tasks.h>
inherit "/obj/cont_save";
inherit "/std/basic/trap";
inherit "/std/room/furniture/inherit/furniture_base";
private nosave string _drawer_mess;
private nosave mixed *_drawers;
private nosave int _biggest;
private nosave int _drawers_inside;
private nosave object *_on_top;
private nosave int _has_surface;
#define DEBUG
void create() {
  do_setup++;
  ::create();
  _drawer_mess = "a drawer in $ob_short$";
  _drawers = ({ });
  _on_top = ({ });
  add_alias( "furniture" );
  add_plural( "furniture" );
  set_opaque();
  if (!query_property("shop type"))
    add_property( "shop type", "furniture" );
   do_setup--;
   if(!do_setup)
     this_object()->setup();
}
string query_drawer_mess() { return _drawer_mess; }
void set_drawer_mess( string words ) { _drawer_mess = words; }
mixed *query_drawers() { return _drawers; }
void add_drawer( string type, int amount ) {
   if ( !type || ( type == "" ) || ( amount < 1 ) ) {
      return;
   }
   _drawers += ({ type, amount });
   set_max_weight(query_max_weight() + amount);
   if ( amount > _biggest ) {
      _biggest = amount;
   }
}
int query_has_surface() { return _has_surface; }
void set_has_surface(int i) { _has_surface = i; }
void set_drawers_inside(int i) { _drawers_inside = i; }
int query_drawers_inside() { return _drawers_inside; }
varargs int move( mixed dest, string messin, string messout ) {
  int i, w;
  object from;
  w = (int)this_object()->query_complete_weight() * 5;
  if ( from = environment() ) {
    from->add_weight( -w );
  }
  if(!dest) {
    return MOVE_INVALID_DEST;
  }
  if (!( dest->add_weight( w ) ) ) {
    if ( from ) {
      from->add_weight( w );
    }
    return MOVE_TOO_HEAVY;
  }
  if ( stringp( dest ) ) {
    dest = find_object( dest );
  }
  i = ::move( dest, messin, messout );
  if ( i != MOVE_OK ) {
    if ( from ) {
      from->add_weight( w );
    }
    dest->add_weight( -w );
  } else if (query_light_needs_inform()) {
    if ( from ) {
      inform_of_light_level_change(from);
    }
    inform_of_light_level_change(dest);
  }
  return i;
}
string long( string word, int dark ) {
   int i;
   string ret, *sizes;
   mapping types;
  ret = ::long( word, dark );
   if ( sizeof( _drawers ) && !dark &&
        (!query_closed() || !_drawers_inside)) {
     types = ([ ]);
     for ( i = 0; i < sizeof( _drawers ); i += 2 ) {
       types[ _drawers[ i ] ]++;
     }
     sizes = m_indices( types );
     for ( i = 0; i < sizeof( sizes ); i++ ) {
       sizes[ i ] = query_num( types[ sizes[ i ] ] ) +" "+ sizes[ i ] +
         " drawer"+ ( types[ sizes[ i ] ] > 1 ? "s" : "" );
     }
     ret += "It has "+ query_multiple_short( sizes ) +".\n";
   }
   if(sizeof(_on_top))
     ret += query_contents( "On " + the_short() + " " +
                            (sizeof(_on_top) == 1 ? "is " : "are " ), _on_top);
   return ret;
}
varargs string query_contents( string start, object *things,
  int ignore_living) {
  if(!arrayp(things)) {
    things = this_object()->find_inv_match( "", this_player() );
    things -= ({ this_player() });
    things = filter_array( things, (: environment( $1 ) == this_object() :) );
    things -= _on_top;
  }
  return ::query_contents(start, things, ignore_living);
}
int test_remove(object thing, int flag, mixed dest) {
  int result;
  mixed *stuff;
  result = ::test_remove(thing, flag, dest);
  if(result) {
    stuff = thing->query_property("dropped");
    if(environment() &&
       dest == this_player() &&
       function_exists("test_occupier", environment()) &&
       !environment()->test_occupier(this_player()->query_name()) &&
       (!sizeof(stuff) || stuff[0] != this_player()->query_name())) {
      event(environment(this_player()), "theft", this_player(), this_object(),
            ({ thing }));
    }
    if(dest) {
      _on_top -= ({ thing });
      thing->remove_property("_on_top");
    }
    event(environment(), "save");
  }
  return result;
}
int test_add( object thing, int flag ) {
  int i;
  int result;
  if ( flag )
    return 0;
  if(!environment(thing))
    return 1;
  result = ::test_add(thing, flag);
  if(!result)
    return 0;
  if("/cmds/living/put"->query_con() == "on" && _has_surface) {
    _on_top += ({ thing });
    thing->add_property("_on_top", 1);
  } else if(sizeof(_drawers)) {
    if ( !_biggest )
      for ( i = 0; i < sizeof( _drawers ); i+= 2 )
        if ( _drawers[ i + 1 ] > _biggest )
          _biggest = _drawers[ i + 1 ];
    if ( (int)thing->query_complete_weight() > _biggest )
      return write( (string)thing->the_short() +" is too big "+
                    "to fit in any of "+ the_short() +"'s drawers.\n" );
  }
  event(environment(), "save", this_object());
  return result;
}
int pick_unlock(object player) {
  mixed owner;
  if(!environment())
    return ::pick_unlock(player);
  if(!environment() || !function_exists("query_owner", environment()))
    return ::pick_unlock(player);
  owner = environment()->query_owner();
  if(stringp(owner) && pk_check(player, owner, 1)) {
    write("You feel it would be wrong to try to break into "+
          this_object()->query_short() + ".\n");
    return 0;
  }
  return ::pick_unlock(player);
}
mapping int_query_static_auto_load() {
  return ([
           "::" : ::int_query_static_auto_load(),
           "drawer mess" : _drawer_mess,
           "drawers" : _drawers,
           "allowed_positions" : query_allowed_positions(),
           "trap" : query_trap_data(),
           "trap armed": query_trap_armed(),
           ]);
}
mapping query_static_auto_load() {
  return int_query_static_auto_load();
}
void init_static_arg( mapping map ) {
  if ( !mapp( map ) )
    return;
  if ( map[ "::" ] )
    ::init_static_arg( map[ "::" ] );
  if ( !undefinedp( map[ "drawer mess" ] ) )
    _drawer_mess = map[ "drawer mess" ];
  if ( !undefinedp( map[ "drawers" ] ) )
    _drawers = map[ "drawers" ];
  if(!undefinedp(map["allowed_positions"]))
    set_allowed_positions( map["allowed_positions"]);
  if(!undefinedp(map["trap"]))
    setup_trap(map["trap"][0],
                   map["trap"][1],
                   map["trap"][2],
                   map["trap"][3],
                   map["trap"][4]);
  if(!undefinedp(map["trap armed"]))
    set_trap_armed(map["trap armed"]);
}
void init_dynamic_arg(mapping bing) {
  object item;
  ::init_dynamic_arg(bing);
  foreach(item in all_inventory(this_object())) {
    if(item->query_property("_on_top"))
      _on_top += ({ item });
  }
}
string query_help_file_directory() {
  return "/doc/furniture/";
}
mixed *stats() {
  int i;
  mixed *ret;
  ret = ::stats();
  ret += ({ ({ "surface", _has_surface }) });
  for ( i = 0; i < sizeof( _drawers ); i += 2 )
    ret += ({ ({ _drawers[ i ] +" drawer", _drawers[ i + 1 ] }) });
  return ret;
}