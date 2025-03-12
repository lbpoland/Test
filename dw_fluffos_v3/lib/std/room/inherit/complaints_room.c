#include <complaints_handler.h>
#include <board.h>
void init() {
    add_command( "complain", "" );
}
int do_complain() {
    if ( this_player()->query_property( "guest" ) )
        return add_failed_mess( "Guest characters cannot lodge "
                                "complaints.\n" );
    tell_object( this_player(), "You are lodging an official complaint about "
                 "something or someone.\n"
                 "Do not take this action lightly.\n"
                 "Complaints should be about serious Disc-related matters.  "
                 "Please note that this complaint is submitted anonymously.  "
                 "If you wish to receive a reply, make sure you place your "
                 "character name in the complaint so we know who to respond "
                 "to.\n"
                 "Feedback for the general populous also often appears on "
                 "various bulletin boards.\n" );
    this_player()->do_edit( 0, "finish_complaint", this_object() );
    return 1;
}
void finish_complaint( string str ) {
    if ( !str ) {
        tell_object( this_player(), "Complaint aborted.\n" );
    } else {
        if ( COMPLAINTS_HANDLER->do_submit_complaint( str ) ) {
            tell_object( this_player(), "Complaint posted.  Thank you for "
                         "your complaint.  If you submitted your name in "
                         "your complaint, you should receive a response in "
                         "the near future.  Please be patient, as there may "
                         "be in-depth discussions as a result of your "
                         "complaint.\n" );
        } else {
            tell_object( this_player(), "There has been a problem posting "
                         "your complaint.  As a result it has NOT been "
                         "submitted.  You should contact a liaison or other "
                         "creator to get this rectified immediately.\n" );
        }
    }
}
int board_access_check( int type, string, object previous, string name ) {
    tell_creator("arienne",file_name(previous)+"\n");
    switch ( type ) {
    case B_ACCESS_READ:
        return ( "/secure/master"->query_lord( name ) );
    case B_ACCESS_WRITE:
        return ( ( previous == this_object() ) ||
                 ( "/secure/master"->query_lord( name ) ) );
    case B_ACCESS_DELETE :
        return 0;
    }
}