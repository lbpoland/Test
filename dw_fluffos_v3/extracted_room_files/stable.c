# File: /lib/std/room/stable.c

#include <money.h>
#include <player.h>
inherit "/std/room/basic_room";
void load_me();
class stable {
   int date_in;
   int last_paid;
   string name;
   mixed* save_info;
}
private nosave string _directory;
private nosave int _start_cost;
private nosave int _cost_per_week;
private nosave mapping _stable_cache;
private nosave string* _stable_types;
private mapping _accounts;
int do_list();
int do_stable( object *obs );
int do_deposit( string mon );
int do_return( string num );
void create() {
  _start_cost = 400;
  _cost_per_week = 400;
  _stable_cache = ([ ]);
  _accounts = ([ ]);
  _stable_types = ({ });
  add_help_file( "stable" );
  ::create();
}
void init() {
  add_command( "list", "", (: do_list() :) );
  add_command( "stable", "<indirect:object:here>", (: do_stable($1) :) );
  add_command( "deposit", "<string'money'>", (: do_deposit($4[0]) :) );
  add_command( "return", "<string'horse num'>", (: do_return($4[0]) :) );
}
void set_save_directory( string directory ) {
  if ( directory[<1] != '/' )
    directory += "/";
  _directory = directory;
  load_me();
}
string query_save_directory() {
  return _directory;
}
void set_start_cost( int start_cost ) {
  _start_cost = start_cost;
}
int query_start_cost() {
  return _start_cost;
}
void set_cost_per_week( int cost_per_week ) {
  _cost_per_week = cost_per_week;
}
int query_cost_per_week() {
  return _cost_per_week;
}
void save_me() {
  unguarded( (: save_object(_directory + "main_account") :) );
}
void load_me() {
  unguarded( (: restore_object(_directory + "main_account", 1) :) );
}
int query_balance( string name ) {
  return _accounts[name];
}
void set_balance( string name, int amt ) {
  _accounts[name] = amt;
   save_me();
}
void adjust_balance( string name, int amt ) {
  _accounts[name] += amt;
  save_me();
}
int query_player_money( object player, string place ) {
  return player->query_value_in( place ) +
         query_balance( player->query_name() );
}
void remove_player_money( object player, int amt, string place ) {
  int balance;
  balance  = query_balance( player->query_name() );
  if ( balance < 0 ) {
     amt += -balance;
     balance = 0;
  } else {
    if ( amt <= balance ) {
      balance -= amt;
      amt = 0;
    } else {
      amt -= balance;
      balance = 0;
    }
  }
  if ( amt > 0 ) {
    player->pay_money( MONEY_HAND->create_money_array( amt, place ),
                       place );
   }
   set_balance( player->query_name(), balance );
}
void add_stable_type( string type ) {
  if ( member_array( type, _stable_types ) == -1) {
    _stable_types += ({ type });
  }
}
string* query_stable_types() {
  return _stable_types;
}
int can_stable_type( string type ) {
  if ( member_array( type, _stable_types ) != -1 ) {
    return 1;
  }
  return 0;
}
protected class stable* query_stable( string name ) {
  string str;
  if ( !_stable_cache[name] && file_size( _directory + name + ".o" ) > 0 ) {
    str = read_file( _directory + name + ".o" );
    if ( str ) {
      _stable_cache[name] = restore_variable( str );
    }
  }
  return _stable_cache[name];
}
protected void set_stable( string name, class stable* value ) {
  _stable_cache[name] = value;
  if ( !value || !sizeof( value ) ) {
    unguarded( (: rm(_directory + $(name) + ".o") :) );
  } else {
    unguarded( (: write_file( _directory + $(name) + ".o",
                  save_variable( $(value) ), 1 ) :) );
  }
}
int query_stabling_cost( string name, int pos ) {
  class stable* bing;
  bing = query_stable( name );
  if ( pos < 0 || pos >= sizeof( bing ) ) {
    return 0;
  }
  return ( ( time() - bing[pos]->last_paid ) * _cost_per_week ) /
           (7 * 24 * 60 * 60);
}
int add_to_stable( string name, object* horses ) {
  class stable* bing;
  class stable womble;
  object horse;
  bing = query_stable( name );
  if ( !bing ) {
    bing = ({ });
  }
  foreach ( horse in horses ) {
    womble = new( class stable );
    womble->date_in = time();
    womble->last_paid = time();
    womble->name = horse->query_short();
    womble->save_info = AUTO_LOAD_OB->create_auto_load( ({ horse }) );
    bing += ({ womble });
  }
  set_stable( name, bing );
  horses->move("/room/rubbish");
  return 1;
}
void print_ok_message( object me, object* horses ) {
  write( "You stable " + query_multiple_short( horses ) + " into " +
         the_short() + ".\n" );
  say( this_player()->the_short() + " stables " +
       query_multiple_short( horses ) + " into " + the_short() + ".\n" );
}
int do_stable( object *obs ) {
  class stable* bing;
  int cost;
  object horse;
  object *ok;
  string place;
  place = query_property( "place" );
  if ( !place )
    place = "default";
  bing = query_stable( this_player()->query_name() );
  ok = ({ });
  foreach ( horse in obs ) {
    if ( !can_stable_type( horse->query_transport_type() ) ) {
      add_failed_mess( "$I is not able to be stabled here.\n", ({ horse }) );
    } else if ( horse->query_owner() != this_player()->query_name() ) {
      add_failed_mess( "You do not own $I and therefore cannot stable them.\n",
                       ({ horse }) );
    } else {
      ok += ({ horse });
      cost += _start_cost;
    }
  }
  if ( sizeof( ok ) ) {
    if ( query_player_money( this_player(), place ) < cost ) {
      add_failed_mess( "You do not have enough money to stable $I, you "
                       "need " + MONEY_HAND->money_value_string(cost, place) +
                       ".\n", ok );
      return 0;
    }
    write( "It will cost you " + MONEY_HAND->money_value_string( cost, place ) +
           " to stable " + query_multiple_short( ok ) + " here and " +
           MONEY_HAND->money_value_string( _cost_per_week, place ) +
           " for each horse for every week it stays here.\nDo you accept "
           "this? " );
    input_to( "check_stable", 0, cost, ok, place );
    add_succeeded_mess( "" );
  }
  return sizeof( ok );
}
protected void check_stable( string mess, int cost, object *ok, string place ) {
  if ( strlen( mess ) && lower_case( mess )[0] == 'y' ) {
    if ( query_player_money( this_player(), place ) < cost ) {
      write("Oops!  You seem to have run out of money.\n" );
    } else {
      remove_player_money( this_player(), cost, place );
      add_to_stable( this_player()->query_name(), ok );
      print_ok_message( this_player(), ok );
    }
  } else {
    write( "Ok, abandoning the check in.\n" );
  }
}
int do_list() {
  class stable* bing;
  int i;
  int cost;
  int balance;
  string debt;
  string place;
  place = query_property( "place" );
  if ( !place )
    place = "default";
  bing = query_stable( this_player()->query_name() );
  balance = query_balance( this_player()->query_name() );
  if ( !bing || !sizeof( bing ) ) {
    if( !balance ) {
      add_failed_mess( "You do not have any horses stabled here.\n" );
      return 0;
    }
    write( "You have a balance of " +
           MONEY_HAND->money_value_string( cost, place ) +
           " in your stabling account.\n" );
    return 1;
  }
  for ( i = 0; i < sizeof( bing ); i++ ) {
    cost = query_stabling_cost( this_player()->query_name(), i );
    if ( cost == 0 ) {
      debt = "paid up";
    } else if (cost < 0) {
      debt = "in credit " + MONEY_HAND->money_value_string( -cost, place );
    } else {
      debt = "in debt " + MONEY_HAND->money_value_string( cost, place );
    }
    write( sprintf( " %c) %s; %s\n ", 'A' + i, bing[i]->name, debt ) );
  }
  if ( balance > 0 ) {
    write( "You have a stable balance of " +
           MONEY_HAND->money_value_string( balance, place ) + ".\n" );
  } else if ( balance < 0 ) {
    write( "You have a stable balance of " +
           MONEY_HAND->money_value_string( balance, place ) + " in debt.\n" );
  } else {
    write( "You do not have a balance at this time.\n" );
  }
  add_succeeded_mess( ({ "", "$N checks out $p horses.\n" }) );
  return 1;
}
int do_return( string num ) {
  class stable* bing;
  int pos;
  int cost;
  object* horses;
  string place;
  place = query_property( "place" );
  if ( !place )
    place = "default";
  bing = query_stable( this_player()->query_name() );
  if ( !sizeof( bing ) ) {
    add_failed_mess( "You do not have any horses stabled here.\n" );
    return 0;
  }
  num = lower_case( num );
  pos = num[0] - 'a';
  if ( pos < 0 || pos > sizeof( bing ) ) {
    add_failed_mess( "You must return a horse in the range 'A' - '" +
                     sprintf( "%c", 'A' + sizeof( bing ) - 1 ) + "'.\n" );
    return 0;
  }
  cost = query_stabling_cost( this_player()->query_name(), pos );
  if ( query_player_money( this_player(), place ) < cost ) {
    add_failed_mess( "You do not have enough money to return this horse "
                     "you need " +
                     MONEY_HAND->money_value_string( cost, place ) +
                     ".\n" );
    return 0;
  }
  horses = AUTO_LOAD_OB->load_auto_load_to_array( bing[pos]->save_info );
  horses->move( this_object() );
  horses->set_owner( this_player()->query_name() );
  bing = bing[0..pos - 1] + bing[pos + 1..];
  set_stable( this_player()->query_name(), bing );
  if ( cost > 0 ) {
    remove_player_money( this_player(), cost, place );
  }
  add_succeeded_mess( "$N $V $I from " + the_short() + ".\n", horses );
  return 1;
}
int do_deposit( string mon ) {
  string place;
  mixed money;
  int amt;
  place = query_property( "place" );
  if ( !place )
    place = "default";
  if ( undefinedp( query_balance( this_player()->query_name() ) ) ) {
    add_failed_mess( "You do not currently have a balance here.\n" );
    return 0;
  }
  money = MONEY_HAND->parse_money( mon, this_player(), place );
  if ( intp( money ) ) {
    switch ( money ) {
      case NO_MATCH :
        add_failed_mess( "You do not have '" + mon + "'.\n" );
        return 0;
      case NO_MONEY :
        add_failed_mess( "You can only deposit money.\n" );
        return 0;
      default :
        add_failed_mess( "You can only deposit legal tender.\n" );
        return 0;
    }
  }
  amt = money->query_value_in( place );
  if ( place != "default" ) {
    amt += money->query_value_in( "default" );
  }
  adjust_balance( this_player()->query_name(), amt );
  add_succeeded_mess( ({ "You deposit " +
                      MONEY_HAND->money_string( money->query_money_array() ) +
                      " into your stable account.\n",
                      "$N deposits some money into $p account.\n" }) );
  return 1;
}