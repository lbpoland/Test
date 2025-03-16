#include <move_failures.h>
inherit "/std/object";
private int _call_out_handle;
void setup() {
    reset_get();
    if ( clonep() ) {
        _call_out_handle = call_out("die",400);
    }
}
void set_type(string type) {
    set_name(type);
    set_short(type);
    set_long("A wonderful " + type + " with glowing eyes made of coal and twigs "
      "for ears.\n");
    add_extra_look( this_object() );
}
string extra_look( object ob ) {
    int time_left;
    if ( !_call_out_handle ) {
        return "";
    }
    time_left = find_call_out( _call_out_handle );
    debug_printf( "time left is %d\n", time_left );
    if ( time_left > 300 || time_left < 0 ) {
        return "";
    }
    return "It is " + ({ "mostly", "half", "slightly" })[time_left/100] +
        " melted.\n";
}
void die() {
    string noun;
    switch( environment( this_object() )->query_property( "location" ) ) {
    case "inside":
        noun = "floor";
        break;
    case "outside":
        noun = "ground";
        break;
    case "underwater":
        noun = "seabed";
        break;
    default:
        noun = "floor";
        break;
    }
    tell_room( environment( this_object() ),
      the_short() + " $V$0=melts,melt$V$ into the " + noun + ".\n");
    if ( this_object()->move( "/room/rubbish" ) != MOVE_OK ) {
        dest_me();
    }
}