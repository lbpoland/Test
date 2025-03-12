#include <move_failures.h>
#include <player.h>
inherit "/std/object";
inherit "/std/basic/cute_look";
inherit "/std/basic/item_chat";
inherit "/std/room/furniture/inherit/furniture_base";
private nosave int _loc_weight, _max_weight;
private nosave string *_shadows;
private nosave object _player;
private nosave string *_aliases;
private nosave int _use_internals;
void create() {
  do_setup++;
  furniture_base::create();
  object::create();
  add_alias( "furniture" );
  add_plural( "furniture" );
  set_opaque();
  do_setup--;
  if ( !do_setup ) {
    this_object()->setup();
  }
  set_no_all(1);
}
void init() {
  string alias;
  if(_aliases)
    foreach(alias in _aliases) {
      add_command(alias, "<indirect:object:me> {in|on|into} <indirect:object>",
                  (: "/cmds/living/put"->cmd($1, $3, $4) :) );
    }
  ::init();
}
void set_put_aliases(string *aliases) {
  _aliases = aliases;
}
void set_allow_use_internals(int allow) {
   _use_internals = allow;
}
int query_allow_use_internals() {
   return _use_internals;
}
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
  } else {
    if (_use_internals) {
      if (from) {
        from->remove_use_internal_object(this_object());
      }
      dest->add_use_internal_object(this_object());
    }
    if (query_light_needs_inform()) {
      if ( from ) {
        inform_of_light_level_change(from);
      }
      inform_of_light_level_change(dest);
    }
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
int test_remove(object thing, int flag, mixed dest) {
  mixed *stuff;
  object thief;
  if(environment() && this_player()) {
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
  return 1;
}
int test_add( object thing, int flag ) {
  if(environment())
    event(environment(), "save");
#ifdef DEBUG
  if(environment() && base_name(environment()) != "/room/rubbish")
    log_file(base_name(environment()) + ".log",
             "%s %s put on %s by %s.\n", ctime(time())[4..18],
             thing->query_short(), this_object()->query_short(),
             this_player() ? this_player()->query_name() : "Unknown");
#endif
  return 1;
}
void set_max_weight(int arg) { _max_weight = arg; }
int query_max_weight() { return _max_weight; }
int query_loc_weight() { return _loc_weight; }
int query_has_surface() { return 1; }
void update_loc_weight() {
  int i;
  object *contents;
  _loc_weight = 0;
  contents = all_inventory( this_object() );
  for ( i = 0; i < sizeof( contents ); i++ )
    _loc_weight += (int)contents[ i ]->query_complete_weight();
}
int query_complete_weight() {
  return ::query_complete_weight() + query_loc_weight();
}
int add_weight( int n ) {
  if ( !_max_weight ) return 1;
  if ( n + _loc_weight > _max_weight ) return 0;
  if ( !environment() ) {
    _loc_weight += n;
    return 1;
  }
  if ( !( environment()->add_weight( n ) ) ) return 0;
  _loc_weight += n;
  return 1;
}
int transfer_all_to(object dest) {
  object *ob;
  int i;
  ob = all_inventory(this_object());
  for (i=0;i<sizeof(ob);i++)
    ob[i]->move(dest);
  if (first_inventory(this_object())) return 0;
  return 1;
}
string long( string word, int dark ) {
   object *things;
   things = (object *)this_object()->find_inv_match( "all", this_player() );
   if ( !sizeof( things ) )
      return object::long( word, dark ) +"There is nothing on "+
            the_short() +".\n";
   return object::long( word, dark ) + query_contents( "On " +
            the_short() +" "+ ( sizeof( things ) == 1 ? "is " :
            "are " ), things );
}
object *find_inv_match( string words, object looker ) {
   int i;
   object *things;
   things = all_inventory( this_object() );
   for ( i = sizeof( things ) - 1; i > -1; i-- ) {
      if ( !things[ i ]->short( 0 ) ) {
         things = delete( things, i, 1 );
         continue;
      }
      if ( !looker )
         continue;
      if ( !things[ i ]->query_visible( looker ) )
         things = delete( things, i, 1 );
   }
   return things;
}
void set_player( object thing ) { _player = thing; }
object query_player() { return _player; }
mixed stats() {
  return ::stats() + ({
    ({ "loc_weight", query_loc_weight(), }),
    ({ "max_weight", query_max_weight(), }),
  });
}
mapping int_query_static_auto_load() {
  return ([
    "::" : ::int_query_static_auto_load(),
    "max weight" : _max_weight,
    "allowed positions" : query_allowed_positions(),
  ]);
}
mapping query_dynamic_auto_load() {
  mixed inventory;
  if (!inventory) {
    catch(inventory = PLAYER_OB->
        create_auto_load( all_inventory( this_object() ) ) );
  }
  return ([ "::" : ::query_dynamic_auto_load(),
            "inv" : inventory,
            "bonded" : query_bonded()
         ]);
}
int handle_restore_inventory(object ob) {
  return (int)ob->move(this_object());
}
void init_dynamic_arg( mapping bing ) {
  function f;
  if ( bing[ "::" ] ) {
    ::init_dynamic_arg( bing[ "::" ] );
  }
  if ( bing[ "inv" ] ) {
    f = (: handle_restore_inventory($1) :);
    if (_player) {
      _player->load_auto_load_to_inventory( bing["inv"], this_object(),
                                            _player, f);
    } else {
      PLAYER_OB->load_auto_load_to_inventory( bing["inv"], this_object(),
                                              this_player(), f);
    }
  }
  set_bonded(bing["bonded"]);
}
void init_static_arg(mapping bing) {
  if (bing["::"]) {
     ::init_static_arg(bing["::"]);
  }
  if (!undefinedp(bing["max weight"])) {
    _max_weight = bing["max weight"];
  if(!undefinedp(bing["allowed_positions"]))
    set_allowed_positions(bing["allowed_positions"]);
  }
}
mixed query_static_auto_load() {
  if ( base_name(this_object()) + ".c" == __FILE__ )
    return int_query_static_auto_load();
  return ([ ]);
}
void dest_me() {
  int i;
  object shadow;
  for ( i = 0; i < sizeof( _shadows ); i++ ) {
    if ( shadow = find_object( _shadows[ i ] ) ) {
      shadow->destruct_shadow( shadow );
    }
  }
  all_inventory()->dest_me();
  object::dest_me();
}
string query_help_file_directory() {
   return "/doc/furniture/";
}