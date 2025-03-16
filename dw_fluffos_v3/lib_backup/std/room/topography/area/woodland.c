inherit "/std/outsides/woodland";
inherit "/std/room/inherit/topography/aroom";
mixed* query_dest_other(string direc) {
   return aroom::query_dest_other(direc, woodland::query_dest_other(direc));
}
string query_look(string direc) {
   return aroom::query_look(direc, woodland::query_look(direc));
}
void create() {
   set_not_replaceable(1);
   ::create();
}
string query_room_letter() {
   return "%";
}