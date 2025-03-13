# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/dir_s.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            mixed *stuff
            stuff = this_player()->query_property("dir list")
            if (!stuff) {
            stuff = D_DEFAULT



class Dir_s(MudObject):
