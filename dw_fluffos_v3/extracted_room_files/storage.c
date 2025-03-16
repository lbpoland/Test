# File: /lib/std/room/furniture/storage.c

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
#undef DEBUG
void create() {
   do_setup++;
   furniture_base::create();
   cont_save::create();
   _drawer_mess = "a drawer in $ob_short$";
   _drawers = ({ });
   add_alias( "furniture" );
   add_plural( "furniture" );
   set_opaque();
   do_setup--;
   if ( !do_setup ) {
     this_object()->setup();
   }
   set_no_all(1);
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
void set_drawers_inside(int i) { _drawers_inside = i; }
int query_drawers_inside() { return _drawers_inside; }
varargs int move( mixed dest, string messin, string messout ) {
  int i, w;
  object from;
  if (!move_check(dest)) {
     write(the_short() + " resists being picked up and shocks you slightly.\n");
     return MOVE_INVALID_DEST;
  }
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
int get(mixed dest) {
  if(!move_check(dest)) {
    write("You feel it would be wrong to take " + the_short() + ".\n");
    return 2;
  }
  return ::get(dest);
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
   return ret;
}
int test_remove(object thing, int flag, mixed dest) {
  int result;
  mixed *stuff;
  object thief;
  result = ::test_remove(thing, flag, dest);
  if(result && environment() && this_player()) {
    thief = this_player();
    if(thief->query_caster())
      thief = find_player(thief->query_caster());
    else if(thief->query_owner())
      thief = thief->query_owner();
    stuff = thing->query_property("dropped");
    if(function_exists("test_occupier", environment()) &&
       !environment()->test_occupier(thief->query_name()) &&
       (!sizeof(stuff) || stuff[0] != thief->query_name()) &&
       thief && environment(thief)) {
      event(environment(thief), "theft", thief, this_object(), ({ thing }));
    }
#ifdef DEBUG
    if(base_name(environment()) != "/room/rubbish")
      log_file(base_name(environment()) + ".log",
               "%s %s moved from %s to %s.\n", ctime(time())[4..18],
               thing->query_short(), this_object()->query_short(),
               dest->query_short());
#endif
    event(environment(), "save");
  }
  return result;
}
int test_add( object thing, int flag ) {
  int i;
  if ( flag )
    return 0;
  if(!environment(thing))
    return 1;
  if(sizeof(_drawers)) {
    if ( !_biggest )
      for ( i = 0; i < sizeof( _drawers ); i+= 2 )
        if ( _drawers[ i + 1 ] > _biggest )
          _biggest = _drawers[ i + 1 ];
    if ( (int)thing->query_complete_weight() > _biggest )
      return write( (string)thing->the_short() +" is too big "+
                    "to fit in any of "+ the_short() +"'s drawers.\n" );
  }
  event(environment(), "save", this_object());
  i = ::test_add(thing, flag);
#ifdef DEBUG
  if(environment() && base_name(environment()) != "/room/rubbish")
    log_file(base_name(environment()) + ".log",
             "%s %s put in %s by %s [%d].\n", ctime(time())[4..18],
             thing->query_short(), this_object()->query_short(),
             this_player() ? this_player()->query_name() : "Unknown",
             i);
#endif
  return i;
}
private int pick_ok(object player) {
  mixed owner;
  if(!environment() ||
     !function_exists("query_owner", environment()) ||
     environment()->test_occupier(player->query_name()))
    return ::pick_unlock(player);
  owner = environment()->query_owner();
  if(stringp(owner) && pk_check(player, owner, 1)) {
    write("You feel it would be wrong to try to break into "+
          this_object()->query_short() + ".\n");
    return 0;
  }
  return ::pick_unlock(player);
}
int pick_unlock(object player) {
  if(!pick_ok(player))
    return 0;
  return ::pick_unlock(player);
}
int pick_lock(object player) {
  if(!pick_ok(player))
    return 0;
  return ::pick_lock(player);
}
mixed *stats() {
  int i;
  mixed *ret;
  ret = ::stats();
  for ( i = 0; i < sizeof( _drawers ); i += 2 )
    ret += ({ ({ _drawers[ i ] +" drawer", _drawers[ i + 1 ] }) });
  return ret;
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
    set_allowed_positions(map["allowed_positions"]);
  if(!undefinedp(map["trap"]))
    setup_trap(map["trap"][0],
                   map["trap"][1],
                   map["trap"][2],
                   map["trap"][3],
                   map["trap"][4]);
  if(!undefinedp(map["trap armed"]))
    set_trap_armed(map["trap armed"]);
}
string query_help_file_directory() {
   return "/doc/furniture/";
}
mixed query_dynamic_auto_load() {
   mapping junk;
   junk = cont_save::query_dynamic_auto_load();
   if (!junk) {
      junk = ([ ]);
   }
   junk["bonded"] = query_bonded();
   return junk;
}
void init_dynamic_arg(mapping map, object) {
   cont_save::init_dynamic_arg(map, 0);
   set_bonded(map["bonded"]);
}