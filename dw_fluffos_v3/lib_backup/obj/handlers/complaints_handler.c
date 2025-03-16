#include <board.h>
#define SAVEFILE "/save/complaints/complaints_handler.o"
#define BOARD "complaints"
int _complaintNumber;
void save_file() {
    unguarded( (: save_object( SAVEFILE ) :) );
}
void load_file() {
    unguarded( (: restore_object( SAVEFILE ) :) );
}
void create() {
    seteuid( getuid() );
    _complaintNumber = 1;
    load_file();
}
int do_submit_complaint( string str ) {
    int ret = 0;
    if ( str ) {
        ret = BOARD_HAND->
            add_message( BOARD, "Anonymous",
                         "Anonymous complaint #" + _complaintNumber,
                         sprintf( "%-=78s\n", str ) );
        _complaintNumber++;
        save_file();
    }
    return ret;
}
int board_access_check( int type, string, object previous, string name ) {
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