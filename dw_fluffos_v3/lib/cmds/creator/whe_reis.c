#include <creator.h>
inherit "/cmds/base";
int cmd( object *indirect_obs ) {
    object ob, e;
    int described;
    string txt;
    if ( !sizeof( indirect_obs ) ) {
        add_failed_mess( "Where is what?\n" );
        return 0;
    }
    txt = "$P$Whereis$P$";
    foreach ( ob in indirect_obs ) {
        if ( ob->query_hidden() )
            continue;
        described = 0;
        e = ob;
        while ( e = environment( e ) ) {
            if ( interactive( e ) && !reference_allowed( e, this_player() ) )
                break;
            if ( !described ) {
                txt += WIZ_PRESENT->desc_object(ob) + " is : \n";
                described = 1;
            }
            txt += "  in " + WIZ_PRESENT->desc_f_object(e) + "\n";
        }
        if ( !described )
            txt += WIZ_PRESENT->desc_object(ob) + " is in Null-space.\n";
    }
    tell_object( this_player(), txt + "\n" );
    return 1;
}
mixed *query_patterns() {
    return ({ "<indirect:wiz-present>", (: cmd($1) :) });
}