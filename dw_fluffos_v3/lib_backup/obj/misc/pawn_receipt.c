#include <am_time.h>
#include <armoury.h>
#include <money.h>
#include <move_failures.h>
#include <player.h>
#include <virtual.h>
#define TO this_object()
#define TP this_player()
inherit "/obj/misc/paper" ;
private int    _expired ;
private int    _expired_sold ;
private int    _expiry_time ;
private int    _item_value, _obplural ;
private int    _timestamp;
private mixed  _static_save;
private string _obname, _obpath, _obshort ;
private string _shop_path, _virt_name ;
object do_kiss();
void setup() {
    set_name( "receipt" );
    set_short( "pawned item receipt" ) ;
    add_adjective( ({ "pawned", "item" }) );
    set_long( "This is a small slip of paper, with a black border.\n" );
    set_main_plural( "pawned item receipts" ) ;
    add_plural( "receipts" );
    add_adjective( "pawned" ) ;
    set_value( 0 ) ;
    set_weight( 1 );
    _obname = "unknown object";
    _obpath = "***";
    _timestamp = time();
}
void init() {
    add_command( "reclaim", "<direct:object:me'receipt'>" ) ;
}
void reset() {
    object item ;
    if ( ( ! _expired ) && time() > _expiry_time ) {
        _expired = 1 ;
        set_short( "expired pawned item receipt" ) ;
        add_adjective( "expired" ) ;
        if ( ! _expired_sold ) {
            _expired_sold = 1 ;
            item = do_kiss() ;
            if ( item ) {
                item->move( _shop_path->query_store_room() ) ;
            }
        }
    }
}
void set_obshort( string s ) {
  _obshort = s;
}
string query_obshort() {
  return _obshort;
}
void set_expiry_time( int time ) {
    _expiry_time = time ;
}
int query_expiry_time() {
    return _expiry_time ;
}
void set_item_value( int value ) {
    _item_value = value ;
}
int query_item_value() {
    return _item_value ;
}
void set_shop_path( mixed shop ) {
    if ( objectp( shop ) ) {
        _shop_path = base_name( shop ) ;
        return ;
    }
    _shop_path = shop ;
    return ;
}
string query_shop_path() {
    return _shop_path ;
}
void set_obname( string name ) {
    _obname = name;
}
void set_object( string path ) {
    _obpath = path;
}
void set_virtobname( string name ) {
    _virt_name = name;
}
string query_obname() {
    return _obname;
}
string query_obpath() {
    return _obpath;
}
int query_timestamp() {
    return _timestamp;
}
string query_virt_obname() {
    return _virt_name;
}
mixed query_static_save() {
  return _static_save;
}
int query_pawned_item_receipt() {
    return 1 ;
}
void set_static_save( mixed args ) {
  mixed p;
  _static_save = args;
  if (_obname != "unknown object") {
    return;
  }
  p = args[0];
  while (mapp(p)) {
    if (!undefinedp(p["short"])) {
      _obname = p["short"];
      return;
    }
    p = p["::"];
  }
}
void set_object_plural( object ob ) {
  if ( ob->query_collective() && ob->query_amount() > 1 ) {
    _obplural = 1;
  } else {
    _obplural = 0;
  }
}
int query_object_plural() {
  return _obplural;
}
string query_correct_short( object ob ) {
    if ( ! ob ) {
      return 0;
    }
    set_object_plural( ob );
    if ( _obplural ) {
      return pluralize( ob->query_short() );
    }
    return ob->query_short();
}
void setup_receipt( object ob ) {
   mixed* bits;
   bits = AUTO_LOAD_OB->fragile_auto_str_ob(ob);
   set_obname(ob->query_name());
   set_obshort( query_correct_short( ob ) );
   set_object(bits[1]);
   set_static_save(bits[2]);
}
string pluralize_sentence( string text, int plural ) {
  if ( plural ) {
    return replace( text, ({
      "$o", "them",
      "$r", "they",
      "$ve", "ve"
    }) );
  }
  return replace( text, ({
    "$o", "it",
    "$r", "it",
    "$ve", "s"
  }) );
}
string query_details() {
    if ( _expired ) {
        return pluralize_sentence(
          "This is a receipt for your pawned " + query_obshort() + ".\n"
          "Sadly, you have left it too long to collect $o and $r ha$ve "
          "expired, so the shop will put $o up for sale.  Better hurry to "
          + _shop_path->the_short() + " sharpish and try to buy $o back!",
          _obplural );
    }
    return pluralize_sentence(
      "This is a receipt for your pawned " + query_obshort() + ".\n"
      "You must reclaim $o from " + _shop_path->the_short() + " before "
      + AM_TIME_HANDLER->query_am_time( _expiry_time ) + " or $r will "
      "be sold.", _obplural );
}
mixed *query_read_mess() {
  string lang;
  if ( _shop_path ) {
    lang = _shop_path->query_language();
  } else {
    lang = "general";
  }
  return ::query_read_mess()
    + ({ ({ (: query_details() :), "neat printing", lang, 0 }) });
}
mapping query_dynamic_auto_load()
{
   return ([
     "::"         : ::query_dynamic_auto_load(),
     "obname"     : _obname,
     "obpath"     : _obpath,
     "obvalue"    : value,
     "virt"       : _virt_name,
     "timestamp"  : _timestamp,
     "static"     : _static_save,
     "been sold"  : _expired_sold,
     "expired"    : _expired,
     "expires on" : _expiry_time,
     "item value" : _item_value,
     "item short" : _obshort,
     "item plural": _obplural,
     "shop path"  : _shop_path
  ]);
}
void init_dynamic_arg(mapping arg, object) {
   _obname = arg["obname"];
   if ( stringp( _obname ) ) {
       add_adjective( explode( lower_case( _obname ), " " ) );
   }
   _obpath = arg["obpath"];
   set_value(arg["obvalue"]);
   _virt_name = arg["virt"];
   _timestamp = arg["timestamp"];
   _static_save = arg["static"];
   _expired = arg["expired"] ;
   _expired_sold = arg["been sold"] ;
   _expiry_time = arg["expires on"] ;
   _item_value = arg["item value"] ;
   _obshort = arg["item short"];
   _obplural = arg["item plural"];
   _shop_path = arg["shop path"] ;
   ::init_dynamic_arg(arg["::"]);
   if ( _expired ) {
       set_short( "expired pawned item receipt" ) ;
       add_adjective( "expired" ) ;
       set_main_plural( "expired pawned item receipts" ) ;
       add_plural( "pawned item receipts" ) ;
   }
}
mixed *stats() {
  mixed *stuff;
  stuff = ::stats() + ({
      ({ "obname", _obname }),
      ({ "obpath", _obpath }),
      ({ "timestamp", _timestamp + " (" + ctime(_timestamp) + ")" }),
      ({ "been sold", _expired_sold }),
      ({ "expired", _expired }),
      ({ "expires on", _expiry_time }),
      ({ "item short", _obshort }),
      ({ "item value", _item_value }),
      ({ "item plural", _obplural }),
      ({ "shop path", _shop_path })
   });
  if (_virt_name)
    stuff += ({ ({ "virtname", _virt_name }) });
  return stuff;
}
object do_kiss() {
    object thing;
    if (sizeof(_static_save) < 2) {
        if (this_player()->query_creator()) {
            write("This receipt has no auto-load information, possibly "
                  "because the object was broken when the player logged "
                  "out.  It will have to be replaced by hand.\n");
        } else {
            write("Sorry, but this object is too broken to repair "
                  "with a kiss.  You'll have to contact a creator.\n");
        }
        return 0;
    }
    if (_virt_name) {
       _virt_name = CLONER->other_file( _virt_name );
       if (file_size(_virt_name) <= 0) {
          _virt_name = ARMOURY->remap_file_path(_virt_name);
       }
       if (file_size(_virt_name) <= 0) {
           write("The receipt whispers: Sorry, I'm still broken.  "
                 "Try again some other time, or contact a creator.\n");
           return 0;
       }
    }
    if ( !catch( thing = (object)CLONER->clone( _obpath ) ) ) {
        if ( thing ) {
            thing->init_static_arg(_static_save[0]);
            thing->init_dynamic_arg(_static_save[1]);
            thing->add_property(VIRTUAL_NAME_PROP, _virt_name);
            move("/room/rubbish");
            return thing;
        } else {
            write("The receipt whispers: I'm going to need some "
                  "creator help.\n");
            thing->dest_me();
        }
    } else {
         write("The receipt whispers: Sorry, I'm still broken.  "
               "Try again some other time, or contact a creator.\n");
    }
    return 0;
}
int do_reclaim() {
    int cost, i ;
    object change, item ;
    string change_str, place ;
    if ( ! query_pawned_item_receipt() ) {
        add_failed_mess( "$D is not a pawned item receipt.\n" ) ;
        return 0 ;
    }
    if ( base_name( environment( TP ) ) != _shop_path ) {
        add_failed_mess(
            "This is not the right place for you to reclaim $D.  "
            "Try a pawn shop.\n" ) ;
        return 0 ;
    }
    if ( ! environment( TP )->is_open( TP, 0 ) ) {
        return 0;
    }
    if ( _expired ) {
        add_failed_mess( "Oh dear, your receipt has expired.  With luck, your "
            + query_obshort() + " will be available for sale in the shop.\n" ) ;
        return 0 ;
    }
    place = query_property( "place" ) ;
    if ( ! place || ( place == "" ) ) {
        place = "default" ;
    }
    cost = ( ( 100 + _shop_path->query_pawn_markup() ) * _item_value ) / 100 ;
    debug_printf( "cost = %d, _item_value = %d, markup = %d",
        cost, _item_value, _shop_path->query_pawn_markup() ) ;
    if ( TP->query_value_in( place ) < cost ) {
        add_failed_mess( "You don't have enough money to reclaim $D.  "
            "It would cost you "
            + MONEY_HAND->money_value_string( cost, place ) + "\n" ) ;
        return 0 ;
    }
    change = MONEY_HAND->pay_amount_from( cost, TP, place ) ;
    if ( change ) {
        change->move( TP ) ;
        change_str = change->short() ;
    }
    item = do_kiss();
    if ( ! item ) {
        add_failed_mess(
          "Oh dear, your item doesn't seem to be here any more.  "
          "Please contact a liaison.\n" );
        return 0;
    }
    i = item->move( TP );
    if ( i != MOVE_OK ) {
        tell_object( TP, "You're too heavily burdened to accept "
          + item->the_short() + ", so it is placed on the floor for you.\n" );
        item->move( environment(TP) );
    }
    add_succeeded_mess( ({
        "$N $V " + item->the_short() + " for "
          + MONEY_HAND->money_value_string( cost, place )
          + ( change_str ? " and receive " + change_str + " in change" : "" )
          + ".\n",
        "$N $V $D and receives " + item->the_short() + " in exchange.\n"
    }) ) ;
    return 1 ;
}