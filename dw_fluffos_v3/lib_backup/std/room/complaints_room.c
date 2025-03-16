inherit "/std/room/inherit/complaints_room";
inherit "/std/room/basic_room";
void create() {
    add_help_file("complaints_room");
    do_setup++;
    basic_room::create();
    do_setup--;
    set_not_replaceable( 1 );
    if ( !do_setup ) {
        this_object()->setup();
        this_object()->reset();
    }
}
void init() {
    complaints_room::init();
    basic_room::init();
}