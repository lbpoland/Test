# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/monitor.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            int monitor
            monitor = TP.query_monitor()
            if(!str) {
            write("Your hit point monitor is set to " + MONITOR_OPTIONS[monitor] +
            ".\n")
            return 1



class Monitor(MudObject):
