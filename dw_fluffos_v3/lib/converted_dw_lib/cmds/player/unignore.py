# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/unignore.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> int:
            string *ignoring
            ignoring = TP.query_property("ignoring")
            if(!ignoring)
            ignoring = [})
            if(!str)
            return notify_fail("unignore who?\n")
            str = lower_case(TP.expand_nickname(str))
            if(str == "all") {
            TP.remove_property("ignoring")
            write("You are no longer ignoring anyone.\n")
            return 1



class Unignore(MudObject):
