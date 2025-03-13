# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/room_rental.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def reset(self, ) -> None:
            string room
            int now = time()
            foreach( room in keys( rented_rooms ) ) {
            if ( stringp( rented_rooms[ room ] ) ) {
            if ( ( eviction_times[ room ] < now ) &&
            ( eviction_times[ room ] > -1 ) ) {
            evict_tenant( find_object( room ) )
            tell_creator( "goldenthread", "RENTAL: %s no longer rents %s\n",
            rented_rooms[ room ], room )
            rented_rooms[ room ] = 0
            eviction_times[ room ] = -1


    def evict_tenant(self, room_ob: MudObject) -> None:
            object *occupants
            occupants = filter( all_inventory( room_ob ), (: living :) )
            room_ob.evict_tenant( occupants )


    def add_room(self, room: str, cost: int, office: MudObject) -> int:
            object room_ob
            if( !room_ob = load_object( room ) )
            return 0
            rented_rooms[ room ] = 0
            rental[ room ] = cost
            eviction_times[ room ] = -1
            locations[ room ] = office.query_location()
            paths[ room_ob.short() ] = room
            do_save()
            return 1


    def query_who_rents(self, room: str, office: MudObject) -> str:
            if ( locations[room] == office.query_location() ) {
            if ( stringp( rented_rooms[room] ) )
            return rented_rooms[room]
            else
            return "nobody"
            } else
            return "no such room in this location"


    def check_tenant(self, player_ob: MudObject, room_ob: MudObject, office: MudObject) -> int:
            string player = player_ob.short()
            string room = room_ob.short()
            if ( player == query_who_rents( room, office ) )
            return RENTAL_SUCCESS
            else if ( player == "nobody" )
            return RENTAL_AVAILABLE
            else if ( player == "no such room!" )
            return RENTAL_NO_SUCH_ROOM
            else
            return RENTAL_ALREADY_RENTED


    def delete_room(self, room: str, office: MudObject) -> int:
            string room_short = load_object( room )->short()
            if ( locations[room] == office.query_location() ) {
            map_delete( rented_rooms, room )
            map_delete( rental, room )
            map_delete( eviction_times, room )
            map_delete( locations, room )
            map_delete( paths, room_short )
            do_save()
            return 1
            } else
            return 0


    def clear_rooms(self, office: MudObject) -> int:
            object room_ob
            foreach( string room in keys( filter( locations,
            (: $2 == $( office.query_location() ) :) ) ) ) {
            room_ob = load_object( room )
            map_delete( rented_rooms, room )
            map_delete( rental, room )
            map_delete( eviction_times, room )
            map_delete( locations, room )
            map_delete( paths, room_ob.query_short() )


    def do_rental(self, player_ob: MudObject, room_short: str, office: MudObject) -> int:
            int result
            string domain = office.query_domain()
            string room = paths[ room_short ]
            if ( locations[room] == office.query_location() ) {
            if ( !rented_rooms[room] ||
            ( rented_rooms[room] == player_ob.short()) ) {
            if ( (int)player_ob.query_value_in( domain ) < rental[room] )
            return RENTAL_NO_MONEY
            rented_rooms[room] = player_ob.short()
            eviction_times[room] = time() + ONE_DAY
            result = RENTAL_SUCCESS
            } else
            result = RENTAL_ALREADY_RENTED
            } else
            result = RENTAL_NO_SUCH_ROOM
            do_save()
            return result


    def query_rental_value(self, room: str) -> int:
            return rental[ room ]


    def remove_rental(self, room_ob: MudObject) -> int:
            int result
            string room_short = room_ob.short()
            string room = paths[ room_short ]
            if ( !undefinedp( rented_rooms[room] ) ) {
            rented_rooms[room] = 0
            result = RENTAL_SUCCESS
            } else
            result = RENTAL_NO_SUCH_ROOM
            do_save()
            return result



class Room_rental(MudObject):
