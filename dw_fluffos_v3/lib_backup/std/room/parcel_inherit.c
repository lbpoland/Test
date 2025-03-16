#include <money.h>
#include <mail.h>
#include <player_handler.h>
#include <player.h>
inherit "/std/room/basic_room";
string loc;
string where;
object shelf;
int cost;
varargs int do_deposit( object *obs, string name, int show_sender );
int do_collect();
void make_shelf( string short, string long ) {
  shelf = clone_object( "/std/surface" );
  shelf->set_name( short );
  shelf->set_long( long );
  shelf->set_max_weight( 10000 );
  shelf->move( this_object() );
  shelf->add_property( "there", "fixed to one wall" );
  shelf->reset_get();
}
void set_location( string _loc ) { loc = _loc; }
void set_cost( int _cost ) { cost = _cost; }
void set_currency( string temp ) { where = temp; }
string query_location() { return loc; }
int query_cost() { return cost; }
string query_currency() { return where; }
void init() {
    ::init();
  this_player()->add_command( "deposit", this_object(),
                  "<indirect:object> for <string>",
                  (: do_deposit( $1, $4[1] ) :) );
  this_player()->add_command( "collect", this_object(), "",
                  (: do_collect() :) );
}
int deposit_parcel( object *obs, string name, int show_sender ) {
  if ( obs == 0 || name == 0 ) {
    return 0;
  }
  if ( !PLAYER_HANDLER->test_user( name ) )  {
    return -2;
  }
  if ( !sizeof( obs ) ) {
    return 0;
  }
  if ( PLAYER_MULTIPLAYER_HANDLER->member_denied_parcel( this_player()->query_name() ) ) {
    return -4;
  }
  if ( PLAYER_MULTIPLAYER_HANDLER->member_denied_parcel( lower_case(name) ) ) {
    return -5;
  }
  MAIL_PARCEL_HANDLER->deposit( name, this_player()->query_name(),
                   loc, obs );
  AUTO_MAILER->auto_mail( name, "the parcel clerk",
       "Parcel Deposit Notification", "",
       "Please come to the " + loc + " Post Office parcel counter to\n"
       "collect " + ( sizeof( obs ) == 1 ? "a parcel which has" :
       query_num( sizeof( obs ) ) +" parcels which have" ) +
       " been deposited for you" +
       ( show_sender ? " by " + this_player()->query_short() : "" ) + ".\n\n"
       "Due to limited space in our warehouse you have two weeks to collect\n"
       "your parcels, if you do not collect them within this time they will\n"
       "will be destroyed.\n\n   The parcel clerk, " +
       loc + " Post Office.", 0, 0 );
  return 1;
}
varargs int do_deposit( object *obs, string name, int show_sender ) {
  int ret;
  int total_cost;
  object* total_obs;
  object ob;
  total_obs = obs;
  foreach (ob in obs) {
     total_obs += deep_inventory(ob);
  }
  if (sizeof(total_obs) > 20) {
     add_failed_mess("You are depositing too many items.  The maximum is "
                     "20.\n");
     return -6;
  }
  total_cost = cost * sizeof(total_obs);
  if ( this_player()->query_value_in( where ) < total_cost )  {
    add_failed_mess("You do not have enough money to deposit these "
                    "items, you need " +
                    MONEY_HAND->money_value_string(total_cost,
                            query_property("place")) + ".\n");
    return -1;
  }
  if ( lower_case(name) == this_player()->query_name() ) {
    add_failed_mess("You cannot deposit things for yourself!\n");
    return -3;
  }
  ret = deposit_parcel(obs, name, show_sender);
  switch (ret) {
  case 0 :
  case -1 :
  case -2 :
     return ret;
  case -3 :
    add_failed_mess("You cannot deposit things for yourself!\n");
    return -3;
  case -4 :
    add_failed_mess("You are not allowed to deposit parcels.\n");
    return -4;
  case -5 :
    add_failed_mess(upper_case(name)+" is not allowed to recieve parcels.\n");
    return -5;
  case 1 :
     this_player()->pay_money( (mixed *)MONEY_HAND->create_money_array(
                                total_cost, where ), where );
     return 1;
  }
  return ret;
}
int do_collect() {
  string this_player_name;
  this_player_name = lower_case(this_player()->query_name());
  if( PLAYER_MULTIPLAYER_HANDLER->member_denied_parcel(this_player_name) ) {
    add_failed_mess("You are not allowed to collect things.\n");
    return 0;
  }
  if ( !MAIL_PARCEL_HANDLER->collect( this_player()->query_name(), loc,
                        (shelf) ? shelf : this_object(), 0 ) ) {
    return 0;
  }
  return 1;
}
void set_shelf( object ob ) {
    shelf = ob;
}
object query_shelf() {
    return shelf;
}