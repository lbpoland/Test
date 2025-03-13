# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/disease/gp_drain_effect.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_classification(self, ) -> str:
            return CLASS


    def query_death_reason(self, ) -> str:
            return "wasting away slowly"


    def adjust_health(self, player: MudObject) -> None:
            int damage,
            *enums = player.effects_matching( query_classification() )
            mixed *args
            if( sizeof( enums ) ){
            args = player.arg_of( enums[ 0 ] )


    def end(self, player: MudObject, arg: Any) -> None:
            string *message = arg[2]
            await  player.send(message[1] + "\n" )


    def restart(self, player: MudObject, arg: Any) -> None:
            string *message = arg[2]
            await  player.send(message[0] + "\n" )



class Gp_drain_effect(MudObject):
