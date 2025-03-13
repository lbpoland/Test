# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/external/coffee_nose.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, time: int) -> None:
            if (time > 1800)
            time = 1800
            await  player.send("\n" )
            await driver.tell_room( environment( player ), (string)player.the_short() + " drinks some of his coffee and ends up with a small amount of froth on "+player.query_possessive()+" nose.\n", exclude=player)
            player.submit_ee( 0, time, EE_REMOVE )
            player.add_extra_look( self )


    def merge_effect(self, player: MudObject, time1: int, time2: int) -> int:
            int newtime
            newtime = (time1 > time2 ) ? time1 : time2
            newtime = ( newtime > 1800 ) ? 1800 : newtime
            player.submit_ee( 0, newtime, EE_REMOVE )
            return newtime


    def end(self, player: MudObject, time: int) -> None:
            if ( !player.query_property( "dead" ) )
            await  player.send("A small amount of frothy Coffee drops onto the floor.\n" )
            player.remove_extra_look( self )


    def extra_look(self, player: MudObject) -> str:
            return capitalize( player.query_pronoun()+" looks "
            "like "+player.query_pronoun()+" has a small amount of creamy, frothy coffee on "+player.query_possessive()+" nose.\n" )



class Coffee_nose(MudObject):
