# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/object/cabbage.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, time: int, id: int) -> None:
            player.submit_ee( "make_stink", [20, 20], EE_CONTINUOUS )
            player.submit_ee( 0, time, EE_REMOVE )


    def merge_effect(self, player: MudObject, time1: int, time2: int, id: int) -> int:
            player.submit_ee( 0, time1 + time2 - (int)player.expected_tt(),
            EE_REMOVE )
            return time1 + time2


    def end(self, player: MudObject, time: int, id: int) -> None:
            await  player.send("Your stomach calms down at last.\n" )


    def make_stink(self, player: MudObject, time: int, id: int) -> None:
            tell_object( player, "A huge trumpeting noise comes from your "
            "rear, closely followed by a stench of boiled cabbage.\n" )
            tell_room( environment( player ), "The smell of sprouts and cabbages from "
            + (string)player.one_short() +
            " wafts over you and you find yourself thinking of school dinners."
            "\n", player )


    def smell_string(self, player: MudObject, time: int) -> str:
            return "the delicious doughnutty smell"



class Cabbage(MudObject):
