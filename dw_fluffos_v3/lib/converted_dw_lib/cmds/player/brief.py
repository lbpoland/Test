# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/brief.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, which: str, type: str) -> int:
            string t, disp
            if(!type) {
            disp = "Your settings are: "
            foreach(t in TP.query_verbose_types())
            disp += t + (TP.query_verbose(t) ? " (verbose) " : " (brief) ")
            write(disp + "\n")



class Brief(MudObject):
