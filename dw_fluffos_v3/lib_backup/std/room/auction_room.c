#include <money.h>
#include <move_failures.h>
#include <player_handler.h>
#include <mail.h>
#define COLOUR_ID "colour code"
#define AUCTION_PLAYER_NAME 0
#define AUCTION_PLAYER_BID 1
#define ERRNOSPACE -1
#define ERRBADPARM -2
#define ERRBADCBOB -3
#define ERROBNOMOVE -4
#define ERRGENFAIL -5
#define ERRNORECV -6
#define ERRRECVEMP -7
#define WARNUNDEST -8
#define WARNEXCL -9
#define WARNNOLOTS "NULL"
#define TCTP( x, y ) tell_creator( this_player(), x, y )
#define GECM( x ) "/global/events"->convert_message( x )
#define c_item class item
#define c_store class store
#define c_lot class lot
#define OPEN "open"
#define CLOSED "closed"
#define WAIT_SELLER "waitsell"
#define WAIT_BUYER "waitbuy"
#define WAIT_BUYER_LAPSE "waitbuylapse"
#define WAIT_CRE_INTERVENTION "waitcreint"
#define CHECK_CYCLE 10
#define COLOURS ({ "red", "orange", "yellow", "blue", "green", "indigo",\
  "violet", "crimson", "puce", "emerald", "ochre", "tangerine", "aquamarine",\
  "silver", "gold", "copper", "lilac" })
#define NO_COLOURS sizeof( COLOURS )
nosave inherit "/std/room";
inherit "/global/auto_load";
c_item {
  string name;
  string *alias;
  string *adjectives;
  string long;
  string read_mess;
  string enchant_mess;
}
c_store {
  int case_code;
  string colour;
  string inv_string;
  c_item *inventory;
}
c_lot {
  int case_code;
  c_store assoc_store;
  string seller;
  string status;
  int expiration_time;
  int reserve_price;
  mapping bids;
  mixed *lot_autoload;
  mixed *current_bid;
  string *auto_bids;
  string notes;
  string *excluded;
}
c_lot *lots = ({ });
mapping payments = ([ ]);
int lot_count = 0;
nosave string *used_colours = ({ });
nosave string currency = "default";
nosave string location = "unset";
nosave string shop_name = "REAS Auction Inheritable";
nosave int admin_cost = 2000;
nosave float commission = ( 5.0/100.0 );
mapping cases = ([ ]);
void save_file();
void load_file();
void set_location( string loc );
void set_currency( string cur );
void set_admin_cost( int value );
void set_commission( int percent );
void set_case_desc( string *bits );
mixed recover_lot( mixed lot_autoload );
int change_status( int lot_ident, string new_status );
void adjust_money( int amount, object player );
mixed generate_auto_load( object *obs );
c_store generate_store( object *things, int lot_id );
c_lot query_status( int lot_ident );
int do_deposit( object *things, int auction_time, string time_type,
  string res_price );
int do_bid( string offer, object *boxes );
int do_collect( string pattern );
int do_list();
int do_withdraw( object *boxes);
int do_describe( object *boxes, string int_desc );
int do_exclude( object *cases, string excluded );
int do_browse( object *cases, string target, int identifier );
int do_unexclude( object *cases, string excluded );
string generate_advertising_string( c_lot lot );
string generate_random_adv_str();
void create() {
    do_setup++;
    ::create();
    do_setup--;
    if ( !do_setup ) {
       this_object()->setup();
       this_object()->reset();
    }
    call_out( "load_file", 1 );
    call_out( "load_store", 2 );
    call_out( "lot_check", 5 );
}
void init() {
    this_player()->add_command( "bid", this_object(),
      "<string'amount'> {on|for} <indirect:object:here'case'>",
      (: do_bid( $4[0], $1 ) :) );
   this_player()->add_command( "collect", this_object(),
      ({ "successful bids", "money", "expired lots",
        "all" }),
      (: do_collect( $5 ) :) );
    this_player()->add_command( "deposit", this_object(),
      "<indirect:object:me'items'> for <number> "
      "{minute|hour|day} auction" ,
      (: do_deposit( $1, $4[1], $4[2], "" ) :) );
   this_player()->add_command( "deposit", this_object(),
      "<indirect:object:me'items'> for <number> "
      "{minute|hour|day} "
      "auction with [a] reserve price of <string'amount'>",
      (: do_deposit( $1, $4[1], $4[2], $4[3] ) :) );
    this_player()->add_command( "list", this_object(), "" );
   this_player()->add_command( "browse", this_object(),
       "<string'object'> in <indirect:object'case'>", (: do_browse( $1, $4[0], 0 ) :) );
    this_player()->add_command( "browse", this_object(),
       "<string'object'> <number> in <indirect:object'case'>",
       (: do_browse( $1, $4[0], $4[1] ) :) );
    this_player()->add_command( "withdraw", this_object(),
      "<indirect:object'case'> from auction",
      (: do_withdraw( $1 ) :) );
   this_player()->add_command( "write", this_object(),
      "<string'text'> on <indirect:object'case'>",
      (: do_describe( $1, $4[0] ) :) );
   this_player()->add_command( "exclude", this_object(),
      "<string'name'> from bidding on <indirect:object'case'>",
      (: do_exclude( $1, $4[0] ) :) );
   this_player()->add_command( "exclude", this_object(),
      "list for <indirect:object'case'>",
      (: do_exclude( $1, "list" ) :) );
   this_player()->add_command( "exclude", this_object(),
      "current ignore list from bidding on <indirect:object'case'>",
      (: do_exclude( $1, "ignore list" ) :) );
   this_player()->add_command( "unexclude", this_object(),
      "<string'name'> from bidding on <indirect:object'case'>",
      (: do_unexclude( $1, $4[0] ) :) );
}
int automated_deposit( object *things, int auction_length,
 string function_cb, string object_cb, int res_price,
  string int_desc ) {
  mixed *auto_load_string;
  c_lot temp;
  c_store temp2;
 if ( !sizeof( COLOURS - used_colours ) ) {
#ifdef DEBUG
   log_file( "REAS", "%s: ERRNOSPACE generated by: %s!\n", ctime( time() ),
             (previous_object()?file_name( previous_object()):"No previous object" ) );
#endif
    return ERRNOSPACE;
  }
  if ( !sizeof( things ) || auction_length < 0 ) {
#ifdef DEBUG
    log_file( "REAS", "%s: ERRBADPARM generated by: %s!\n", ctime( time() ),
      (previous_object()?file_name( previous_object()):"No previous object" ) );
#endif
    return ERRBADPARM;
  }
  if ( !objectp( load_object( object_cb ) ) ) {
#ifdef DEBUG
    log_file( "REAS", "%s: ERRBADCBOB generated by: %s!\n", ctime( time() ),
      (previous_object()?file_name( previous_object()):"No previous object" ) );
#endif
    return ERRBADCBOB;
  }
 lot_count ++;
  temp2 = generate_store( things, lot_count );
  auto_load_string = generate_auto_load( things );
  if ( !arrayp( auto_load_string ) ) {
   if ( (int) auto_load_string == ERROBNOMOVE ) {
#ifdef DEBUG
      log_file( "REAS", "%s: ERROBNOMOVE generated by: %s!\n", ctime( time() ),
        query_multiple_short( map( things, (: file_name( $1 ) :) ) ) );
#endif
      return ERROBNOMOVE;
    }
#ifdef DEBUG
    log_file( "REAS", "%s: ERRGENFAIL generated by: %s!\n", ctime( time() ),
      query_multiple_short( map( things, (: file_name( $1 ) :) ) ) );
#endif
    return ERRGENFAIL;
    }
   temp = new( c_lot, assoc_store: temp2, case_code: lot_count, seller: "Auto", status: OPEN,
      expiration_time: time() + auction_length, reserve_price: res_price,
      bids: ([ ]), current_bid: allocate( 2 ), lot_autoload: auto_load_string,
      auto_bids: ({ function_cb, object_cb }), notes: int_desc, excluded: ({ }) );
    lots += ({ temp });
   return lot_count;
}
mixed generate_auto_load( object *obs ) {
 object box = clone_object( "/obj/baggage" );
string *temp;
  box->set_name( "box" );
  box->set_long( "This is a box used in the auction room inheritable. "
    "How did you get hold of one?\n" );
  box->set_weight( 500000 );
  box->set_max_weight( 500000 );
  box->set_volume( 500000 );
 if ( sizeof( filter( obs->move( box ), (: $1 != 0 :) ) ) )
   return ERROBNOMOVE;
  temp = create_auto_load( ({ box }), 0 );
  if ( !arrayp( temp ) )
  return ERRGENFAIL;
   obs->dest_me();
   obs -= ({ 0 });
   if ( sizeof( obs ) ) {
#ifdef DEBUG
     log_file( "REAS", "%s: WARNUNDEST generated by object %s.\n", ctime( time() ),
     query_multiple_short( map( obs, (: file_name( $1 ) :) ) ) );
#endif
   }
   box->dest_me();
   return temp;
}
c_store generate_store( object *things, int lot_id ) {
  c_store temp;
  c_item temp2;
  object temp3;
  string *avail_colours = COLOURS - used_colours;
  string _colour = avail_colours[ random( sizeof( avail_colours ) ) ];
  temp = new( c_store, case_code: lot_id, colour: _colour,
    inventory: ({ }), inv_string: GECM( query_multiple_short( things ) ) );
    used_colours += ({ _colour });
  foreach( temp3 in things ) {
    temp2 = new( c_item, name: temp3->query_name(),
    alias: temp3->query_alias(), long: temp3->query_long(),
    read_mess: temp3->query_readable_message(), enchant_mess:
    temp3->enchant_string(), adjectives: temp3->query_adjectives() );
    temp->inventory += ({ temp2 });
    if ( !stringp( temp2->read_mess ) )
      temp2->read_mess = "";
  }
 return temp;
}
void lot_check() {
  c_lot temp_lot;
  c_store current_store;
  object new_case;
  object *all_new_cases = ({ });
  object *obs;
  object *exp_cases;
  int *active_lots;
  string name;
  int *bids;
  cases = filter( cases, (: objectp( $1 ) :) );
  active_lots = map( filter( lots, (: ( (c_lot) $1)->status == OPEN :) ),
   (: ( (c_lot) $1)->case_code :) );
  if ( sizeof( cases ) < sizeof( active_lots ) ) {
    active_lots = active_lots - values( cases );
    foreach( int temp in active_lots ) {
      temp_lot = filter( lots, (: $1->case_code == $(temp) :) )[0];
      current_store = temp_lot->assoc_store;
      new_case = clone_object( "/std/object" );
      new_case->set_name( "case" );
      new_case->set_short( current_store->colour + " case" );
      new_case->set_long( "This is a display case used in this auction shop. "
        "It contains " + current_store->inv_string +".\nYou can \"browse\" these"
        " items.\n" );
      new_case->add_adjective( current_store->colour );
      new_case->move( this_object() );
      new_case->reset_get();
      new_case->add_extra_look( this_object() );
      used_colours += ({ current_store->colour });
      cases += ([ new_case: temp ]);
      all_new_cases += ({ new_case });
    }
    if ( sizeof( all_new_cases ) )
      this_object()->add_new_case( all_new_cases );
  }
  foreach( temp_lot in ( filter( lots, (: $1->expiration_time < time() :) ) ) ) {
    TCTP( "Looking at lot %d. ", temp_lot->case_code );
    TCTP( "Status is: %s\n", temp_lot->status );
    switch( temp_lot->status ) {
      case OPEN:
      TCTP( "In open %s", "\n" );
        current_store = temp_lot->assoc_store;
        exp_cases = filter( cases, (: $2 == $(temp_lot)->case_code :) );
        map( exp_cases, (: this_object()->remove_lot( $1 ) :) );
        if ( sizeof( temp_lot->auto_bids ) ) {
          obs = recover_lot( temp_lot->lot_autoload );
          call_other( temp_lot->auto_bids[1], temp_lot->auto_bids[0],
          temp_lot->case_code, stringp( temp_lot->current_bid[ AUCTION_PLAYER_NAME ] ),
          temp_lot->current_bid[ AUCTION_PLAYER_NAME ],
          temp_lot->current_bid[ AUCTION_PLAYER_BID ], obs );
          temp_lot->status = CLOSED;
          temp_lot->expiration_time = time() + ( 2 * 60 * 60 );
          continue;
        }
        if ( stringp( name = temp_lot->current_bid[ AUCTION_PLAYER_NAME ] ) ) {
          if ( PLAYER_HANDLER->test_user( name ) ) {
            AUTO_MAILER->auto_mail( name, shop_name, "Your successful purchase!",
            "","Congratulations! You have successfully purchased "+
            current_store->inv_string +" with a bid of "
            + MONEY_HAND->money_value_string( temp_lot->current_bid[ AUCTION_PLAYER_BID ],
            currency )+ ".\n\nYou have one week to collect your items before they are "
            "forfeit.\n", 0, 0 );
          }
          temp_lot->status = WAIT_BUYER;
          temp_lot->expiration_time = time() + ( 7 * 24 * 60 * 60 );
          continue;
        }
        case WAIT_BUYER_LAPSE:
        name = temp_lot->seller;
        if (PLAYER_HANDLER->test_user( name ) ) {
          AUTO_MAILER->auto_mail( name, shop_name, "Your unsuccessful sale!",
          "", "Dear "+ capitalize( name ) +",\n\nIt is with some regret that I inform you "
          "that we were unable to sell " + current_store->inv_string +
          ".\n\nYou have one week to collect your items before they are forfeit.\n",
          0, 0 );
        }
        temp_lot->status = WAIT_SELLER;
        temp_lot->expiration_time = time() + ( 7 * 24 * 60 * 60 );
        continue;
      case WAIT_SELLER:
        name = temp_lot->seller;
        if ( PLAYER_HANDLER->test_user( name ) ) {
          AUTO_MAILER->auto_mail( name, shop_name, "Your unsuccessful sale!",
          "", "Dear "+ name +",\n\nAs you have not collected your items within "
          "7 days, they have been disposed of.\n\nHave a nice day.\n",
         0, 0 );
        }
        temp_lot->status = CLOSED;
        temp_lot->expiration_time = time() + ( 2 * 60 * 60 );
        continue;
    case WAIT_BUYER:
      name = temp_lot->current_bid[ AUCTION_PLAYER_NAME ];
      if ( PLAYER_HANDLER->test_user( name ) ) {
        AUTO_MAILER->auto_mail( name, shop_name, "Your successful purchase!",
        "","Dear " + name +",\nBecause you have not picked up your items, "+
        "they have been sold to another client.\n\nHave a nice day.", 0, 0 );
      }
      map_delete( temp_lot->bids, name );
      if ( sizeof( temp_lot->bids ) == 0 ) {
        temp_lot->status = WAIT_BUYER_LAPSE;
        temp_lot->expiration_time = time() + ( 2 * 60 * 60 );
        continue;
      }
      bids = sort_array( values( temp_lot->bids ), -1 );
      TCTP( "bids is %O.\n", bids );
      name = filter( temp_lot->bids, (: $2 == $(bids[0]) :) );
      temp_lot->current_bid[ AUCTION_PLAYER_NAME ] = name;
      temp_lot->current_bid[ AUCTION_PLAYER_BID ] = bids[0];
      if ( PLAYER_HANDLER->test_user( name ) ) {
        AUTO_MAILER->auto_mail( name, shop_name, "Your successful purchase!",
        "","Congratulations! You have successfully purchased "+
        current_store->inv_string +" with a bid of "
        + MONEY_HAND->money_value_string( temp_lot->current_bid[ AUCTION_PLAYER_BID ],
        currency )+ ".\n\nYou have one week to collect your items before they are "
        "forfeit.\n", 0, 0 );
      }
      temp_lot->status = WAIT_BUYER;
      temp_lot->expiration_time = time() + ( 7 * 24 * 60 * 60 );
      continue;
    case WAIT_CRE_INTERVENTION:
#ifdef DEBUG
      log_file("REAS", "%s: Lot %d is still waiting for manual intervention!\n",
        ctime( time() ), temp_lot->case_code );
#endif
      temp_lot->expiration_time = time() + ( 7 * 24 * 60 * 60 );
      continue;
      case CLOSED:
        TCTP( "In closed %s", "" );
        lots -= ({ temp_lot });
#ifdef DEBUG
        log_file( "REAS", "%s: Closed lot %d\n", ctime( time() ), temp_lot->case_code );
#endif
        continue;
    }
  }
  call_out( "lot_check", CHECK_CYCLE );
  return ;
}
int do_deposit( object *things, int auction_time, string time_type, string res_price ) {
  mixed *auto_load_string;
  c_lot temp;
  c_store temp2;
 int value;
  int finishtime;
 if ( auction_time <= 0 || ( time_type == "day" && auction_time > 10 )
    || ( time_type == "minute" && auction_time > 59 ) ||
    ( time_type == "hour" && auction_time > 23 ) ) {
      this_player()->add_failed_mess( this_object(),
        "That's not a valid length.\n" );
      return 0;
  }
  if ( sizeof( res_price ) ) {
   value = MONEY_HAND->value_from_string( res_price, currency );
    if ( value == 0 ) {
      this_player()->add_failed_mess( this_object(),
        res_price +" isn't a valid reserve price.\n" );
      return 0;
    }
  }
 if ( !sizeof( COLOURS - used_colours ) ) {
    this_player()->add_failed_mess( this_object(), "The auction house "
      "doesn't have any display cases left to auction your item.\n" );
    return 0;
  }
  switch( time_type ) {
    case "minute":
      if ( auction_time < 5 ) {
        this_player()->add_failed_mess( this_object(),
          "Auctions must go for at least 5 minutes.\n" );
        return 0;
      }
      finishtime = time() + ( auction_time * 60 );
      break;
    case "hour":
       finishtime = time() + ( auction_time * 60 * 60 );
       break;
    case "day":
      if ( auction_time > 14 ) {
        this_player()->add_failed_mess( this_object(),
          "Auction can not go for longer then two weeks.\n" );
        return 0;
      }
      finishtime = time() + ( auction_time * 60 * 60 * 24 );
      break;
    default:
       return 0;
 }
  foreach( object tmp in things ) {
    if ( base_name( tmp ) == "/obj/money.c" ) {
      this_player()->add_failed_mess( this_player(), "You can't auction money.\n" );
      things->move( this_player(), "" );
      filter( things, (: environment( $1 ) != this_player() :) )->
        move( environment( this_player() ),  "$N falls to the floor!\n" );
      return 0;
    }
  }
  lot_count ++;
  temp2 = generate_store( things, lot_count );
  auto_load_string = generate_auto_load( things );
  if ( !arrayp( auto_load_string ) ) {
    this_player()->add_failed_mess( this_player(), "You can't auction that.\n" );
    things->move( this_player(), "" );
    filter( things, (: environment( $1 ) != this_player() :) )->
      move( environment( this_player() ),  "$N falls to the floor!\n" );
    return 0;
 }
  temp = new( c_lot, assoc_store: temp2, case_code: lot_count, seller: this_player()->query_name(),
    status: OPEN, expiration_time: finishtime, reserve_price: value,
    bids: ([ ]), current_bid: allocate( 2 ), lot_autoload: auto_load_string,
    auto_bids: ({ }), notes: "", excluded: ({ }) );
  lots += ({ temp });
 if ( strlen( res_price ) )
    this_player()->add_succeeded_mess( this_object(), "$N $V "+
    temp2->inv_string + " for "+ add_a( query_num( auction_time, 5000 ) ) +
    " " + time_type + " auction, with a reserve price of "+
      MONEY_HAND->money_value_string( value, currency ) +".\n" );
  else
    this_player()->add_succeeded_mess( this_object(), "$N $V "+
    temp2->inv_string +" for a "+ query_num( auction_time, 5000 ) +
    " " + time_type + " auction, with no reserve price.\n" );
    TCTP( "Generated lot %d.\n", lot_count );
    return 1;
}
int do_list() {
  c_lot *_lots;
  c_lot _lot;
  string str;
  if ( !sizeof( cases ) ) {
    write( "There is nothing up for auction in this store.\n" );
    return 1;
  }
  str = "Items currently for auction:\n" ;
  foreach( object _case in keys( cases ) ) {
    _lots = filter( lots, (: $1->case_code == $( cases[ _case ] ) :) );
    if ( !sizeof( _lots ) ) continue;
    _lot = _lots[0];
    str +=  "$I$6=   " +
      capitalize( _lot->assoc_store->colour + " case" ) + ": " +
      _lot->assoc_store->inv_string;
    if (_lot->current_bid[AUCTION_PLAYER_NAME]) {
       str += "; bid: "+ MONEY_HAND->money_value_string(
        _lot->current_bid[1], currency ) + ", by " +
        capitalize(_lot->current_bid[ AUCTION_PLAYER_NAME ] ) +".\n";
    } else {
       str += ", no bid yet.\n";
    }
  }
  write("$P$Auctions$P$" + str);
  return 1;
}
void remove_lot( object ob ) {
  if ( member_array( ob, keys( cases ) ) == -1 )  {
    return;
  }
  map_delete( cases, ob );
  ob->dest_me();
  return;
}
int do_bid( string offer, object *boxes ) {
c_lot temp;
c_lot *temps;
c_store temp2;
object box;
int value;
 if ( sizeof( boxes ) > 1 ) {
    this_player()->add_failed_mess( this_object(),
      "You can only $V on one case at "
      "a time.\n" );
    return 0;
  }
  box = boxes[0];
  if ( member_array( box, keys( cases ) ) == -1 ) {
    this_player()->add_failed_mess( this_object(),
      "$I isn't being auctioned here.\n", ({ box }) );
    return 0;
  }
  temps = filter_array( lots, (: $1->case_code == cases[ $(box) ] :) );
  temp = temps[0];
  temp2 = temp->assoc_store;
  if ( temp->status != OPEN ) {
    this_player()->add_failed_mess(this_object(),
      "The bidding on this item is finished.\n" );
    return 0;
  }
  if ( member_array( this_player()->query_name(),
       temp->excluded ) != -1 ) {
    write( "You have been excluded from bidding on this object.\n" );
    return WARNEXCL;
  }
  if ( !classp( temp2 ) ) {
#ifdef DEBUG
    log_file( "REAS", "%s: Open lot without store! Lot code: %d.\n",
      ctime( time() ), temp->case_code );
#endif
    write( "Something has gone wrong. Please fetch a liaison post haste!\n" );
    printf( "Your lot code is: %d.\n", temp->case_code );
    temp->status = WAIT_CRE_INTERVENTION;
    temp->expiration_time = time() + ( 7 * 24 * 60 * 60 );
    this_player()->add_succeeded_mess( this_object(), "" );
    return 1;
  }
  value = MONEY_HAND->value_from_string( offer, currency );
  if ( value == 0 ) {
        this_player()->add_failed_mess( this_object(),
          offer +" isn't worth anything here.\n" );
        return 0;
  }
 if ( this_player()->query_value_in( currency ) < value ) {
   this_player()->add_failed_mess( this_object(), "You don't "
     "have that much.\n" );
   return 0;
 }
 if ( temp->reserve_price != 0 && value < temp->reserve_price ) {
   this_player()->add_failed_mess( this_object(),
     "The reserve price for this lot is "+
     MONEY_HAND->money_value_string( temp->reserve_price, currency ) +".\n" );
     return 0;
 }
  if ( value < 400 ) {
   this_player()->add_failed_mess( this_object(),
     "You must bid at least "+
     MONEY_HAND->money_value_string( 400, currency ) + ".\n" );
     return 0;
 }
 if ( sizeof( temp->current_bid ) &&
   temp->current_bid[ AUCTION_PLAYER_BID ] >= value ) {
   this_player()->add_failed_mess(this_object(),
     "Someone else has already bid more than that.\n");
   return 0;
 }
 if ( sizeof( temp->current_bid ) &&
   ( ( value - temp->current_bid[ AUCTION_PLAYER_BID ] ) <
     ( temp->current_bid[ AUCTION_PLAYER_BID ] / 20 ) ) ) {
     this_player()->add_failed_mess( this_object(), "You must bid 5% "
     "more then the current bid.\n" );
   return 0;
 }
 temp->bids[ this_player()->query_name() ] = value;
 temp->current_bid[0] = this_player()->query_name();
 temp->current_bid[1] = value;
 this_player()->add_succeeded_mess(this_object(),
   "$N $V "+ offer +" for "+ temp2->inv_string +".\n" );
 return 1;
}
int do_browse( object *boxes, string target, int identifier ) {
object box;
c_store container;
c_item temp;
mapping contents = ([ ]);
string *names = ({ });
mixed *longadj = ({ });
string temp2;
mixed *contenders;
string *contender;
string *adjectives;
string name;
string word;
int keep_flag;
 if ( sizeof( boxes ) > 1 ) {
    this_player()->add_failed_mess( this_object(),
      "You can only $V one case at a time.\n" );
    return 0;
  }
  box = boxes[0];
 if ( member_array( box, keys( cases ) ) == -1 ) {
    this_player()->add_failed_mess( this_object(),
      "$I isn't being auctioned here.\n", ({ box }) );
    return 0;
  }
  container = filter( lots, (: $1->case_code == cases[ $(box) ] :) )[ 0 ]->assoc_store;
  TCTP( "The case code for this case is: %d.\n", container->case_code );
  foreach( temp in container->inventory ) {
    names = temp->alias + ({ temp->name });
    names = uniq_array( names );
    longadj = ({ temp->long + temp->read_mess +
      ( this_player()->query_see_octarine() ? temp->enchant_mess : "" ),
      temp->adjectives });
    foreach( temp2 in names ) {
      if ( arrayp( contents[ temp2 ] ) )
        contents[ temp2 ] += ({ longadj });
      else
        contents[ temp2 ] = ({ longadj });
    }
  }
  adjectives = explode( target, " " );
    name = adjectives[ sizeof( adjectives ) - 1 ];
    adjectives -= ({ name });
  TCTP( "Search Name: %s ", name );
  TCTP( "Search Adj: %O.\n", adjectives );
  if ( !arrayp( contents[ name ] ) ) {
    this_player()->add_failed_mess( this_object(),
      "There is nothing like that in the case.\n" );
    return 0;
 }
  contenders = contents[ name ];
  if ( sizeof( contenders ) == 1 ) {
    contender = contenders[0];
    this_player()->add_succeeded_mess( this_player(),
     "$N $V "+ target +" in $I.\n", ({ box }) );
    call_out( (: tell_object( this_player(),
      $(GECM( contender[0]) ) ) :) );
    return 1;
  }
  if ( identifier != 0 ) {
    if ( identifier > sizeof( contenders ) ) {
     this_player()->add_failed_mess( this_player(),
        "There are only " + sizeof( contenders ) +
        " " + pluralize( target ) + " in $I.\n", ({ box }) );
       return 0;
      }
    this_player()->add_succeeded_mess( this_player(),
      "$N $V "+ add_a( target ) +" in $I.\n", ({ box }) );
    call_out( (: tell_object( this_player(),
      GECM( $(contenders[ identifier - 1 ][0]) ) ) :), 0 );
    return 1;
  }
  if ( !sizeof( adjectives ) ) {
    this_player()->add_failed_mess( this_object(),
      "There are "+ sizeof( contenders ) +" objects like that in the case.\n" );
    return 0;
 }
  foreach ( contender in contenders ) {
    keep_flag = 0;
    foreach( word in contender[ 1 ] ) {
      if ( member_array( word, adjectives ) != -1 )
        keep_flag = 0;
      continue;
    }
    if ( !keep_flag )
      contenders -= ({ contender });
    continue;
  }
  if ( !sizeof( contenders ) ) {
    this_player()->add_failed_mess( this_object(),
      "There is nothing matching "+ target +" in the case.\n" );
    return 0;
  }
  if ( sizeof( contenders ) > 1 ) {
     this_player()->add_failed_mess( this_object(),
       "There are " + sizeof( contenders ) + " items like that in the case. "
       "Please specify which one you want to browse.\n" );
     return 0;
  }
  contender = contenders[0];
  this_player()->add_succeeded_mess( this_player(),
    "$N peruse "+ add_a( target ) +" in $I.\n", ({ box }) );
  call_out( (: tell_object( this_player(),
    GECM( $(contender[0]) ) ) :), 0 );
  return 1;
}
void adjust_money( int amount, object player ) {
    object money;
    if ( amount < 0 ) {
        player->pay_money(MONEY_HAND->create_money_array(-amount, currency ));
        return;
    }
    money = MONEY_HAND->create_money_array( amount, currency );
    player->adjust_money( money, currency );
}
void load_file() {
    if ( !stringp( location ) ) return;
    if ( file_size( location +".o" ) < 0 ) return;
    unguarded( (: restore_object, location :) );
    return;
}
void save_file() {
    if ( location == "unset" ) return;
    unguarded( (: save_object, location :) );
    return;
}
void set_shop_name( string _name ) { shop_name = _name; }
void set_save_path( string path ) { location = path; }
void set_currency( string cur ) { currency = cur; }
void set_admin_cost( int value ) { admin_cost = value; }
void set_commission( int percent ) { commission = percent/100.0; }
mapping query_payments() { return payments; }
void dest_me() {
    save_file();
    if ( sizeof( cases ) ) keys( cases )->dest_me();
    ::dest_me();
}
mixed recover_lot( mixed lot_autoload ) {
  object *boxes;
  object *stuff;
  boxes = load_auto_load_to_array( lot_autoload, this_player() );
  if ( !objectp( boxes[0] ) ) {
#ifdef DEBUG
    log_file( "REAS", "%s: Could not recover: %O.\n", ctime( time() ),
      lot_autoload );
#endif
    return ERRNORECV;
  }
  stuff = all_inventory( boxes[ 0 ] );
  if ( !sizeof( stuff ) ) {
#ifdef DEBUG
    log_file( "REAS", "%s: Recovered case as empty: %O.\n", ctime( time() ),
      lot_autoload );
#endif
    return ERRRECVEMP;
  }
  call_out( (: $(boxes)->dest_me() :), 5 );
  return stuff;
}
int do_withdraw( object *boxes ) {
object box;
c_lot *_lots;
object *obs;
  if ( sizeof( boxes ) > 1  ) {
    this_player()->add_failed_mess( this_object(),
      "You can only $V on one case at "
      "a time.\n" );
      return 0;
  }
  box = boxes[0];
  if ( member_array( box, keys( cases ) ) == -1 ) {
    this_player()->add_failed_mess( this_object(),
      "$I isn't being auctioned here.\n", boxes );
    return 0;
  }
  _lots = filter( lots, (: $1->case_code == cases[ $(box) ] :) );
  if ( this_player()->query_name() != _lots[0]->seller &&
    !this_player()->query_creator() ) {
     this_player()->add_failed_mess( this_player(), "This isn't your "
       "lot to withdraw!\n" );
     return 0;
  }
  _lots[0]->status = CLOSED;
  _lots[0]->expiration_time = time() + ( 2 * 60 * 60 );
  obs = recover_lot( _lots[0]->lot_autoload );
  if ( !arrayp( obs ) ) {
    write( "Something has gone wrong. Please fetch a liaison post haste!\n" );
    printf( "Your lot code is: %d.\n", _lots[0]->case_code );
    _lots[0]->status = WAIT_CRE_INTERVENTION;
    _lots[0]->expiration_time = time() + ( 7 * 24 * 60 * 60 );
    this_player()->add_succeeded_mess( this_object(), "" );
    return 1;
  }
  obs->move( this_player(), "You collect $N." );
  filter( obs, (: environment( $1 ) != this_player() :) )->
    move( environment( this_player() ), "$N falls to the floor!\n" );
  this_object()->remove_lot( box );
  this_player()->add_succeeded_mess( this_object(), "" );
  return 1;
}
int do_describe( object *boxes, string int_desc ) {
    object box;
    c_lot *_lots;
    c_lot  _lot;
    int code;
    if ( sizeof( boxes ) > 1 ) {
        this_player()->add_failed_mess( this_object(),
          "You can only $V on one case at "
          "a time.\n" );
        return 0;
    }
    box = boxes[0];
    if ( member_array( box, keys( cases ) ) == -1 ) {
        this_player()->add_failed_mess( this_object(),
          "$I isn't being auctioned here.\n",
          ({ box }) );
        return 0;
    }
    code = cases[ box ];
    _lots = filter( lots, (: $1->case_code == $(code) :) );
    if ( sizeof( _lots ) != 1 ) {
        printf( "Please inform a creator, there are %d records to "
          "match this case.\n", sizeof( _lots ) );
        printf( "Your lot code is: %d.\n", code );
        this_player()->add_succeeded_mess( this_object(), "" );
        return 1;
    }
    _lot = _lots[0];
    if ( this_player()->query_name() != _lot->seller &&
      !this_player()->query_creator() ) {
        this_player()->add_failed_mess( this_player(), "This isn't your "
          "lot to describe!\n" );
        return 0;
    }
    _lot->notes = int_desc;
    printf( "You neatly letter %s on the case.\n", int_desc );
    this_player()->add_succeeded_mess( this_object(), "" );
    return 1;
}
string extra_look( object ob ) {
    c_lot temp, *temp2;
    mixed bid_info;
    string ret;
    int code;
    if ( member_array( ob, keys( cases ) ) == -1 ) return "";
    code = cases[ ob ];
    temp2 = filter( lots, (: $1->case_code == $(code) :) );
    if ( sizeof( temp2 ) != 1 ) return sizeof( temp2 ) +" found in lot array!\n";
    temp = temp2[0];
    bid_info = temp->current_bid;
    ret = "";
    if ( !stringp( bid_info[ AUCTION_PLAYER_NAME ] ) ) {
        if ( temp->reserve_price ) {
          ret += "Reserve price is: ";
          ret += MONEY_HAND->money_value_string( temp->reserve_price, currency );
          ret += ".\n";
        }
        else
            ret += "No bid as of yet.\n";
    }
    else
      ret += "The current bid is "+ MONEY_HAND->money_value_string(
        bid_info[1], currency ) + ", made by "+ capitalize(
        bid_info[ AUCTION_PLAYER_NAME ] ) +".\n";
    ret += "The bidding on this lot stops at "+ amtime( temp->expiration_time )+
      ".\n";
    if ( sizeof( temp->notes ) ) {
      ret += "Neatly lettered on the case is: ";
      ret += temp->notes;
      ret += ".\n";
    }
    return ret;
}
int do_collect( string pattern ) {
    int amount;
    c_lot _lot, *_lots = ({ }), *_exp_lots;
    object *items = ({ });
    _exp_lots = filter( lots, (: ((c_lot)$1)->status != OPEN :) );
    _exp_lots = filter( _exp_lots, (: ((c_lot)$1)->status != CLOSED :) );
    _exp_lots = filter( _exp_lots, (: ((c_lot)$1)->status != WAIT_CRE_INTERVENTION :) );
    if ( pattern == "all" ) {
        do_collect( "money" );
        do_collect( "successful bids" );
        do_collect( "expired lots" );
        return 1;
    }
    if ( pattern == "money" ) {
      _lots = filter( lots, (: ( $1->seller == $2 ) &&
        ( stringp( $1->current_bid[ AUCTION_PLAYER_NAME ] ) ) :),
        this_player()->query_name() );
      if ( undefinedp( payments[ this_player()->query_name() ] ) ) {
        if ( sizeof( _lots ) ) {
          foreach( c_lot tempy in _lots ) {
            write( capitalize( tempy->current_bid[ AUCTION_PLAYER_NAME ] ) +
              " must pay for the items they bid on before you can collect "
              "the money for them! They have until "+ amtime( tempy->expiration_time )+".\n" );
            }
       }
      }
      if ( undefinedp( payments[ this_player()->query_name() ] ) ) {
        write( "You aren't owed any money!\n" );
        return 0;
      }
      amount = payments[ this_player()->query_name() ];
      adjust_money( amount - to_int( amount * commission ), this_player() );
      printf( "You recieve %s, minus %s commission.\n",
        MONEY_HAND->money_value_string( amount, currency ),
        MONEY_HAND->money_value_string( to_int( amount * commission ),
        currency ) );
      map_delete( payments, this_player()->query_name() );
      this_player()->add_succeeded_mess( this_object(),
        "$N $V some money from $D.\n" );
      save_file();
      return 1;
    }
    if ( pattern == "successful bids" ) {
        _lots = filter( _exp_lots,
          (: $1->current_bid[ AUCTION_PLAYER_NAME ] == $2 :),
          this_player()->query_name() );
        if ( !sizeof( _lots ) ) {
            write( "You aren't expecting any bids!\n" );
            return 0;
        }
        foreach( _lot in _lots )
          amount += _lot->current_bid[ 1 ];
        if ( this_player()->query_value_in( currency ) < amount ) {
            printf( "You have %d %s waiting, for a total cost of %s.\n"
              "You don't have enough money.\n",
              sizeof( _lots ),
              sizeof( _lots ) > 1 ? "lots" : "lot",
              MONEY_HAND->money_value_string( amount, currency ) );
            this_player()->add_failed_mess( this_object(), "" );
            return 0;
        }
        adjust_money( -amount, this_player() );
        foreach( _lot in _lots ) {
          items += recover_lot( _lot->lot_autoload );
          if ( undefinedp( payments[ _lot->seller ] ) )
            payments[ _lot->seller ] = _lot->current_bid[ AUCTION_PLAYER_BID ];
          else
            payments[ _lot->seller ] += _lot->current_bid[ AUCTION_PLAYER_BID ];
          _lot->status = CLOSED;
          _lot->expiration_time = time() + ( 2 * 60 * 60 );
        }
        items->move( this_player(), "You collect $N." );
        filter( items, (: environment( $1 ) != this_player() :) )->
          move( environment( this_player() ), "$N falls to the floor!\n" );
        printf( "You had %d %s waiting, for a total cost of %s.\nYou "
          "hand over the money.\n", sizeof( _lots ),
          sizeof( _lots ) > 1 ? "lots" : "lot",
          MONEY_HAND->money_value_string( amount, currency ) );
        return 1;
    }
    if ( pattern == "expired lots" ) {
        _lots = filter( _exp_lots,
          (: !stringp( $1->current_bid[ AUCTION_PLAYER_NAME ] ) &&
            $1->seller == $2 :), this_player()->query_name() );
        if ( !sizeof( _lots ) ) {
            this_player()->add_failed_mess( this_object(), "You aren't expecting "
              "any items.\n" );
            return 0;
        }
        amount = admin_cost * sizeof( _lots );
        if ( this_player()->query_value_in( currency ) < amount ) {
            printf( "You have %d %s waiting, for a total administration "
              "cost of %s.\n"
              "You don't have enough money.\n",
              sizeof( _lots ),
              sizeof( _lots ) > 1 ? "lots" : "lot",
              MONEY_HAND->money_value_string( amount, currency ) );
            return 0;
        }
        adjust_money( -amount, this_player() );
        foreach( _lot in _lots ) {
          items += recover_lot( _lot->lot_autoload );
          if ( undefinedp( payments[ _lot->seller ] ) )
            payments[ _lot->seller ] = _lot->current_bid[ AUCTION_PLAYER_BID ];
          else
            payments[ _lot->seller ] += _lot->current_bid[ AUCTION_PLAYER_BID ];
          _lot->status = CLOSED;
          _lot->expiration_time = time() + ( 2 * 60 * 60 );
        }
        items->move( this_player(), "You collect $N." );
        filter( items, (: environment( $1 ) != this_player() :) )->
          move( environment( this_player() ), "$N falls to the floor!\n" );
        printf( "You had %d %s waiting, for a total administration "
          "cost of %s.\n"
          "You hand over the money.\n",
          sizeof( _lots ), sizeof( _lots ) > 1 ?
          "lots" : "lot",
          MONEY_HAND->money_value_string( amount, currency ) );
        return 1;
    }
}
int do_exclude( object *boxes, string excluded ) {
    object box;
    c_lot *_lots;
    c_lot  _lot;
    int code;
    string *ignored = this_player()->query_property( "ignoring" );
    if ( sizeof( boxes ) > 1 ) {
        this_player()->add_failed_mess( this_object(),
          "You can only $V people from one case at "
          "a time.\n" );
        return 0;
    }
    box = boxes[0];
    if ( member_array( box, keys( cases ) ) == -1 ) {
        this_player()->add_failed_mess( this_object(),
          "$I isn't being auctioned here.\n",
          ({ box }) );
        return 0;
    }
    code = cases[ box ];
    _lots = filter( lots, (: $1->case_code == $(code) :) );
    if ( sizeof( _lots ) != 1 ) {
        printf( "Please inform a creator, there are %d records to "
          "match this case.\n", sizeof( _lots ) );
        printf( "Your lot code is: %d.\n", code );
        this_player()->add_succeeded_mess( this_object(), "" );
        return 1;
    }
    _lot = _lots[0];
    if ( this_player()->query_name() != _lot->seller &&
      !this_player()->query_creator() ) {
        this_player()->add_failed_mess( this_player(), "This isn't your "
          "lot to exclude people from!\n" );
        return 0;
    }
    if ( excluded == "list" ) {
      if ( !sizeof( _lot->excluded ) )
        write( "No one is being excluded from bidding on this lot.\n" );
      else
        write( query_multiple_short( _lot->excluded ) + " is being excluded from "
          "bidding on this lot.\n" );
      return 1;
    }
    if ( excluded != "ignore list" ) {
      if ( member_array( excluded, _lot->excluded ) != -1 ) {
        write( excluded + " is already excluded from this lot.\n" );
        return 1;
      }
      if ( !PLAYER_HANDLER->test_user( excluded ) )
        return notify_fail( excluded +" is not a player here!\n" );
      else  {
        _lot->excluded += ({ excluded });
        _lot->excluded = uniq_array( _lot->excluded );
        write( excluded +" will not be allowed to bid on "+
          query_multiple_short( boxes ) +".\n" );
        return 1;
      }
    }
    if ( !arrayp( ignored ) || !sizeof( ignored ) ) {
      write( "You aren't ignoring anyone!\n" );
      return 1;
    }
    _lot->excluded += ignored;
    _lot->excluded = uniq_array( _lot->excluded );
    write( query_multiple_short( ignored ) + " will not be allowed to bid on "+
      query_multiple_short( boxes ) +".\n"  );
    this_player()->add_succeeded_mess( this_object(), "" );
    return 1;
}
int do_unexclude( object *boxes, string excluded ) {
    object box;
    c_lot *_lots;
    c_lot  _lot;
    int code;
    if ( sizeof( boxes ) > 1 ) {
        this_player()->add_failed_mess( this_object(),
          "You can only $V people from one case at "
          "a time.\n" );
        return 0;
    }
    box = boxes[0];
    if ( member_array( box, keys( cases ) ) == -1 ) {
        this_player()->add_failed_mess( this_object(),
          "$I isn't being auctioned here.\n",
          ({ box }) );
        return 0;
    }
    code = cases[ box ];
    _lots = filter( lots, (: $1->case_code == $(code) :) );
    if ( sizeof( _lots ) != 1 ) {
        printf( "Please inform a creator, there are %d records to "
          "match this case.\n", sizeof( _lots ) );
        printf( "Your lot code is: %d.\n", code );
        this_player()->add_succeeded_mess( this_object(), "" );
        return 1;
    }
    _lot = _lots[0];
    if ( this_player()->query_name() != _lot->seller &&
      !this_player()->query_creator() ) {
        this_player()->add_failed_mess( this_player(), "This isn't your "
          "lot to unexclude people from!\n" );
        return 0;
    }
    if ( member_array( excluded, _lot->excluded ) == -1 ) {
      if ( !sizeof( _lot->excluded ) ) {
        write( "No one is excluded from bidding on this case!\n" );
        return 1;
      }
      write( "Only "+ query_multiple_short( _lot->excluded ) +
        ( sizeof( excluded ) == 1 ? " is " : " are " ) +
        " being excluded from bidding on this case!\n" );
      return 1;
    }
    _lot->excluded -= ({ excluded });
    write( capitalize( excluded ) + " is now allowed to bid on this case.\n" );
    this_player()->add_succeeded_mess( this_object(), "" );
    return 1;
}
c_lot find_spec_lot( int pos ) { return lots[ pos ]; }
string generate_advertising_string( c_lot lot ) {
  string c_string;
  if ( intp( lot->current_bid[ 0 ] ) && ( lot->current_bid[ 0 ] ) )
    c_string = MONEY_HAND->money_value_string( lot->current_bid[ 0 ], currency );
  else
    if ( intp( lot->reserve_price ) && lot->reserve_price )
      c_string = MONEY_HAND->money_value_string( lot->reserve_price, currency );
    else
     c_string = "make an offer";
  if ( c_string == "make an offer" )
    return lot->assoc_store->inv_string + ", " + c_string +
    " but hurry, bidding stops at " + amtime( lot->expiration_time );
  return lot->assoc_store->inv_string + ", currently going for " + c_string +
    " but hurry, bidding stops at " + amtime( lot->expiration_time );
}
string generate_random_adv_string() {
c_lot temp;
  if ( sizeof( lots ) ) {
    temp = lots[ random( sizeof( lots ) ) ];
    if ( temp->status != OPEN )
      return WARNNOLOTS;
    else return generate_advertising_string( temp );
  }
  else
    return WARNNOLOTS;
}