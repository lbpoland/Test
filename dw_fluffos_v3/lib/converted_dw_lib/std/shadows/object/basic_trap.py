# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/object/basic_trap.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def trap_lock(self, type: str) -> int:
            if(type != "pick")
            return 0
            await this_player().send("Trap triggered.\n")
            return 0



class Basic_trap(MudObject):
