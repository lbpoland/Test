# File: /lib/std/room/delivery_room.c

inherit "/std/room/basic_room";
inherit "/std/delivery";
void create() {
    delivery::create();
    basic_room::create();
}
void dest_me() {
    delivery::dest_me();
    basic_room::dest_me();
}
mixed *stats() {
    return delivery::stats() + basic_room::stats();
}
int query_delivery_room() {
    return 1;
}