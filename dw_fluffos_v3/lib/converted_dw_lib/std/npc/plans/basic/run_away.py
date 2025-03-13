# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/npc/plans/basic/run_away.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_sutability(PLAN_MEDIUM_SUTABILITY)
            add_hooked_event(EVENT_MOVED, (: moved_event :))


    def finished(self, npc: MudObject) -> int:
            return !being_attacked(npc)



class Run_away(MudObject):
