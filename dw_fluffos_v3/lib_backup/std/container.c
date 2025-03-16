#include <move_failures.h>
#include <player.h>
#include <player_handler.h>
inherit "/std/object";
inherit "/std/basic/cute_look";
inherit "/std/basic/export_inventory";
inherit "/global/auto_load";
private nosave int _max_weight;
private nosave int _loc_weight;
private nosave int _max_items;
private nosave int _prevent_insert;
private nosave string _ownership;
private nosave object _player;
private nosave int _n_tracked_items;
private nosave int _tracking;
void create() {
  registered_containers = ({ });
  _n_tracked_items = 0;
  _tracking = 1;
  export_inventory::create();
  object::create();
}
int query_max_items() {
  if(_max_items)
    return _max_items;
  if(_max_weight)
    return 4 * sqrt(_max_weight);
  return -1;
}
void set_max_items( int number ) { _max_items = number; }
int query_max_weight() { return _max_weight; }
void set_max_weight( int number ) { _max_weight = number; }
int query_loc_weight() { return _loc_weight; }
void update_loc_weight() {
   object thing;
   _loc_weight = 0;
   foreach ( thing in all_inventory( this_object() ) )
      _loc_weight += (int)thing->query_complete_weight();
}
int query_complete_weight() {
   return ::query_complete_weight() + _loc_weight;
}
int add_weight( int n ) {
#ifdef 0
  if ( _prevent_insert )
    return 0;
#endif
  if ( !_max_weight ) {
    _loc_weight += n;
    return 1;
  }
  if ( n + _loc_weight > _max_weight )
    return 0;
  if ( !environment() ) {
    _loc_weight += n;
    return 1;
  }
  if ( !environment()->add_weight( n ) )
    return 0;
  _loc_weight += n;
  return 1;
}
string query_ownership() { return _ownership; }
void set_ownership( string word ) {
  if( word )
    _ownership = lower_case( word );
  else
    _ownership = word;
}
int test_remove( object thing, int flag, mixed dest ) {
  int player;
  string str;
  if( !_ownership || !this_player() ) {
    return 1;
  }
  if( objectp( dest ) ) {
    dest = file_name( dest );
  }
  if( dest == "/room/rubbish" || dest == "/room/vault" ) {
    return 1;
  }
  str = "Item " + file_name( this_object() ) + " accessed by " +
    this_player()->query_short() + " which belongs to $C$" + _ownership;
  if( (string)this_player()->query_name() == _ownership ) {
    str += ".  Taking items, no theft event.";
    log_file( "/w/trilogy/CONTAINER", str + "\n" );
    return 1;
  }
  player = PLAYER_HANDLER->test_user( _ownership );
  if( player ) {
    str += ", who is a player.  ";
    if( !pk_check( this_player(), _ownership, 1 ) &&
      environment( this_player() ) ) {
      str += "PK check succeded: Taking items, theft event triggered.";
      this_player()->zap_harry_shadow();
      event( environment( this_player() ), "theft", this_player(),
        this_object(), ({ thing }) );
      log_file( "/w/trilogy/CONTAINER", str + "\n" );
      return 1;
    } else {
      str += "PK check failed: Cannot take items.";
      write( "An unseen force stays your hand.\n" );
      log_file( "/w/trilogy/CONTAINER", str + "\n" );
      return 0;
    }
  } else {
    str += ", which is not a player.  Taking items, theft event triggered.";
    this_player()->zap_harry_shadow();
    event( environment( this_player() ), "theft", this_player(),
      this_object(), ({ thing }) );
    log_file( "/w/trilogy/CONTAINER", str + "\n" );
    return 1;
  }
}
int test_add(object ob, int flag) {
  if(!_max_weight && !_max_items)
    return 1;
  if(ob->query_max_weight() > _max_weight - _loc_weight) {
    return 0;
  }
  if(this_object()->query_length() > 1 &&
     this_object()->query_length() < ob->query_length()) {
    return 0;
  }
  if(this_object()->query_width() > 1 &&
     this_object()->query_width() < ob->query_width()) {
    return 0;
  }
  if(ob->query_max_weight())
    return ((sizeof(deep_inventory(this_object())) +
             sizeof(deep_inventory(ob))) < query_max_items());
  else
    return sizeof(deep_inventory(this_object())) < query_max_items();
}
int set_prevent_insert() { _prevent_insert = 1; }
int reset_prevent_insert() { _prevent_insert = 0; }
int query_prevent_insert() { return _prevent_insert; }
varargs int move(mixed dest, mixed messin, mixed messout) {
  if (_prevent_insert && _loc_weight && !living(dest) && environment(dest))
    return MOVE_INVALID_DEST;
  return object::move( dest, messin, messout );
}
object *find_inv_match( string words, object looker ) {
   object *things;
   things = all_inventory( this_object() );
   things = filter(things, (: $1->short(0) &&
                              (!$2 || $1->query_visible($2)) :), looker);
   return things;
}
int do_restore_inventory_error(object ob, int move_flag) {
   object receipt;
   int ret;
   receipt = clone_object(PLAYER_RECEIPT);
   receipt->setup_receipt(ob);
   receipt->set_weight(0);
   ret = receipt->move(this_object());
   if (ret != MOVE_OK) {
      receipt->dest_me();
   } else {
      move_flag = MOVE_OK;
      ob->move("/room/rubbish");
   }
   return move_flag;
}
protected int handle_restore_inventory(object ob) {
  int move_flag;
  ob->disable_item_tracking();
  move_flag = ob->move(this_object());
  ob->enable_item_tracking();
  if (move_flag != MOVE_OK) {
     move_flag = do_restore_inventory_error(ob, move_flag);
  }
  return move_flag;
}
mixed stats() {
  return ::stats() + ({
    ({ "loc_weight", query_loc_weight(), }),
    ({ "max_weight", query_max_weight(), }),
    ({ "max_items", query_max_items(), }),
    ({ "export invent", query_can_export_inventory() }),
  });
}
mapping int_query_static_auto_load() {
  mapping tmp;
  tmp = ::int_query_static_auto_load();
  return ([
     "::" : tmp,
     "max weight" : _max_weight,
     "prevent insert" : _prevent_insert,
     "can export inventory" : query_can_export_inventory(),
  ]);
}
mapping query_dynamic_auto_load() {
  mixed inventory;
  catch(inventory = create_auto_load( all_inventory( this_object() ), 0 ) );
  return ([
    "::" : object::query_dynamic_auto_load(),
    "inv" : inventory
  ]);
}
void set_player( object thing ) {
   ::set_player(thing);
    _player = thing;
}
object query_player() { return _player; }
nomask void enable_item_tracking() { _tracking = 1; }
nomask void disable_item_tracking() { _tracking = 0; }
nomask void event_container_move( object mover, mixed from, mixed to ) {
  if (_n_tracked_items)
    all_inventory()->event_container_move( mover, from, to );
}
void event_move_object( mixed from, mixed to ) {
  if (_n_tracked_items && _tracking && !interactive()) {
    all_inventory()->event_container_move( this_object(), from, to );
    if (objectp(from)) from->remove_tracked_items( _n_tracked_items );
    if (objectp( to )) to->add_tracked_items( _n_tracked_items );
  }
}
nomask void set_tracked_item_status_reason(string reason) {
  if (_n_tracked_items)
    all_inventory()->set_tracked_item_status( reason );
}
nomask void add_tracked_items( int n_items ) {
   _n_tracked_items += n_items;
   if (environment()) environment()->add_tracked_items( n_items );
}
nomask void remove_tracked_items( int n_items ) {
  _n_tracked_items -= n_items;
  if (environment()) environment()->remove_tracked_items( n_items );
}
nomask int query_tracked_items() {
  return _n_tracked_items;
}
int can_find_match_recurse_into(object looker) {
   object env;
   env = environment();
   while (env &&
          !living(env) &&
          env != looker &&
          env != environment(looker)) {
      env = environment(looker);
   }
   return env == looker || env == environment(looker);
}
int can_find_match_reference_inside_object(object thing, object looker) {
   return 1;
}
void init_dynamic_arg( mapping bing, object ) {
  function f;
  if ( bing[ "::" ] ) {
    ::init_dynamic_arg( bing[ "::" ] );
  }
  if ( bing[ "inv" ] ) {
    f = (: handle_restore_inventory($1) :);
    if (!_player) {
      _player = this_player();
    }
    if (_player) {
      load_auto_load_to_inventory( bing["inv"], this_object(), _player, f );
    } else {
      load_auto_load_to_inventory( bing["inv"], this_object(), this_player(), f);
    }
  }
}
void init_static_arg( mapping bing ) {
  if ( bing[ "::" ] ) {
    ::init_static_arg( bing[ "::" ] );
  }
  if ( !undefinedp( bing[ "max weight" ] ) ) {
    _max_weight = bing[ "max weight" ];
  }
  if ( !undefinedp( bing[ "prevent insert" ] ) ) {
    _prevent_insert = bing[ "prevent insert" ];
  }
  if (bing["can export inventory"]) {
    set_can_export_inventory();
  } else {
    reset_can_export_inventory();
  }
}
mixed query_static_auto_load() {
  if (file_name(this_object())[0..13] == "/std/container") {
    return int_query_static_auto_load();
  }
  return ([ ]);
}
void dest_me() {
   foreach( object ob in all_inventory( this_object() ) ) {
       reset_eval_cost();
       ob->dest_me();
   }
   ::dest_me();
}