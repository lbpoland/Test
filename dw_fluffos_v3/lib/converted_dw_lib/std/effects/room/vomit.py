# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/room/vomit.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, room: MudObject, args: int) -> None:
            {
            int duration, pools
            duration = args [ 0 ]
            pools    = args [ 1 ]
            pool_descripts ( room , pools )
            room -> submit_ee ( 0 , duration , EE_REMOVE )


    def pool_descripts(self, room: MudObject, pools: int) -> None:
            {
            room -> remove_item( "pool" )
            room -> add_item( ["pool" , "vomit" , "puddle" ] , "There " +
            ( ( pools == 1 ) ? "is a pool" : "are " + query_num( pools , 10 ) +
            " pools" ) + " of vomit decorating the place.  Inevitably there "
            "are little bits of carrot in it, and it would also be a good "
            "idea to watch one's step." )
            room.add_extra_look( self )


    def end(self, room: MudObject, names: Any) -> None:
            {
            room -> remove_item ( "pool" )
            room -> remove_extra_look( self )


    def extra_look(self, room: MudObject) -> str:
            {
            int     *enums
            int     pools
            string  look, number
            enums = room -> effects_matching( query_classification() )
            if( !sizeof( enums ) ) return ""
            pools = ( room -> arg_of( enums[0] ) ) [ 1 ]
            number = query_num( pools , 10 )
            look = "There " + ( ( pools == 1 ) ? ( "is a pool " ) : ( "are " +
            number + " pools ") ) + "of vomit here.\n"
            return look



class Vomit(MudObject):
