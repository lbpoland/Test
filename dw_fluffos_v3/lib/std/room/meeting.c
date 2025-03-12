inherit "/std/room/basic_room";
inherit "/std/room/inherit/meeting";
void create() {
   add_help_file("meeting");
   basic_room::create();
   meeting::create();
}
void init() {
   basic_room::init();
   meeting::init();
}