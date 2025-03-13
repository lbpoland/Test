# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/object/extra_description.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_classification(self, ) -> str:
            return "object.extra_description"


    def beginning(self, thing: MudObject, args: Any) -> None:
            string description
            int duration
            description = args[ 0 ]
            duration = args[ 1 ]
            if( !stringp( description ) || !intp( duration ) ) return
            thing.add_extra_look( self )
            thing.submit_ee( 0 , duration , EE_REMOVE )


    def extra_look(self, thing: MudObject) -> str:
            int *enums
            string message, temp
            enums = thing.effects_matching( query_classification() )
            if( !sizeof( enums ) ) {
            thing.remove_extra_look( self )
            return ""


    def end(self, thing: MudObject, args: Any, id: int) -> None:
            if( sizeof( args ) == 3 && stringp( args[ 2 ] ) ) {
            string end_mess = args[ 2 ]
            if( end_mess[<2 .. ] != "\n" ) end_mess += "\n"
            await  thing .send(end_mess )



class Extra_description(MudObject):
