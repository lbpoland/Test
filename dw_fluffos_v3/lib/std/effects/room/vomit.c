#include <effect.h>
void pool_descripts( object room , int pools );
string query_classification () { return "room.vomit"; }
void beginning ( object room, int *args )
{
    int duration, pools ;
    duration = args [ 0 ] ;
    pools    = args [ 1 ] ;
    pool_descripts ( room , pools ) ;
    room -> submit_ee ( 0 , duration , EE_REMOVE ) ;
}
void pool_descripts ( object room , int pools )
{
    room -> remove_item( "pool" );
    room -> add_item( ({ "pool" , "vomit" , "puddle"  }) , "There " +
        ( ( pools == 1 ) ? "is a pool" : "are " + query_num( pools , 10 ) +
        " pools" ) + " of vomit decorating the place.  Inevitably there "
        "are little bits of carrot in it, and it would also be a good "
        "idea to watch one's step." ) ;
    room->add_extra_look( this_object() );
}
int *merge_effect( object room , int *new_args , int *old_args )
{
    int duration , pools ;
    duration = new_args [ 0 ] + room -> expected_tt()  ;
    pools =    new_args [ 1 ] + old_args [ 1 ] ;
    pool_descripts( room , pools ) ;
    return ({ duration , pools }) ;
}
void end( object room, mixed names )
{
    room -> remove_item ( "pool" );
    room -> remove_extra_look( this_object() );
}
string extra_look( object room )
{
    int     *enums;
    int     pools;
    string  look, number;
    enums = room -> effects_matching( query_classification() );
    if( !sizeof( enums ) ) return "";
    pools = ( room -> arg_of( enums[0] ) ) [ 1 ] ;
    number = query_num( pools , 10 );
    look = "There " + ( ( pools == 1 ) ? ( "is a pool " ) : ( "are " +
        number + " pools ") ) + "of vomit here.\n" ;
    return look;
}