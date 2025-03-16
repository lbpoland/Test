#include <room/room_rental.h>
inherit "/std/room/basic_room";
inherit ROOM_RENTAL_INHERIT_ROOM;
void create() {
   basic_room::create();
}
void init() {
   basic_room::init();
}