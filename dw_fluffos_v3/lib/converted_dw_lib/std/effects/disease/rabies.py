# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/disease/rabies.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, time: int) -> int:
            if( player.query_property( "undead" ) ) {
            player.submit_ee( 0, 0, EE_REMOVE )
            return -1


    def merge_effect(self, player: MudObject, time1: int, time2: int) -> int:
            return time1


    def restart(self, player: MudObject, time: int) -> int:
            player.adjust_bonus_wis( -2 )
            player.adjust_bonus_int( -2 )
            return time


    def end(self, player: MudObject, time: int) -> None:
            player.adjust_bonus_int( 2 )
            player.adjust_bonus_wis( 2 )
            tell_object( player, "You feel the madness leave you, and stop frothing"
            ".\n" )


    def wretch(self, player: MudObject, time: int) -> None:
            int msg_no
            msg_no = random( sizeof( wretch_msg ) )
            await  player.send(wretch_msg[ msg_no ] )
            tell_room( environment( player ), (string)player.the_short() +
            room_msg[ msg_no ], player )
            player.adjust_hp( - ( ( (int)player.query_hp() / 10 ) +
            ( random( 50 ) ) ) )
            COMBAT_EFFECT.monitor_points( player, 1 )


    def query_death_reason(self, ) -> str:
            return "a nasty case of rabies"



class Rabies(MudObject):
