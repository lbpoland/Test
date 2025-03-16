#include <money.h>
#include <move_failures.h>
#define RECEIPT "/obj/misc/pawn_receipt"
#define TO this_object()
#define TP this_player()
inherit "/std/shop" ;
private int    _pawn_ttl ;
private mixed  _pawn_mess ;
private int    _pawn_markup ;
private string _shop_language;
void set_language( string lang ) {
    _shop_language = lang;
}
string query_language() {
    return _shop_language;
}
void set_pawn_markup( int percent ) {
    _pawn_markup = percent ;
}
int query_pawn_markup() {
    return _pawn_markup ;
}
void set_pawn_ttl( int ttl ) {
    _pawn_ttl = ttl ;
}
int query_pawn_ttl() {
    return _pawn_ttl ;
}
void set_pawn_mess( mixed mess ) {
    _pawn_mess = mess ;
}
string query_pawn_mess() {
    return _pawn_mess ;
}
void create() {
    do_setup++ ;
    ::create() ;
    do_setup-- ;
    add_help_file( "pawn_shop" ) ;
    remove_help_file( "shop" );
    _pawn_mess = ({
        "You pawn $ob$ for $money$.\n",
        "$client$ pawns $ob$.\n"
    }) ;
    _pawn_markup = 20 ;
    _pawn_ttl = 7 * 24 * 60 * 60 ;
    _shop_language = "morporkian" ;
    set_min_amount( 400 ) ;
    add_property( "no steal", 1 ) ;
    if ( ! do_setup ) {
        TO->setup() ;
        TO->reset() ;
    }
}
void init() {
    ::init() ;
    add_command( "pawn", "<indirect:object:me'items'>" ) ;
}
int do_pawn( object *in_obs ) {
    int value, total ;
    mixed *m_array ;
    object ob, money, receipt ;
    object *cheap, *cre, *expensive, *kept, *nobuy, *stolen, *worn ;
    string place, fn ;
    string *text = ({ }) ;
    if ( ! is_open( TP, 0 ) ) {
        return 0 ;
    }
    in_obs = uniq_array( in_obs ) ;
    cre = filter( in_obs, (: creator_object($1) :) ) ;
    if ( sizeof(cre) ) {
        if ( ! TP->query_creator() ) {
            tell_object( TP,
                "Oh dear, you shouldn't have " + query_multiple_short( cre ) +
                "!  "
                + ( sizeof(cre) > 1 ? "They disappear" : "It disappears" ) +
                " with a flash of octarine light.\n" ) ;
            cre->move( "/room/rubbish" ) ;
        } else {
            tell_object( TP,
                "You decide not to pawn " + query_multiple_short( cre ) +
                ", as " + ( sizeof(cre) > 1 ? "they are creator-only items"
                : "it is a creator-only item" ) + ".\n" ) ;
        }
        foreach( ob in cre ) {
            if ( fn = ob->query_property( "virtual name" ) ) {
                fn = ob->query_property( "virtual name" ) ;
            } else {
                fn = base_name( ob ) ;
            }
            text += ({ fn }) ;
        }
        log_file( "ILLEGAL_OBJECT", "%s: %s tried to pawn %s at %s.\n\n",
            ctime(time()), TP->query_name(), query_multiple_short( text ),
            file_name( TO ) ) ;
        in_obs -= cre ;
    }
    kept = filter_array( in_obs, (: $1->query_keep() :) ) ;
    if ( sizeof(kept) ) {
        tell_object( TP,
            "You decide not to pawn " + query_multiple_short( kept ) +
            ", as you are keeping " + ( sizeof(kept) > 1 ? "them" : "it" )
            + ".\n" ) ;
        in_obs -= kept ;
    }
    worn = filter( in_obs, (: $1->query_holder() || $1->query_worn_by() :) ) ;
    if ( sizeof(worn) ) {
        tell_object( TP, "You decide not to pawn "
            + query_multiple_short( worn ) + ", because you are wearing or "
            "holding " + ( sizeof(worn) > 1 ? "them" : "it" ) + ".\n" ) ;
        in_obs -= worn ;
    }
    stolen = filter( in_obs, (: $1->query_property( "stolen" ) :) ) ;
    if ( sizeof(stolen) ) {
        tell_object( TP,
            "You cannot pawn " + query_multiple_short( stolen ) +
            " because " + ( sizeof(stolen) > 1 ? "they're" : "it's" ) +
            " stolen!\n" ) ;
        in_obs -= stolen ;
    }
    nobuy = filter( in_obs, (: $1->do_not_sell() || TO->do_not_buy($1) :) ) ;
    if ( sizeof( nobuy ) ) {
        tell_object( TP,
            "You cannot pawn " + query_multiple_short( nobuy ) + ".\n" ) ;
        in_obs -= nobuy ;
    }
    cheap = filter( in_obs, (: $1->query_value() < TO->query_min_amount() :) ) ;
    if ( sizeof(cheap) ) {
        tell_object( TP,
            "You cannot pawn " + query_multiple_short( cheap ) +
            " as " + ( sizeof(cheap) > 1 ? "they are" : "it is" ) +
            " not expensive enough.\n" ) ;
        in_obs -= cheap ;
    }
    expensive = filter( in_obs,
        (: $1->query_value() > TO->query_max_amount() :) ) ;
    if ( sizeof(expensive) ) {
        tell_object( TP,
            "You cannot pawn " + query_multiple_short( expensive ) +
            " as " + ( sizeof(expensive) > 1 ? "they are" : "it is" ) +
            " too expensive.\n" ) ;
        in_obs -= expensive ;
    }
    if ( ! sizeof( in_obs ) ) {
        add_failed_mess( "You have nothing to pawn.\n" ) ;
        return 0 ;
    }
    foreach( ob in in_obs ) {
        value = scaled_value( ob->query_value() ) ;
        value = ( value * 90 ) / 100;
        total += value ;
        receipt = clone_object( RECEIPT ) ;
        if ( ! receipt ) {
            add_failed_mess(
                "Oh dear, something went very wrong (can't clone receipt object).  "
                "Please bugrep this room.\n" ) ;
            return 0 ;
        }
        receipt->setup_receipt( ob ) ;
        receipt->set_shop_path( TO ) ;
        receipt->set_item_value( value ) ;
        receipt->set_expiry_time( time() + query_pawn_ttl() ) ;
        receipt->setup_read_mess( _shop_language );
        receipt->move( TP ) ;
        ob->move( "/room/rubbish" ) ;
    }
    place = query_property( "place" ) ;
    if ( ! place || ( place == "" ) ) {
        place = "default" ;
    }
    m_array = MONEY_HAND->create_money_array(total, place);
    money = clone_object(MONEY_OBJECT);
    if ( ! money ) {
        add_failed_mess(
            "Oh dear, something went very wrong (can't clone money object).  "
            "Please bugrep this room.\n" ) ;
        return 0 ;
    }
    money->set_money_array(m_array);
    if ( money->move( TP ) != MOVE_OK ) {
        tell_object( TP,
            "You're too heavily burdened to accept all that money, so the "
            "shopkeeper puts it on the floor.\n" ) ;
        money->move( TO ) ;
    }
    do_parse( _pawn_mess, in_obs, TP,
        MONEY_HAND->money_string( m_array ), "" ) ;
    return 1 ;
}
int do_sell( object *in_obs ) {
    add_failed_mess(
        "If you just want to sell items, you'll need to find a general "
        "store.  Pawn shops are for pawning in.\n" ) ;
    return 0 ;
}