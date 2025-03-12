#include <move_failures.h>
#include <virtual.h>
inherit "/std/container";
inherit "/std/basic/wearable";
inherit "/std/basic/close_lock";
string pocket_mess;
mixed *pockets;
nosave int biggest;
int _is_pair = 0;
void create() {
   do_setup++;
   container::create();
   wearable::create();
   close_lock::create();
   set_stuck(1);
   set_can_export_inventory();
   pocket_mess = "a pocket in $ob_short$";
   pockets = ({ });
   add_alias( "clothing" );
   add_plural( "clothes" );
   add_immune_to( "blunt" );
   add_help_file("clothing");
   set_opaque();
   set_open();
   if ( !query_property( "shop type" ) ) {
      add_property( "shop type", "haberdashery" );
   }
   do_setup--;
   if ( !do_setup ) {
      this_object()->setup();
   }
}
int query_clothing() { return 1; }
string query_pronoun()  {
   if (!_is_pair)
      return "it";
   return "they";
}
string query_objective()  {
   if (!_is_pair)
      return "it";
   return "them";
}
void set_is_pair(int comes_in_pairs)  {
   _is_pair = comes_in_pairs;
   if (_is_pair)
      add_adjective(({ "pair", "of" }));
}
int query_is_pair() { return _is_pair; }
string long( string word, int dark ) {
   int i;
   string ret, *sizes;
   mapping types;
   ret = container::long( word, dark );
   if ( sizeof( pockets ) && !dark ) {
      types = ([ ]);
      for ( i = 0; i < sizeof( pockets ); i += 2 ) {
         types[ pockets[ i ] ]++;
      }
      sizes = m_indices( types );
      for ( i = 0; i < sizeof( sizes ); i++ ) {
         sizes[ i ] = query_num( types[ sizes[ i ] ] ) +" "+ sizes[ i ] +
               " pocket"+ ( types[ sizes[ i ] ] > 1 ? "s" : "" );
      }
      ret += "$C$"+ the_short() +" has "+ query_multiple_short( sizes ) +".\n"+
            query_contents( "It contains: " );
      ret += close_lock::long_status();
   }
   return ret + wearable::long( word, dark );
}
varargs string pretty_short( object thing ) {
   mixed pshort = ::pretty_short( thing );
   string short_stat = close_lock::short_status();
   if( arrayp( pshort ) ) {
      for( int i = 0; i < sizeof( pshort ); ++i ) {
         pshort[i] = short_stat + pshort[i];
      }
   } else {
      pshort = short_stat + pshort;
   }
   return pshort;
}
varargs string pretty_plural( object thing ) {
   mixed plural = ::pretty_plural( thing );
   string short_stat = close_lock::short_status();
   if( arrayp( plural ) ) {
      for( int i = 0; i < sizeof( plural ); ++i ) {
         plural[i] = short_stat + plural[i];
      }
   } else {
      plural = short_stat + plural;
   }
   return plural;
}
string query_pocket_mess() { return pocket_mess; }
void set_pocket_mess( string words ) { pocket_mess = words; }
mixed *query_pockets() { return pockets; }
void remove_pockets() {
  for( int i = 0; i < sizeof( pockets ); i+=2 ) {
    set_max_weight( query_max_weight() - pockets[ i+1 ] );
  }
  pockets = ({ });
}
void add_pocket( string type, int amount ) {
   if ( !type || ( type == "" ) || ( amount < 1 ) ) {
      return;
   }
   pockets += ({ type, amount });
   set_max_weight(query_max_weight() + amount);
   if ( amount > biggest ) {
      biggest = amount;
   }
}
int test_add( object thing, int flag ) {
   int i;
   if ( !sizeof( pockets )  || flag ) {
      return 0;
   }
   if ( !environment( thing ) ) {
      return 1;
   }
   if ( !biggest ) {
      for ( i = 0; i < sizeof( pockets ); i+= 2 ) {
         if ( pockets[ i + 1 ] > biggest ) {
            biggest = pockets[ i + 1 ];
         }
      }
   }
   if ( (int)thing->query_complete_weight() > biggest ) {
      return write( (string)thing->the_short() +" is too big "+
            "to fit in any of "+ the_short() +"'s pockets.\n" );
   }
   return ::test_add(thing, flag);
}
int can_find_match_recurse_into(object looker) {
   if (query_closed()) {
      return 0;
   }
   return ::can_find_match_recurse_into(looker);
}
int query_ac( string type, int amount ) {
   do_damage( type, amount );
   return 0;
}
void setup_clothing( int number ) {
   set_max_cond( number );
   set_cond( number );
   set_lowest_cond( number );
}
int query_value() {
   return modify_value( container::query_value() );
}
int query_full_value() { return container::query_value(); }
int drop(mixed stuff) {
   if ( worn_by ) {
      if ( living( worn_by ) ) {
         return 1;
      }
   }
   return container::drop(stuff);
}
varargs int move( mixed dest, string messin, string messout ) {
   int flag;
   object from;
   from = environment();
   flag = container::move( dest, messin, messout );
   if ( ( flag == MOVE_OK ) && worn_by ) {
      set_worn_by( 0 );
      if (from) {
         from->remove_inventory_container(this_object());
      }
      if (environment()) {
         environment()->add_inventory_container(this_object());
      }
   }
   return flag;
}
string *parse_command_adjectiv_id_list() {
    return container::parse_command_adjectiv_id_list() +
        close_lock::parse_command_adjectiv_id_list();
}
void dest_me() {
   set_worn_by( 0 );
   container::dest_me();
}
void break_me() {
   if ( worn_by ) {
      all_inventory()->move( environment( worn_by ), "$N fall$s from "+
            a_short() +"." );
   } else {
      all_inventory()->move( environment(), "$N fall$s out of "+
            a_short() +"." );
   }
   ::break_me();
}
mixed *stats() {
   int i;
   mixed *ret;
   ret = container::stats() + wearable::stats();
   for ( i = 0; i < sizeof( pockets ); i += 2 ) {
      ret += ({ ({ pockets[ i ] +" pocket", pockets[ i + 1 ] }) });
   }
   return ret;
}
mapping int_query_static_auto_load() {
   return ([
      "::" : container::int_query_static_auto_load(),
      "wear" : wearable::query_static_auto_load(),
      "pocket mess" : pocket_mess,
      "pockets" : pockets,
      "trans" : query_transparent(),
      "difficulty" : query_difficulty(),
      "key" : query_key(),
      "trap open func" : query_open_trap_func(),
      "trap lock func" : query_lock_trap_func(),
      "trap open ob" : query_open_trap_ob(),
      "trap lock ob" : query_lock_trap_ob(),
      "stuck" : query_stuck(),
      "pair" : _is_pair
   ]);
}
mapping query_static_auto_load() {
   if ( base_name(this_object()) != __FILE__[0..<3]) {
      return ([ ]);
   }
   return int_query_static_auto_load();
}
mapping query_dynamic_auto_load() {
   return ([
      "::" : container::query_dynamic_auto_load(),
      "wear" : wearable::query_dynamic_auto_load(),
      "locked" : query_locked(),
      "closed" : query_closed(),
   ]);
}
void init_static_arg( mapping map ) {
   if ( !mapp( map ) ) {
      return;
   }
   if ( map[ "::" ] ) {
      container::init_static_arg( map[ "::" ] );
   }
   if ( map[ "wear" ] ) {
      wearable::init_static_arg( map[ "wear" ] );
   }
   if ( !undefinedp( map[ "pocket mess" ] ) ) {
      pocket_mess = map[ "pocket mess" ];
   }
   if ( !undefinedp( map[ "pockets" ] ) ) {
      pockets = map[ "pockets" ];
   }
   if (!undefinedp(map["pair"]))
      _is_pair = map["pair"];
   if (!undefinedp(map["trans"])) {
      if (map["trans"]) {
         set_transparent();
      } else {
         set_opaque();
      }
   }
   if (!undefinedp(map["difficulty"])) {
      set_difficulty(map["difficulty"]);
   }
   if (!undefinedp(map["key"])) {
      set_key(map["key"]);
   }
   if (!undefinedp(map["trap open func"])) {
      set_open_trap(map["trap open ob"], map["trap open func"]);
   }
   if (!undefinedp(map["trap lock func"])) {
      set_lock_trap(map["trap lock ob"], map["trap lock func"]);
   }
   if ( !undefinedp( map[ "stuck" ] ) ) {
      set_stuck(map["stuck"]);
   }
}
void replace_me(){
  object receipt;
  receipt = clone_object( "/std/object" );
  receipt->set_name( "receipt" );
  receipt->set_short( "destructed item receipt" );
  receipt->add_adjective( ({ "destructed", "item" }) );
  receipt->set_long( "This seems to be a small piece of paper.\n" );
  receipt->set_read_mess( "According to our sources, your "+query_short()+" was not "
                          "allowed to exist.  Have a nice day." );
  receipt->move( environment() );
  receipt->set_weight( 1 );
  destruct( this_object() );
}
void init_dynamic_arg( mapping map, object ob ) {
   mapping stat_temp;
   string virt_name, new_name;
   if ( map[ "::" ] ) {
      container::init_dynamic_arg( map[ "::" ], ob );
   }
   if ( map[ "wear" ] ) {
      wearable::init_dynamic_arg( map[ "wear" ], ob );
   }
   if ( !undefinedp( map[ "locked" ] ) ) {
      if ( map[ "locked" ] ) {
         set_locked();
      } else {
         set_unlocked();
      }
   }
   if ( !undefinedp( map[ "closed" ] ) ) {
      if (map["closed"]) {
         set_closed();
      } else {
         set_open();
      }
   }
   if( virt_name = query_property( VIRTUAL_NAME_PROP ) ) {
      if( file_size( virt_name ) == -1 ) {
         new_name = ( CLONER )->other_file( virt_name );
         if( stringp( new_name ) && ( new_name != virt_name ) ) {
            add_property( VIRTUAL_NAME_PROP, new_name );
            virt_name = new_name;
         } else {
            if( VIRTUAL_HANDLER->query_forbidden( virt_name ) ) {
               call_out( "replace_me", 1 );
            } else {
               VIRTUAL_HANDLER->add_missing( virt_name );
            }
         }
      }
      if( file_size( virt_name ) != -1 &&
          query_property( "virtual time" ) < stat( virt_name )[1] ) {
         stat_temp = ( VIRTUAL_HANDLER )->new_data( virt_name );
         if( mapp( stat_temp ) ) {
            init_static_arg( stat_temp );
            add_property( "virtual time", time() );
         }
      }
   }
}