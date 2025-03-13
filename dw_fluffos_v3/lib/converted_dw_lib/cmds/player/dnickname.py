# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/dnickname.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            mapping map_nicknames
            map_nicknames = this_player()->query_nicknames()
            if (!map_nicknames)
            map_nicknames = ([ ])
            if (!map_nicknames[str]) {
            notify_fail("That nickname does not exist.\n")
            return 0



class Dnickname(MudObject):
