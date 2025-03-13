# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/idle.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, who: MudObject) -> int:
            if (!interactive(who))
            write(who.query_cap_name() + " is net-dead.\n")
            else
            write(who.query_cap_name() + " has been idle for " +
            "/secure/finger"->time_elapsed_string(query_idle(who)) + ".\n")
            return 1



class Idle(MudObject):
