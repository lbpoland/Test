# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/npc/goals/misc/get_drunk.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_default_priority(GOAL_LOW_PRIORITY)
            add_default_plan(EVENT_GIVEN_MONEY,
            PLAN_DIR + "control/goto_location")


    def invarient(self, npc: MudObject) -> int:
            return 1



class Get_drunk(MudObject):
