#include <effect.h>
#define SOAP_EFFECT "/std/effects/healing/antiseptic_soap"
#define WET_EFFECT "/std/effects/other/wetness"
protected int add_wash_effect( string classification, function func );
protected int add_finished_func( function func );
protected void advanced_antiseptic( object ob, string classification, mixed arg, int effect_enum, object effect_ob );
protected void basic_cleaning( object ob, int effect_enum, string message );
protected void apply_soap( object ob, string *applied_effects );
protected void wet_person( object ob, string *applied_effects );
private mapping _wash;
private function *_finished_funcs;
void create() {
    _wash = ([ ]);
    _finished_funcs = ({ });
    add_wash_effect( "body.smell", (: advanced_antiseptic :) );
    add_wash_effect( "misc.ketchup", (: basic_cleaning( $1, $3,
        "The soap rinses the ketchup off your face." ) :) );
    add_wash_effect( "object.label", (: basic_cleaning( $1, $3,
        "The labels stuck to your body peel off in the water." ) :) );
    add_wash_effect( "body.frog-adhesive", (: basic_cleaning( $1, $3,
        "The frantic ribbiting fades away as the frog adhesive washes "
        "off." ) :) );
    add_finished_func( (: apply_soap :) );
    add_finished_func( (: wet_person :) );
    this_object()->add_setup_wash_command();
}
void init() {
    this_object()->add_init_wash_command();
}
protected int add_wash_effect( string classification, function func ) {
    if ( !_wash[ classification ] ) {
        _wash[ classification ] = func;
        return 1;
    }
    return 0;
}
protected int add_finished_func( function func ) {
    _finished_funcs += ({ func });
    return 1;
}
public string *query_wash_classifications() {
    return keys( _wash );
}
protected int remove_wash_effect( string classification ) {
    if ( _wash && _wash[ classification ] ) {
        map_delete( _wash, classification );
        return 1;
    }
    return 0;
}
protected void advanced_antiseptic( object ob, string classification, int effect_enum, mixed arg, object effect_ob ) {
    tell_object( ob,
        "The antiseptic power of the soap defeats " +
        effect_ob->smell_string( ob, arg ) + ".\n" );
    ob->delete_effect( effect_enum );
}
protected void basic_cleaning( object ob, int effect_enum, string message ) {
    tell_object( ob, message + "\n" );
    ob->delete_effect( effect_enum );
}
protected void apply_soap( object ob, string *applied_effects ) {
    ob->add_effect( SOAP_EFFECT, 10000 );
}
protected void wet_person( object ob, string *applied_effects ) {
    ob->add_effect( WET_EFFECT, 250 );
}
public int wash_player( object ob ) {
    function func;
    string eff;
    string *cleaned;
    int *enums, eff_enum;
    cleaned = ({ });
    if ( !objectp( ob ) ) {
        return 0;
    }
    foreach( eff, func in _wash ) {
        enums = ob->effects_matching( eff );
        if ( sizeof( enums ) ) {
            foreach( eff_enum in enums ) {
                evaluate( func, ob, eff, eff_enum, ob->arg_of( eff_enum ),
                    ob->eff_of( eff_enum ) );
            }
            cleaned += ({ eff });
        }
    }
    foreach( func in _finished_funcs ) {
        evaluate( func, ob, cleaned );
    }
    return 1;
}
int query_baths() {
    return 1;
}