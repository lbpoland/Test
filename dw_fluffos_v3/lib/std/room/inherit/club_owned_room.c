inherit "/std/room/inherit/owned_room";
private nosave string _club_controller;
private nosave string _club_owned_id;
string query_owner() {
   return _club_controller->query_owner_of(_club_owned_id);
}
void set_club_controller(string club_controller) {
   _club_controller = club_controller;
}
string query_club_controller() {
   return _club_controller;
}
void set_owned_id(string id) {
   _club_owned_id = id;
}
string query_owned_id() {
   return _club_owned_id;
}