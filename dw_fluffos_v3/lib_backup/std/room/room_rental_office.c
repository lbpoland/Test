#include <room/room_rental.h>
inherit "/std/room/basic_room";
inherit ROOM_RENTAL_INHERIT_OFFICE;
void create() {
   basic_room::create();
   room_rental_office::create();
}
void init() {
   basic_room::init();
   room_rental_office::init();
}