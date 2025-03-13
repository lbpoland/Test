# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/room/crater.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_classification(self, ) -> str:
            string *beginning( object room, string name ) {
            room.add_item( [name + " shaped crater", "crater"],
            "There is a large crater in the ground, as if " +
            capitalize( name ) + " happened here recently, from a "
            "very great height indeed." )
            room.add_extra_look( self )
            return [name]


    def end(self, room: MudObject, names: Any) -> None:
            string name
            foreach( name in names )  {
            room.remove_item( name + " shaped crater" )


    def extra_look(self, room: MudObject) -> str:
            int     *enums
            string  *shapes
            enums = room.effects_matching( query_classification() )
            if( !sizeof( enums ) )
            return ""
            shapes = room.arg_of( enums[0] )
            if( !sizeof( shapes ) )
            return ""
            if( sizeof( shapes ) == 1 )
            return "There is " + add_a( capitalize( shapes[0] ) ) +
            " shaped crater in the ground.\n"
            else {
            return "There are " + query_multiple_short( map( shapes, (: capitalize(
            $1 ) :) ) ) + " shaped craters in the ground.\n"



class Crater(MudObject):
