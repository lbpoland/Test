#include <playerinfo.h>
inherit "/cmds/base";
int cmd( object victim, string reason, int number ) {
   victim->add_property( "gagged", reason, 60 * number );
   log_file( "GAG", ctime(time()) +": "+ this_player()->query_short()
             + " gagged " + victim->query_short() + " for " + number
             + " minutes.  Reason: " + reason +".\n");
   PLAYERINFO_HANDLER->add_entry( this_player(), victim->query_name(),
             "gag", "Gagged for " + number + " minutes.  Reason: '" + reason +
             "'.\n");
   tell_object( victim,
         "%^RED%^%^BOLD%^You have been gagged by " +
         this_player()->query_short() + " for the reason: '" + reason +
         "'.\nYou will not be able to shout, chat or use the newbie "
         "channel until the gag is removed.%^RESET%^\n" );
   write( "Okay, gagged " + victim->query_short() + " for " + number +
          " minutes.  Now please discuss your reason for gagging with "
          "them.  IMPORTANT! You should only be gagging for deliberately "
          "offensive language.\n" );
   event( users(), "inform", this_player()->query_short()
          + " gagged " + victim->query_short() + " for: " + reason, "gag");
   return 1;
}
mixed *query_patterns() {
   return ({ "<indirect:player'player'> <string'reason'>",
                (: cmd( $1[0], $4[1], 15 ) :),
             "<indirect:player'player'> <string'reason'> <number'minutes'>",
                (: cmd( $1[0], $4[1], $4[2] ) :) });
}