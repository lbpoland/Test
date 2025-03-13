# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/fighting/bob.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, things: MudObject, id: int) -> None:
            tell_object( player, "You prepare to bob "+
            (string)things[ 0 ]->the_short() +".\n" )
            player.set_data( ["unarmed", "blunt", "hands"] )
            player.submit_ee( 0, 10 * COMBAT_SPEED, EE_REMOVE )


    def end(self, player: MudObject, things: MudObject, id: int) -> None:
            if ( sizeof( things ) )
            await  player.send("You missed your opportunity!\n" )


    def restart(self, player: MudObject, things: MudObject, id: int) -> None:
            player.submit_ee( 0, 0, EE_REMOVE )



class Bob(MudObject):
