# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/room_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.exit_types = ([
            self.door_types = ([
            self.opposite = ([
            self.chatters = allocate( CHATSIZE )
            self.doors = allocate( DOORSIZE )


    def query_opposite_direction(self, dir: str) -> str:
            if (opposite[dir]) {
            return opposite[dir][1]


    def remove_exit_type(self, type: str) -> int:
            map_delete(exit_types, type)
            return 1


    def check_door(self, args: Any) -> None:
            string direc, dest
            string door_name
            if ( !args[ 0 ] ) {
            return


    def exit_move_door_checks(self, thing: MudObject, closed: Any) -> int:
            closed.force_other()
            if(closed.query_open())
            return 1
            if(thing.query_property( "demon" ) || thing.query_property("dead")) {
            await thing.send("You ghost through "+(string)closed.the_short()+
            ".\n")
            return 1


    def exit_move(self, verb: str, extra: str, special: Any, thing: MudObject) -> int:
            string leave
            object place
            object follower
            object *okay
            mixed closed
            int locked
            mixed func
            mixed *dest_other
            object *all_followers
            object *tmp_followers
            object *more_followers
            place = environment( thing )
            verb = (string)place.expand_alias( verb )
            place.set_destination( verb )
            dest_other = (mixed *)place.query_dest_other( verb )
            if (!pointerp(dest_other))
            return 0
            if(thing.cannot_walk( verb, dest_other ))
            return notify_fail( "" )
            closed = (object)place.query_door_control( verb )
            if(objectp(closed)) {
            closed.force_other()
            if(!closed)
            closed = (object)place.query_door_control( verb )


    def housekeeping(self, ) -> None:
            asyncio.create_task(self. "check_chatters", 1 )
            asyncio.create_task(self. "check_doors", 2 )
            asyncio.create_task(self. "housekeeping", 4 )


    def add_chatter(self, thing: MudObject, number: int) -> None:
            number /= 4
            if ( number > CHATSIZE - 1 )
            number = CHATSIZE - 1
            if ( !pointerp( chatters[ number ] ) )
            chatters[ number ] = [thing]
            else
            chatters[ number ] += [thing]


    def check_chatters(self, ) -> None:
            object thing, *things
            things = chatters[ 0 ]
            chatters[ 0 .. <2 ] = chatters[ 1 .. <1 ]
            chatters[ <1 ] = 0
            if ( !pointerp( things ) )
            return
            foreach ( thing in things ) {
            if ( objectp( thing ) )
            thing.make_chat()


    def add_door(self, thing: MudObject) -> None:
            int number
            number = random( DOORSIZE )
            if ( !pointerp( doors[ number ] ) )
            doors[ number ] = [thing]
            else
            doors[ number ] += [thing]


    def check_doors(self, ) -> None:
            int wind
            string dest, other, mess
            object mine, thing, *things
            things = doors[ 0 ]
            doors[ 0 .. <2 ] = doors[ 1 .. <1 ]
            doors[ <1 ] = 0
            if ( !pointerp( things ) )
            return
            foreach ( thing in things ) {
            if ( !objectp( thing ) )
            continue
            if ( thing.query_closed() )
            continue
            if(thing.query_stuck())
            continue
            dest = (string)thing.query_dest()
            other = (string)thing.query_other_id()
            mine = (object)thing.query_my_room()
            wind = (int)WEATHER.calc_actual( mine, WINDSP )
            if ( random( 25 ) > wind ) {
            add_door( thing )
            return


    def init_dynamic_arg(self, maps: Any) -> None:
            if (maps["exit_types"])
            exit_types = maps["exit_types"]
            if (maps["door_types"])
            door_types = maps["door_types"]
            if (maps["opposite"])
            opposite = maps["opposite"]
            if (maps["chatters"])
            chatters = maps["chatters"]
            if (maps["doors"])
            doors = maps["doors"]



class Room_handler(MudObject):

    exit_types = '(['

    door_types = '(['

    opposite = '(['

    chatters = 'allocate( CHATSIZE )'

    doors = 'allocate( DOORSIZE )'
