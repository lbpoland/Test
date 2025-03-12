#include <creator.h>
inherit "/cmds/base";
private string inherith(string ob, string ind, string leaf);
private int cmd(string fn, string fn2) {
    object ob, ob2;
    fn = this_player()->get_path( fn );
    if (!( ob = find_object( fn ))) {
        add_failed_mess( "No such object: " + fn + "\n" );
        return 0;
    }
    if ( fn2 ) {
        fn2 = this_player()->get_path( fn2 );
        if (!( ob2 = find_object( fn2 ))) {
            add_failed_mess( "No such object: " + fn2 + "\n" );
            return 0;
        }
    }
    fn = file_name(ob);
    write(fn + "\n" + inherith(fn, "  ", fn2 ));
    return 1;
}
private string inherith(string ob, string ind, string leaf) {
    string *fn, rtn = "", s;
    int i;
    if(!load_object(ob))
      return ind + "unable to find " + ob + "\n";
    fn = inherit_list(find_object(ob));
    for (i = 0; i < sizeof(fn); i++) {
        if (leaf && (find_object(fn[i]) == find_object(leaf))) {
            rtn += ind + fn[i] + "\n";
        } else {
            s = inherith(fn[i], ind + "  ", leaf);
            if (!leaf || (s != "")) {
                rtn += ind + fn[i] + "\n" + s;
            }
        }
    }
    return rtn;
}
int wiz_present_cmd( mixed indirect_obs ) {
    object fo, fo2;
    string fn, fn2;
    if ( !arrayp( indirect_obs ) ) {
        return 0;
    }
    if ( sizeof( indirect_obs ) < 1 ) {
        return 0;
    }
    if ( arrayp( indirect_obs[0] ) ) {
        fo = indirect_obs[0][0];
        if ( sizeof( indirect_obs ) == 2 ) {
            fo2 = indirect_obs[ 1 ][ 0 ];
        }
    }
    else {
        fo = indirect_obs[ 0 ];
        if ( sizeof( indirect_obs ) == 2 ) {
            fo2 = indirect_obs[ 1 ];
        }
    }
    if ( fo ) {
        fn = file_name( fo );
    }
    if ( fo2 ) {
        fn2 = file_name( fo2 );
    }
    debug_printf( "%O, %O\n", fn, fn2 );
    return cmd( fn, fn2 );
}
public mixed *query_patterns() {
    return ({
              "<word> [with] <word>", (: cmd( $4[0], $4[1] ) :),
              "<word>", (: cmd( $4[0], 0 ) :),
              "<indirect:wiz-present> with <indirect:wiz-present>", (: wiz_present_cmd( $1 ) :),
              "<indirect:wiz-present>", (: wiz_present_cmd( $1 ) :),
    });
}