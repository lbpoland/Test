#include <creator.h>
inherit "/cmds/base";
string format_data( object *items, object victim, object target ) {
    int size;
    string vname, tname;
    vname = victim->the_short();
    tname = target->the_short();
    switch( size = sizeof( items ) ) {
    case 0:
        return "No objects in " + vname + " were cloned by " +
        tname;
    case 1:
        return "One object, " + query_multiple_short( items ) +
        " in " + vname + "'s inventory was cloned by " +
        tname;
    default:
        return query_num( size, 100 ) + " objects in " +
        vname + "'s inventory were cloned by " + tname;
    }
}
void describe_objects( object player1, object player2 ) {
    string mess;
    mapping data;
    data = filter( unique_mapping( all_inventory( player1 ),
        (: $1->query_cloned_by() :) ),
      (: $1 == $(player2)->query_name() :) );
    if ( !sizeof( data ) ) {
        data[ player1->query_name() ] = ({ });
    }
    mess = implode( values( map( data,
          (: format_data( $2, $(player1), $(player2) ) :) ) ), "\n" );
    tell_object( this_player(), "$P$compare$P$" + mess + "." );
}
int cmd( object player1, object player2 ) {
    describe_objects( player1, player2 );
    describe_objects( player2, player1 );
    return 1;
}
mixed *query_patterns() {
    return ({ "<indirect:wiz-present> {against|with|and} "
      "<indirect:wiz-present>",
      (: cmd( $1[0][0], $1[1][0] ) :) });
}