# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/external/snowball.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, amount: int, id: int) -> None:
            player.add_extra_look( self )
            player.submit_ee( "decrease_amount", 15, EE_CONTINUOUS )


    def restart(self, player: MudObject, amount: int, id: int) -> None:
            player.add_extra_look( self )


    def merge_effect(self, player: MudObject, old_amount: int, new_amount: int, id: int) -> int:
            return old_amount + new_amount


    def end(self, player: MudObject, amount: int, id: int) -> None:
            player.remove_extra_look( self )


    def decrease_amount(self, player: MudObject, amount: int, id: int) -> None:
            amount -= 3 + random( random(amount) )
            if ( amount < 0 ) {
            amount = 0
            player.submit_ee( 0, 1, EE_REMOVE )


    def extra_look(self, player: MudObject) -> str:
            int *enums
            string desc
            enums = (int *)player.effects_matching( "mudlib.snowball" )
            if ( !sizeof( enums ) )
            return ""
            switch ( (int)player.arg_of( enums[ 0 ] ) ) {
            case 0 .. 99 :
            desc = " has a little bit of snow"
            break
            case 100 .. 199 :
            desc = " has a bit of snow"
            break
            case 200 .. 299 :
            desc = " has a few small lumps of snow"
            break
            case 300 .. 399 :
            desc = " has a few lumps of snow"
            break
            case 400 .. 499 :
            desc = " has a number of lumps of snow"
            break
            case 500 .. 599 :
            desc = " has quite a lot of snow"
            break
            case 600 .. 699 :
            desc = " has a lot of snow"
            break
            default :
            desc = " has a thick layer of snow"



class Snowball(MudObject):
