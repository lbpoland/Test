#include <money.h>
inherit "/obj/monster";
private mapping fitted_surfaces = ([ ]);
private string *allowed_surfaces = ({ });
private string *allowed_domains = ({ });
private string *responses = ({
        "'I don't fit those kinds of surfaces.",
        "'I don't fit that kind of decor.",
        "'You don't own this place, sorry!",
        "'I can't decorate surfaces here!",
        "'Something went horribly wrong!",
        "'All finished!",
        "'You don't have enough money to pay for the $decor$!  It "
        "will cost you $amount$.",
        "'I can fit $allowed$ with any of the following:",
        "'I don't have any stock right now.",
        "'Ok, I'll get right on with it.",
        "'What?  Did somebody say something?",
        "'I've already been hired by $employer$.",
        "'Ok, take me to the room you want decorated and ask me to "
        "fit something when we get there.",
        "'Sorry, I don't go there."
    });
private string under_construction_mess = "covered in dust and dirt" ;
private int work_time = 10;
private object employer;
private string last_ok;
int do_ask( string surface, string decor );
void create() {
    do_setup++;
    ::create();
    do_setup--;
    if (!do_setup) {
        this_object()->setup();
        this_object()->reset();
    }
    add_help_file("/doc/object/surface_decorator");
    add_enter_commands("#check_domain");
}
void init() {
    ::init();
    this_player()->add_command( "ask", this_object(), "<direct:object> to "
        "fit the <string'surface'> with <string'decor'>",
        (: do_ask($4[1], $4[2])  :) );
    this_player()->add_command( "list", this_object(), "goods from "
        "<direct:object>" );
    this_player()->add_command( "hire", this_object(), "<direct:object>");
}
int do_list() {
    int i;
    string thing;
    i=1;
    if( !sizeof( fitted_surfaces ) ) {
        init_command( responses[8], 1 );
        return 1;
    }
    init_command( replace( responses[7], ({
            "$allowed$", query_multiple_short( map( allowed_surfaces,
                (: pluralize($1) :) ) )
        }) ), i );
    foreach( thing in keys( fitted_surfaces ) ) {
        i++;
        init_command("'" + capitalize(thing) + " for " +
            MONEY_HAND->money_value_string(fitted_surfaces[thing][1],
            query_property("place")) + ".", i);
    }
    return 1;
}
int do_hire() {
    this_player()->add_succeeded_mess( this_object(), "$N ask$s $D about "
        + this_object()->query_possessive() + " services.\n", ({ }) );
    if( !this_player()->query_visible( this_object() ) ) {
        init_command( responses[10], 1 );
        return 1;
    }
    if( employer &&
        environment( employer ) == environment( this_object() ) &&
        this_player() != employer ) {
        init_command( replace( responses[11], ({ "$employer$", "$C$" +
            employer->query_name() }) ), 1 );
        return 1;
    }
    employer = this_player();
    do_command("unfollow everyone");
    employer->add_follower(this_object());
    init_command( responses[12], 1 );
    return 1;
}
int do_ask( string surface, string decor ) {
    string long, allowed, place;
    int fee, can_do;
    object where;
    can_do = 0;
    foreach( allowed in allowed_surfaces ) {
        if( strsrch( surface, allowed ) != -1 ) {
            can_do = 1;
        }
    }
    if( !can_do ) {
        do_command(responses[0]);
        return 1;
    }
    if( member_array( decor, keys( fitted_surfaces ) ) == -1 ) {
        do_command(responses[1]);
        return 1;
    }
    long = fitted_surfaces[decor][0];
    fee  = fitted_surfaces[decor][1];
    where = environment( this_object() );
    if(!where->test_occupier( this_player()->query_name() ) ) {
        do_command(responses[2]);
        return 1;
    }
    if(!function_exists("decorate_surface", where)) {
        do_command(responses[3]);
        return 1;
    }
    place = query_property("place");
    if ( this_player()->query_value_in( place ) < fee ) {
        do_command( replace( responses[6], ({
            "$decor$", decor,
            "$amount$", MONEY_HAND->money_value_string(fee, place)
        }) ) );
        queue_command("stare" + this_player()->query_name());
        return 1;
    }
    if(!where->decorate_surface(surface,under_construction_mess)) {
        do_command(responses[4]);
        return 1;
    }
    call_out( "finish_work", work_time, surface, long, where );
    do_command( responses[9] );
    do_command( "unfollow everyone" );
    this_player()->pay_money( (mixed *)MONEY_HAND->create_money_array( fee,
            place ), place);
    this_player()->add_succeeded_mess( this_object(), "$N pay$s $D some "
        "money and " + this_object()->query_pronoun() + " starts to go "
        "about his work on the " + surface + ".\n", ({ }) );
    return 1;
}
void finish_work( string surface, string long, object where ) {
    do_command(":finishes his work.");
    if( employer ) {
        employer->add_follower(this_object());
    }
    if(!where || !where->decorate_surface(surface, long )) {
        do_command(responses[4]);
        return;
    }
    else {
        do_command(responses[5]);
        return;
    }
}
private void go_back() {
    move("/room/rubbish", "$N walk$s in.", "$N walk$s away.");
    if( last_ok ) {
        move(last_ok, "$N walk$s in.", "$N walk$s away.");
    }
}
void check_domain() {
    string allowed, here;
    int ok;
    here = file_name( environment( this_object() ) );
    ok = 0;
    foreach( allowed in allowed_domains ) {
        if( strsrch( here, allowed ) != -1 ) {
            ok = 1;
        }
    }
    if( ok ) {
        last_ok = here;
        return;
    }
    else {
        do_command("unfollow everyone");
        do_command( responses[13] );
        go_back();
        return;
    }
}
void add_fitted_surface( string short, string long, int cost ) {
    fitted_surfaces[ short ] = ({ long, cost });
}
mapping query_fitted_surfaces() { return fitted_surfaces; }
void remove_fitted_surface( string short ) {
    map_delete( fitted_surfaces, short );
}
void remove_all_fitted_surfaces() {
    fitted_surfaces = ([ ]);
}
void add_allowed_surface( string surface ) {
    if( member_array( surface, allowed_surfaces ) == -1 ) {
        allowed_surfaces += ({ surface });
    }
}
string *query_allowed_surfaces() { return allowed_surfaces; }
void add_allowed_domain( string domain ) {
    if( member_array( domain, allowed_domains ) == -1 ) {
        allowed_domains += ({ domain });
    }
}
string *query_allowed_domains() { return allowed_domains; }
void set_responses( string *the_responses ) {
    if( sizeof(the_responses) != sizeof(responses) ) {
        return 0;
    }
    else {
        responses = the_responses;
    }
}
string *query_responses() { return responses; }
void set_under_construction_mess( string mess ) {
    under_construction_mess = mess;
}
string query_under_construction_mess() { return under_construction_mess; }
void set_work_time( int time ) {
    work_time = time;
}
int query_work_time() { return work_time; }
void set_employer( object player ) {
    employer = player;
}
object query_employer() { return employer; }