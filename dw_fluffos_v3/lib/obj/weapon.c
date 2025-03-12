inherit "/std/object";
inherit "/std/weapon_logic";
inherit "/std/basic/condition";
inherit "/std/basic/holdable";
#include "weapon.h"
#include "money.h"
#include <move_failures.h>
#include <virtual.h>
string *un_modifyable;
mixed *wield_func;
void create() {
   set_damage_chance( 25 );
   un_modifyable = ({ });
   weapon_logic::create();
   holdable::create();
   condition::create();
   object::create();
   add_alias("weapon");
   add_plural("weapons");
   if (!query_property("shop type")) {
      add_property("shop type", "armoury");
   }
   add_help_file("weapon");
}
string short(int dark) {
   string str;
   str = "";
   return ::short(dark)+str;
}
void set_wield_func(string func, mixed ob) {
   if (!func) {
      wield_func = 0;
   } else {
      wield_func = ({ func, ob });
   }
}
int query_weapon() { return 1; }
string long(string s, int dark) {
   return ::long(s, dark)+cond_string();
}
void new_weapon( int new_condition ) {
   set_cond( new_condition );
   set_max_cond( new_condition );
   set_lowest_cond( new_condition );
}
int held_this_item(int held, object holder, mixed arg) {
  int weight;
  object weapon;
  if(held == 1 && interactive(holder)) {
    weight = this_object()->query_weight();
    foreach(weapon in holder->query_weapons())
      weight += weapon->query_weight();
    weight -= holder->query_str();
    switch(weight) {
    case 76..10000:
      tell_object(holder, "You struggle to hold " +
                  query_multiple_short(holder->query_holding() +
                                       ({ this_object() }) - ({ 0 })) +
                  ".\n");
      break;
    case 50..75:
      tell_object(holder, "You struggle slightly to hold " +
                  query_multiple_short(holder->query_holding() +
                                       ({ this_object() }) - ({ 0 })) +
                  ".\n");
      break;
    default:
    }
  }
  if (wield_func) {
    if (!held) {
      return call_other(wield_func[1], wield_func[0], 0);
    } else if (held == 1) {
      return call_other(wield_func[1], wield_func[0], holder);
    }
  }
  return 1;
}
varargs int move( mixed dest, string messin, string messout ) {
   int ret;
   int limb;
   object holder;
   limb = query_my_limb();
   holder = query_holder();
   ret = holdable::move(dest);
   if (ret != MOVE_OK) {
      return ret;
   }
   ret = object::move( dest, messin, messout );
   if (ret != MOVE_OK && holder) {
      holder->set_hold(this_object(), limb);
   }
   return ret;
}
void dest_me() {
  holdable::dest_me();
  object::dest_me();
}
int modify_damage(int val, string name) {
  int tmp;
  tmp = val + (val * query_enchant()) /
    (query_max_enchant() + query_enchant());
  if(member_array(name, un_modifyable) != -1)
    return tmp;
  tmp = ( tmp * query_cond() ) / query_max_cond();
  if(tmp < val / 10)
    return val / 10;
  return tmp;
}
void hit_weapon( int amount, string type ) {
   if ( member_array( type, un_modifyable) != -1 )
      return;
   do_damage( type, amount );
}
int add_immune(string name) {
   if (member_array(name, un_modifyable) != -1)
      return 0;
   un_modifyable += ({ name });
   return 1;
}
int remove_immune(string name) {
   int i;
   if ((i = member_array(name, un_modifyable)) == -1)
      return 0;
   un_modifyable = delete(un_modifyable, i, 1);
   return 1;
}
int query_value() {
   return ( ::query_value() * ( 10 + ( 90 * query_cond() ) /
                               query_max_cond() ) ) / 100;
}
int query_full_value() { return ::query_value(); }
mixed *query_money_array() {
   return (mixed *)MONEY_HAND->create_money_array(query_value());
}
int query_money(string type) {
   int i;
   mixed *m_a;
   m_a = (mixed *)MONEY_HAND->create_money_array(query_value());
   if ((i=member_array(type, m_a)) == -1)
      return 0;
   return m_a[i+1];
}
mixed *stats() {
   return
      object::stats() +
      condition::stats() +
      weapon_logic::stats();
}
void break_me() {
   if ( query_holder() ) {
      tell_object( query_holder(), "%^RED%^$C$"+ the_short() +" breaks!%^RESET%^\n" );
      tell_room( environment( query_holder() ), poss_short() +
                 " breaks!\n", query_holder() );
      query_holder()->set_unhold( this_object() );
   }
   ::break_me();
}
void player_wield(int pos) {
  if (!environment()) {
    return;
  }
  this_object()->hold_item( environment(), pos );
}
mapping query_static_auto_load() {
   if ( base_name( this_object() ) == "/obj/weapon" )
      return int_query_static_auto_load();
   return 0;
}
mapping int_query_static_auto_load() {
   mapping tmp;
   tmp = object::int_query_static_auto_load();
   return ([ "::" : tmp,
      "attack names" : attack_names,
      "attack data" : attack_data,
      "attack types" : attack_types,
      "hold" : holdable::query_static_auto_load(),
      "condition" : condition::query_static_auto_load()
          ]);
}
mapping query_dynamic_auto_load() {
   mapping map;
   map = ([
      "::" : object::query_dynamic_auto_load(),
      "condition" : condition::query_dynamic_auto_load(),
      "hold" : holdable::query_dynamic_auto_load(),
           ]);
   return map;
}
void init_static_arg( mapping map ) {
   if ( !mapp( map ) ) return ;
   if ( map[ "::" ] ) {
      object::init_static_arg( map[ "::" ] );
   }
   if ( map[ "attack names" ] ) {
      attack_names = map[ "attack names" ];
   }
   if ( map[ "attack data" ] ) {
      attack_data = map[ "attack data" ];
   }
   if ( map[ "attack types" ] ) {
      attack_types = map[ "attack types" ];
   }
   if ( !undefinedp( map[ "condition" ] ) ) {
      condition::init_static_arg( map[ "condition" ] );
   }
   if (map["no limbs"]) {
      holdable::init_static_arg(map);
   } else {
      holdable::init_static_arg(map["hold"]);
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
void init_dynamic_arg( mapping map, object ) {
   mapping stat_temp;
   string virt_name, new_name;
   if ( map[ "::" ] )
      object::init_dynamic_arg( map[ "::" ] );
   if ( !undefinedp( map[ "condition" ] ) ) {
      condition::init_dynamic_arg( map[ "condition" ] );
   }
   holdable::init_dynamic_arg(map["hold"], 1);
   if( virt_name = query_property( VIRTUAL_NAME_PROP) ) {
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