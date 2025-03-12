#include <move_failures.h>
inherit "/std/container";
inherit "/std/basic/close_lock_container";
inherit "/std/basic/condition";
inherit "/std/basic/holdable";
void create() {
  do_setup++;
  container::create();
  close_lock_container::create();
  condition::create();
  holdable::create();
  set_max_cond(400);
  set_cond(400);
  set_damage_chance(20);
  set_can_export_inventory();
  set_opaque();
  set_open();
  do_setup--;
  if ( !do_setup ) {
    this_object()->setup();
  }
  add_help_file("baggage");
}
void init() {
  close_lock_container::init();
}
int add_weight( int n ) {
  if ( !( ::add_weight( n ) ) ) return 0;
  if ( n >= 0 ) {
    remove_call_out( "check_breakages" );
    call_out( "check_breakages", 5 + random( 16 ) );
  }
  return 1;
}
void check_breakages() {
  object *obs, carrier;
  int i, amt, wt;
  carrier = environment(this_object());
  while (carrier && (!living(carrier)))
    carrier = environment(carrier);
  if (!carrier)
    return;
  obs = all_inventory();
  wt = query_loc_weight() - (int)query_property("padded");
  for (i=0;i<sizeof(obs);i++)
    if ((amt = obs[i]->query_property("fragile"))) {
      if (wt <= amt || ((wt - amt)*100)/amt <= random(100))
          obs[i] = 0;
    } else
      obs[i] = 0;
  obs = obs - ({ 0 });
  if (sizeof(obs) && environment(carrier)) {
    tell_room(environment(carrier), carrier->the_short()+" breaks "+
          (sizeof(obs)>1?"some things":"one thing")+" in "+
          query_multiple_short(({ this_object() }))+".\n", ({ carrier }));
    tell_object(carrier, "You break "+query_multiple_short(obs)+" in "+
          query_multiple_short(({ this_object() }))+".\n");
    obs->dest_me();
  }
}
string long( string word, int dark ) {
  string ret;
  ret = ::long( word, dark );
  ret += cond_string();
  if ( query_transparent() || !query_closed() ) {
    if (dark == 2 ||
        dark == -2) {
       if (query_contents() != "") {
          ret += "$C$$the_short:" + file_name(this_object()) + "$ contains "
                 "some items you cannot make out.\n";
       }
    } else {
       ret += query_contents( "$C$$the_short:"+ file_name( this_object() ) +
           "$ contains " );
    }
  }
  ret += long_status();
  return ret;
}
int ensure_open() {
  if ( query_locked() ) {
      write( "The "+ short( 0 ) +" is locked.\n" );
      return 0;
   }
   if ( query_closed() ) {
      if ( do_open() ) {
         write( "You open the "+ short( 0 ) +".\n" );
         return 1;
      } else {
         write( "You can't open the "+ short( 1 ) +".\n" );
         return 0;
      }
   }
   return 1;
}
mixed stats() {
   return container::stats() + close_lock_container::stats();
}
mapping int_query_static_auto_load() {
  return ([
    "::" : container::int_query_static_auto_load(),
    "condition" : condition::query_static_auto_load(),
    "hold" : holdable::query_static_auto_load(),
    "trans" : query_transparent(),
    "difficulty" : query_difficulty(),
    "key" : query_key(),
    "trap open func" : query_open_trap_func(),
    "trap lock func" : query_lock_trap_func(),
    "trap open ob" : query_open_trap_ob(),
    "trap lock ob" : query_lock_trap_ob(),
  ]);
}
mapping query_dynamic_auto_load() {
   return ([
     "::" : container::query_dynamic_auto_load(),
     "condition" : condition::query_dynamic_auto_load(),
     "hold" : holdable::query_dynamic_auto_load(),
     "locked" : query_locked(),
     "stuck" : query_stuck(),
     "closed" : query_closed(),
   ]);
}
void init_dynamic_arg(mapping map, object) {
  object money;
  if (map["::"]) {
    container::init_dynamic_arg(map["::"]);
  }
  if (map["condition"]) {
    condition::init_dynamic_arg(map["condition"]);
  }
  if (map["hold"]) {
    holdable::init_dynamic_arg(map["hold"]);
  }
  if (sizeof(map["money"])) {
     money = clone_object("/obj/money");
     money->set_money_array(map["money"]);
     money->move(this_object());
  }
  if (map["closed"]) {
     set_closed();
  } else {
     set_open();
  }
  if (map["locked"]) {
     set_locked();
  } else {
     set_unlocked();
  }
  set_stuck(map["stuck"]);
}
void init_static_arg(mapping args) {
  if (args["::"]) {
    ::init_static_arg(args["::"]);
  }
  if (args["condition"]) {
    condition::init_static_arg(args["condition"]);
  }
  if (args["hold"]) {
    holdable::init_static_arg(args["hold"]);
  }
  if (!undefinedp(args["trans"])) {
    if (args["trans"]) {
       set_transparent();
    } else {
       set_opaque();
    }
  }
  if (!undefinedp(args["difficulty"])) {
    set_difficulty(args["difficulty"]);
  }
  if (!undefinedp(args["key"])) {
    set_key(args["key"]);
  }
  if (!undefinedp(args["trap open func"])) {
    set_open_trap(args["trap open ob"], args["trap open func"]);
  }
  if (!undefinedp(args["trap lock func"])) {
    set_lock_trap(args["trap lock ob"], args["trap lock func"]);
  }
  if (!query_max_weight()) {
     set_max_weight(5);
  }
}
mixed query_static_auto_load() {
  if ( !query_name() || ( query_name() == "object" ) ) {
    return 0;
  }
  if ( explode( file_name( this_object() ), "#" )[ 0 ] == "/obj/baggage" ) {
    return int_query_static_auto_load();
  }
  return ([ ]);
}
int can_find_match_recurse_into(object looker) {
   if (query_closed()) {
      return 0;
   }
   return ::can_find_match_recurse_into(looker);
}
int test_add(object ob, int flag) {
  if(flag)
    return 0;
  return ::test_add(ob, flag);
}
varargs int move(mixed dest, string mess1, string mess2) {
   object from;
   int result;
   result = holdable::move(dest);
   if (result != MOVE_OK) {
      return result;
   }
   from = environment();
   result = container::move(dest, mess1, mess2);
   if (result == MOVE_OK) {
      we_moved(from, environment());
   }
   return result;
}
string *parse_command_adjectiv_id_list() {
    return container::parse_command_adjectiv_id_list() +
        close_lock_container::parse_command_adjectiv_id_list();
}
void break_me() {
  all_inventory()->move( environment(), "$N fall$s out of " + a_short() +"." );
  ::break_me();
}
void dest_me() {
   close_lock_container::dest_me();
   container::dest_me();
}