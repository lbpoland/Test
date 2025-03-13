# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/curses/deaf_effect.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, arg: Any) -> Any:
            await  player.send("Sounds seem dim and muffled.\n" )
            if ( pointerp( arg ) ) {
            player.submit_ee( "hear_better", arg[ 1 ], EE_CONTINUOUS )
            return arg[ 0 ]
            } else {
            return arg


    def end(self, player: MudObject) -> None:
            await  player.send("Your hearing has returned to normal.\n" )


    def hear_better(self, player: MudObject, arg: Any, id: int) -> None:
            player.add_message(self, "Your hearing improves somewhat.\n", 0)
            arg = 100 - ((100 - arg) * 2/3)
            if (arg == 100) player.delete_effect( player->sid_to_enum( id ) )
            else
            player.set_arg_of( player->sid_to_enum( id ), arg )


    def merge_effect(self, player: MudObject, old_arg: Any, new_arg: Any, id: int) -> Any:
            player.add_message( self, "Your hearing gets worse.\n", 0 )
            player.set_arg_of( player->sid_to_enum( id ), new_arg )



class Deaf_effect(MudObject):
