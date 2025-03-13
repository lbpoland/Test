# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/unkeep.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, obs: MudObject) -> int:
            object thing, *success
            success = [})
            foreach (thing in obs)  {
            if (thing.query_keep())  {
            thing.reset_keep()
            success += [thing]



class Unkeep(MudObject):
