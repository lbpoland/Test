#include <effect.h>
string query_classification() {
    return "object.extra_description";
}
void beginning( object thing , mixed *args ) {
    string description;
    int duration;
    description = args[ 0 ];
    duration = args[ 1 ];
    if( !stringp( description ) || !intp( duration ) ) return;
    thing->add_extra_look( this_object() );
    thing->submit_ee( 0 , duration , EE_REMOVE );
}
string extra_look( object thing ) {
    int *enums;
    string message, temp;
    enums = thing->effects_matching( query_classification() );
    if( !sizeof( enums ) ) {
        thing->remove_extra_look( this_object() );
        return "";
    }
    message = "";
    foreach( int elem in enums ) {
        temp =  ( thing->arg_of( elem ) ) [ 0 ];
        if( !stringp( temp ) ) {
            temp = "";
        } else {
           if( strlen( temp ) < 2 || temp[ <2 .. ] != "\n" ) temp += "\n";
        }
        message += temp;
    }
    return message;
}
void end( object thing , mixed *args , int id ) {
    if( sizeof( args ) == 3 && stringp( args[ 2 ] ) ) {
         string end_mess = args[ 2 ];
         if( end_mess[<2 .. ] != "\n" ) end_mess += "\n";
         tell_object( thing , end_mess );
    }
}