inherit "/obj/handlers/inherit/club_inherit";
void create() {
   ::create();
   setup_call_check_clubs(0, 1);
}
void dest_me() {
   save_cache();
   destruct(this_object());
}