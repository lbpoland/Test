inherit "/std/room/water_outside";
inherit "/std/room/inherit/topography/aroom";
mixed* query_dest_other(string direc) {
   mixed*fluff;
   fluff =  water_outside::query_dest_other(direc);
printf("%O\n", fluff);
   return aroom::query_dest_other(direc, fluff);
}
string query_look(string direc) {
   return aroom::query_look(direc, water_outside::query_look(direc));
}
void create() {
   set_not_replaceable(1);
   ::create();
}
string query_room_letter() {
   return "~";
}