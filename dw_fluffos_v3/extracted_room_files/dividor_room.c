# File: /lib/std/room/furniture/dividor_room.c

inherit "/std/shops/commercial";
private string _main_room;
void set_main_room(string room) {
   _main_room = room;
}
string query_main_room() {
   return _main_room;
}
string query_parcel_post() {
   return _main_room->query_parcel_post();
}