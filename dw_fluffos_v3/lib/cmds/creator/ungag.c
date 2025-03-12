#include <playerinfo.h>
inherit "/cmds/base";
int cmd( object victim ) {
   if( !victim->query_property( "gagged" ) )
      return notify_fail( victim->query_short() +" is not gagged.\n" );
   victim->remove_property("gagged");
   log_file("GAG", ctime(time()) + ": " + this_player()->
         query_short() + " ungagged " + victim->query_short() + ".\n");
   tell_object( victim, this_player()->query_short() + " ungags you.\n"
                        "%^YELLOW%^Be more careful with what you say "
                        "in future.%^RESET%^\n" );
   write( "Okay, ungagged " + victim->query_short() + ".\n" );
   return 1;
}
mixed *query_patterns() {
   return ({ "<indirect:player'player'>",
                (: cmd( $1[0] ) :) });
}