inherit "/std/room/basic_room";
inherit "/std/shops/inherit/vault_entry";
void create() {
   add_help_file("vault_entry");
   basic_room::create();
}
void init() {
  basic_room::init();
  vault_entry::init();
}