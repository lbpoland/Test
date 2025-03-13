# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/npc/dont_move.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, arg: int, id: int) -> None:
            player.submit_ee(0, arg, EE_REMOVE)


    def merge_effect(self, player: MudObject, time1: int, time2: int, id: int) -> int:
            player.submit_ee( 0, time1 + time2 - player->expected_tt(),
            EE_REMOVE )
            return time1 + time2



class Dont_move(MudObject):
