#include <armoury.h>
#include <money.h>
#include <move_failures.h>
#include <shops/item_shop.h>
#define INFINITE_LEFT 10000
#define TYPE "item shop type"
#define DISPLAY "display in shop"
#define SHOP_INHERIT "/std/shops/inherit/"
inherit SHOP_INHERIT + "clone_on_demand";
inherit SHOP_INHERIT + "open_shop";
inherit SHOP_INHERIT + "shop_event";
private nosave int _no_steal;
private nosave int _steal_difficulty;
private nosave string _shoplift_handler;
private nosave function _list_func;
private nosave function _browse_func;
private nosave function _buy_func;
private nosave function _sort_func;
void setup_safe();
void do_banking();
int do_word_buy(string str);
int do_word_browse(string str);
int do_buy( object *things );
int do_browse( object *things );
void remove_property(string name);
mixed query_property(string name);
void set_max_float( int );
int query_max_float();
private nosave object _safe;
private nosave int _hidden_safe;
private nosave int _max_float;
void create() {
  shop_event::create();
  clone_on_demand::create();
  this_object()->add_help_file("item_shop");
  setup_safe();
  set_max_float( 20000 + random( 50000 ) );
}
object query_safe() {
  return _safe;
}
void setup_safe() {
  if( !_safe ) {
    _safe = clone_object( ITEM_SHOP_ITEMS + "item_shop_safe" );
    _safe->set_difficulty( 2 + random( 7 ) );
    _safe->set_ownership( "shop" );
    if ( this_object()->query_hidden_safe( _safe ) ) {
        this_object()->add_hidden_object( _safe );
    } else {
        _safe->move( this_object() );
    }
  }
}
void set_safe(object safe) {
    _safe = safe;
    if ( _safe ) {
        _safe->set_ownership( "shop" );
        if ( this_object()->query_hidden_safe( _safe ) ) {
            this_object()->add_hidden_object( _safe );
        } else {
            _safe->move( this_object() );
        }
    }
}
void reset() {
  ::reset();
  if(!random(3)) {
    remove_property("inventory_loss");
  }
  do_banking();
}
mixed *switch_extra_properties(){
  return ({ TYPE, DISPLAY });
}
int query_shop() {
   return 1;
}
object *query_shop_lift_items(string str, object player) {
   return filter(match_objects_for_existence(str, ({ query_cont() })),
     (: query_num_items_left($1) > 0 :));
}
object shoplift_success(object ob) {
   object real_ob;
   real_ob = create_real_object(ob);
   return real_ob;
}
string query_shoplift_response_handler() { return _shoplift_handler; }
void set_shoplift_response_handler( string word ) { _shoplift_handler = word; }
void set_open_func(function func) {
   ::set_open_function(func);
}
void set_open_condition(function func) {
   ::set_open_function(func);
}
void set_buy_function(function func) {
  _buy_func = func;
}
function query_buy_function() {
   return _buy_func;
}
void set_browse_function(function func) {
  _browse_func = func;
}
function query_browse_function() {
   return _browse_func;
}
void set_list_function(function func) {
  _list_func = func;
}
function query_list_function() {
   return _list_func;
}
void set_sort_function(function func) {
   _sort_func = func;
}
function query_sort_function() {
   return _sort_func;
}
void set_no_steal(int i) { _no_steal = i; }
int query_no_steal() { return _no_steal; }
void set_steal_difficulty(int i) { _steal_difficulty = i; }
int query_steal_difficulty(int i) { return _steal_difficulty; }
void init() {
   if (query_cont()) {
      add_command( "list", "[all]" );
      add_command( "browse", "<indirect:object:"+file_name(query_cont())+">" );
      add_command( "browse", "<word>", (: do_word_browse($4[0]) :) );
      add_command( "buy", "<indirect:object:"+file_name(query_cont())+">" );
      add_command( "buy", "<word>", (: do_word_buy($4[0]) :) );
   }
}
private object find_object_from_number(int number) {
   object *things;
   things = all_inventory( query_cont() );
   if ( number >= sizeof( things ) ) {
      add_failed_mess( "There is no item with that label.\n" );
      return 0;
   }
   if (_sort_func) {
      things = sort_array(things, _sort_func);
   }
   return things[number];
}
private string letter_name(int letter,
                           object* things) {
   string bing;
   if (sizeof(things) > 26) {
      bing = "AA";
      bing[0] = 'A' + (letter / 26);
      bing[1] = 'A' + (letter % 26);
      return bing;
   }
   bing = "A";
   bing[0] = 'A' + letter;
   return bing;
}
private string start_letter() {
   object *things;
   things = all_inventory( query_cont() );
   return letter_name(0, things);
}
private string end_letter() {
   object *things;
   things = all_inventory( query_cont() );
   return letter_name(sizeof(things) - 1, things);
}
private int query_number_from_string(string name) {
   object *things;
   int pos;
   things = all_inventory( query_cont() );
   if (sizeof(things) > 26) {
      if (strlen(name) != 2) {
         return -1;
      }
      name = lower_case(name);
      if (name[0] < 'a' || name[0] > 'z') {
         return -1;
      }
      if (name[1] < 'a' || name[1] > 'z') {
         return -1;
      }
      pos = (name[0] - 'a') * 26 + name[1] - 'a';
      if (pos >= sizeof(things)) {
         return -1;
      }
      return pos;
   }
   if (strlen(name) != 1) {
      return -1;
   }
   name = lower_case(name);
   if (name[0] < 'a' || name[0] > 'z') {
      return -1;
   }
   pos = name[0] - 'a';
   if (pos >= sizeof(things)) {
      return -1;
   }
   return pos;
}
int query_cost( object thing ) {
   int cost;
   string place;
   if (!thing) {
      return 0;
   }
   if ( environment( thing ) == query_cont() ) {
      cost = (int)thing->query_property( "cost here" );
      if ( cost ) {
         return cost;
      }
   }
   cost = (int)thing->query_value_at( this_object() );
   place = query_property( "place" );
   if ( !place ) {
      return cost;
   }
   cost = (int)MONEY_HAND->query_total_value(
         (mixed *)MONEY_HAND->create_money_array( cost, place ), place );
   if ( environment( thing ) == query_cont() ) {
      thing->add_property( "cost here", cost );
   }
   return cost;
}
int do_list( string str ) {
   int i;
   int left;
   string list;
   string place;
   string display;
   object thing;
   object *listed;
   object *things;
   if (!is_open(this_player(), 0)) {
      if (!broadcast_shop_event(ITEM_SHOP_EVENT_CLOSE, this_player())) {
         add_failed_mess("The shop is not open.\n");
      }
      return 0;
   }
   listed = ({ });
   list = "";
   place = query_property( "place" );
   if ( !place || ( place == "" ) )  {
      place = "default";
   }
   if ( !query_cont() ) {
      if (!broadcast_shop_event(ITEM_SHOP_EVENT_NOTHING, this_player())) {
         add_failed_mess( "There is nothing to buy here.\n" );
      }
      return 0;
   }
   things = all_inventory( query_cont() );
   if (_sort_func) {
      things = sort_array(things, _sort_func);
   }
   foreach ( thing in things ) {
      left = query_num_items_left(thing);
      if (!left) {
         i++;
         continue;
      }
      display = (string)thing->query_property( DISPLAY );
      if ( !stringp( display )  && thing->short()) {
         display = (string)thing->a_short();
      }
      if (display) {
         list += "$I$6=   "+ letter_name(i, things) +": "+ display +" for "+
               (string)MONEY_HAND->money_value_string(
               (int)this_object()->query_cost( thing ), place );
         if ( left == INFINITE_LEFT ) {
            list += " (plenty left).$I$0=\n";
         } else {
            list += " (" + query_num( left, 0 ) +" left).\n";
         }
         listed += ({ thing });
      }
      i++;
   }
   if ( list == "" ) {
      if (!broadcast_shop_event(ITEM_SHOP_EVENT_NOTHING, this_player())) {
         add_failed_mess( "There is nothing to buy here.\n" );
      }
      return 0;
   }
   if (!broadcast_shop_event(ITEM_SHOP_EVENT_LIST, this_player(), list)) {
      list = "/global/events"->convert_message(list);
      write("$P$item list$P$" +
         "The following items are for sale:\n" + list);
      add_succeeded_mess(({ "", "$N list$s the inventory.\n" }), ({ }));
   }
   if (_list_func) {
      evaluate(_list_func, this_player(), listed);
   }
   return 1;
}
int do_word_buy(string str) {
   object thing;
   int i;
   if (!is_open(this_player(), 0)) {
      if (!broadcast_shop_event(ITEM_SHOP_EVENT_CLOSE, this_player())) {
         add_failed_mess("The shop is not open.\n");
      }
      return 0;
   }
   if ( strlen( str ) <= 2 ) {
      i = query_number_from_string( str );
      if ( i == -1) {
         if (!broadcast_shop_event(ITEM_SHOP_EVENT_BAD_LABEL, this_player(), str)) {
            add_failed_mess( "The item label must be from " +
                             start_letter() + " to " + end_letter() + ".\n" );
         }
         return 0;
      }
      thing = find_object_from_number(i);
      if ( !thing) {
         return 0;
      }
      return do_buy( ({ thing }) );
   }
   return 0;
}
int do_buy( object *things ) {
   int i, cost, value, ret, money_in_safe;
   string place;
   object thing, money, *sold, ob, *obs;
   mixed *money_arr, temp;
   if (!is_open(this_player(), 0)) {
      if (!broadcast_shop_event(ITEM_SHOP_EVENT_CLOSE, this_player())) {
         add_failed_mess("The shop is not open.\n");
      }
      return 0;
   }
   sold = ({ });
   for (i = 0; i < sizeof(things); i++) {
      if (query_num_items_left(things[i]) <= 0) {
         if (!broadcast_shop_event(ITEM_SHOP_EVENT_SOLD_OUT, this_player(), things[i..i])) {
            add_failed_mess( "The shop is sold out of "+
                  (string)things[ i ]->query_plural() +".\n" );
         }
         return 0;
      }
      place = query_property( "place" );
      if ( !place || ( place == "" ) ) {
         place = "default";
      }
      value = (int)this_player()->query_value_in( place );
      cost = (int)this_object()->query_cost( things[i] );
      if ( cost > value ) {
         if (!broadcast_shop_event(ITEM_SHOP_EVENT_TOO_EXPENSIVE, this_player(), things[i], cost, value)) {
            add_failed_mess("You cannot afford to buy $I.\n", ({ things[i] }));
         }
      } else {
        thing = create_real_object(things[i]);
        if (!thing){
          add_failed_mess( "Something is hosed.  Please file a bug "
                           "report.  Thank you.\n" );
          return 0;
        }
         ret = 1;
         this_player()->pay_money( (mixed *)MONEY_HAND->create_money_array(
               cost, place ), place );
         if( _safe ) {
           money_arr = MONEY_HAND->create_money_array( cost, place );
           money = clone_object( "/obj/money" );
           money->set_money_array( money_arr );
           money->move( _safe );
           _safe->set_closed();
           _safe->set_locked();
           obs = all_inventory( _safe );
           money_in_safe = 0;
           foreach( ob in obs ) {
             if( ob->query_property( "money" ) ) {
               temp = ob->query_money_array();
               money_in_safe += MONEY_HAND->query_total_value( temp, place );
             }
           }
           if( money_in_safe >= query_max_float() )
            do_banking();
         }
         if (!broadcast_shop_event(ITEM_SHOP_EVENT_BUY_THING, this_player(), thing)) {
            add_succeeded_mess("$N $V $I.\n", ({ thing }) );
         }
         this_object()->something_bought( thing, this_player(), cost );
         if ( query_property( "package items" ) ) {
            thing = (object)this_object()->package_item( thing );
         }
         if ( (int)thing->move( this_player() ) != MOVE_OK ) {
            thing->move( this_object() );
            write( "You cannot pick "+ (string)thing->a_short() +
                  " up.  It's left on the floor for you.\n" );
         }
         sold += ({ thing });
      }
   }
   if (_buy_func) {
      evaluate(_buy_func, this_player(), sold);
   }
   return ret;
}
int do_word_browse( string words ) {
   int i;
   object thing;
   if (!is_open(this_player(), 0)) {
      if (!broadcast_shop_event(ITEM_SHOP_EVENT_CLOSE, this_player())) {
         add_failed_mess("The shop is not open.\n");
      }
      return 0;
   }
   if ( strlen( words ) <= 2 ) {
      i = query_number_from_string( words );
      if ( i == -1) {
         if (!broadcast_shop_event(ITEM_SHOP_EVENT_BAD_LABEL, this_player(), words)) {
            add_failed_mess( "The item label must be from " +
                          start_letter() + " to " + end_letter() + ".\n" );
         }
         return 0;
      }
      thing = find_object_from_number(i);
      if ( !thing) {
         return 0;
      }
      return do_browse( ({ thing }) );
   }
   return 0;
}
int do_browse( object *things ) {
   int i;
   int num;
   string place;
   string mess;
   if (!is_open(this_player(), 0)) {
      if (!broadcast_shop_event(ITEM_SHOP_EVENT_CLOSE, this_player())) {
         add_failed_mess("The shop is not open.\n");
      }
      return 0;
   }
   place = query_property( "place" );
   if ( !place || ( place == "" ) ) {
      place = "default";
   }
   mess = "";
   for (i = 0; i < sizeof(things); i++) {
      if (query_num_items_left(things[i])) {
         mess += things[i]->the_short() +
                 " is priced at " + MONEY_HAND->money_value_string(
                 this_object()->query_cost( things[ i ] ), place ) +
                 " and looks like:\n" + things[ i ]->long();
         num++;
      }
   }
   if (!num) {
      if (!broadcast_shop_event(ITEM_SHOP_EVENT_SOLD_OUT, this_player(), things)) {
         add_failed_mess("The shop is sold out of $I.\n", things);
      }
      return 0;
   }
   if (!broadcast_shop_event(ITEM_SHOP_EVENT_BROWSE, this_player(), things, mess)) {
      write("$P$Browse things$P$" + mess);
      add_succeeded_mess(({ "", "$N $V $I.\n", }), things);
   }
   if (_browse_func) {
      evaluate(_browse_func, this_player(), things);
   }
   return 1;
}
void dest_me() {
  ::dest_me();
}
void event_theft( object command_ob, object thief, object victim,
  object *stolen ) {
  int stolen_from, difficulty;
  if( _safe ) {
    if( victim == _safe ) {
      stolen_from = _safe->query_property( "stolen from" );
      if( !stolen_from )
        _safe->add_property( "stolen from", 1 );
      else
        _safe->add_property( "stolen from", stolen_from + 1 );
      difficulty = _safe->query_difficulty();
      if( difficulty + 1 <= 10 )
        _safe->set_difficulty( difficulty + 2 );
      else
        if( difficulty <= 10 )
          _safe->set_difficulty( difficulty + 1 );
    }
  }
}
void event_shoplift(object command_ob, object thief, object victim) {
   if (stringp(_shoplift_handler)) {
     if(_shoplift_handler != "none" ) {
       _shoplift_handler->handle_shoplift(thief, victim);
     }
   } else {
     "/obj/handlers/theft_handler"->handle_shoplift(thief, victim);
   }
}
void do_banking() {
  object ob, *obs;
  debug_printf( "Doing banking.\n" );
  if( _safe ) {
    obs = all_inventory( _safe );
     foreach( ob in obs ) {
       if( ob->query_property( "money" ) ) {
         ob->move( "/room/rubbish" );
       }
     }
   }
}
void set_max_float( int f ) {
  _max_float = f;
}
int query_max_float() {
  return _max_float;
}