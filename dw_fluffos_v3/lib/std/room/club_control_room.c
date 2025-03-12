inherit "/std/room/basic_room";
inherit "/std/room/inherit/club_control_room";
void create() {
    do_setup++;
    basic_room::create();
    club_control_room::create();
    do_setup--;
    if ( !do_setup ) {
        this_object()->setup();
        this_object()->reset();
    }
}
void init() {
    basic_room::init();
    club_control_room::init();
}