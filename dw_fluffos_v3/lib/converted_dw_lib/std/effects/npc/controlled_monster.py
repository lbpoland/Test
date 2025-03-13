# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/npc/controlled_monster.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, dest: str, id: int) -> None:


    def merge_effect(self, player: MudObject, time1: int, time2: int, id: int) -> int:
            return time2



class Controlled_monster(MudObject):
