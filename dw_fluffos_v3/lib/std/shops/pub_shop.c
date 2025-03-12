inherit "/std/room/basic_room";
inherit "/std/shops/inherit/pub";
void create() {
   add_help_file("pub_shop");
   do_setup++;
   basic_room::create();
   pub::create();
   do_setup--;
   if (!do_setup) {
      this_object()->setup();
      this_object()->reset();
   }
}
void init() {
   basic_room::init();
   pub::init();
}
void dest_me() {
   pub::dest_me();
   basic_room::dest_me();
}