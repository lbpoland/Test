# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/curses/antisqeal.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, time: int) -> int:
            player.submit_ee( 0, time, EE_REMOVE )
            return time


    def merge_effect(self, player: MudObject, time1: int, time2: int) -> int:
            int duration
            duration = time2 + player.expected_tt()
            player.submit_ee( 0, duration, EE_REMOVE )
            return duration


    def end(self, player: MudObject, time: int) -> None:
            tell_object( player, "Your ability to mangle the english language "
            "returns.\n")



class Antisqeal(MudObject):
