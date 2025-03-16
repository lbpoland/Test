inherit "/std/room/outside";
inherit "/std/shops/inherit/pub";
void create() {
   add_help_file("pub_shop");
   do_setup++;
   outside::create();
   pub::create();
   do_setup--;
   if (!do_setup) {
      this_object()->setup();
      this_object()->reset();
   }
}
void init() {
   outside::init();
   pub::init();
}
void dest_me() {
   pub::dest_me();
   outside::dest_me();
}