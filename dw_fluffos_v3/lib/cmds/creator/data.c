#include <creator.h>
inherit "/cmds/base";
int cmd(object *obs, string var) {
    object ob;
    foreach (ob in obs) {
        if ( userp(ob) && !master()->query_lord( this_player()->query_name() ) ) {
            write("You cannot dump a player object.\n");
            continue;
        }
        else {
            this_player()->more_string( WIZ_PRESENT->desc_object( ob ) + ":\n" +
              debug_info( 2, ob ) + "\n", "Data" );
        }
    }
    return 1;
}
mixed *query_patterns() {
    return ({ "<indirect:wiz-present>", (: cmd($1, 0) :) });
}