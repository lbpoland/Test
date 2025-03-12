inherit "/std/room/inherit/newspaper_office";
inherit "/std/room/basic_room";
void create() {
   newspaper_office::create();
   basic_room::create();
   add_help_file("newspaper_office");
}
void init() {
   basic_room::init();
   newspaper_office::init();
}