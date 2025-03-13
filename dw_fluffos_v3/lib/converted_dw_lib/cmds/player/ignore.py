# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/ignore.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd_list(self, ) -> int:
            string *ignoring
            ignoring = TP.query_property("ignoring")
            if(!ignoring) {
            ignoring = [})


    def cmd(self, str: str) -> int:
            string *ignoring
            ignoring = TP.query_property("ignoring")
            if(!ignoring) {
            ignoring = [})



class Ignore(MudObject):
