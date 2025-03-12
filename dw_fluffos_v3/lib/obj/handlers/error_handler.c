inherit "/obj/handlers/inherit/error_handler";
void create() {
  seteuid("Root");
   ::create();
}
void setup_error_handler(string user, string db, string password) {
   ::setup_error_handler(user, db, password);
}