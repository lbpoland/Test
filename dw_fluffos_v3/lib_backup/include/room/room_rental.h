#ifndef __ROOM_RENTAL_H
#define __ROOM_RENTAL_H
#define ROOM_RENTAL_HANDLER               "/obj/handlers/room_rental"
#define ROOM_RENTAL_SAVE_FILE             "/save/rental_save_file"
#define ROOM_RENTAL_INHERIT_ROOM          "/std/room/inherit/room_rental"
#define ROOM_RENTAL_INHERIT_OFFICE        "/std/room/inherit/room_rental_office"
#define ROOM_RENTAL_INHERIT_BASIC_ROOM    "/std/room/room_rental"
#define ROOM_RENTAL_INHERIT_BASIC_OFFICE  "/std/room/room_rental_office"
#define RENTAL_SUCCESS         0
#define RENTAL_NO_SUCH_ROOM    1
#define RENTAL_ALREADY_RENTED  2
#define RENTAL_AVAILABLE       3
#define RENTAL_NO_MONEY        4
#define ONE_DAY                86400
#endif