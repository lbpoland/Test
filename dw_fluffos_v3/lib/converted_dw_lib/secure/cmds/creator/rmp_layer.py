# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/rmp_layer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, player: str, reason: str, immediately: int) -> int:
            if (!master()->query_liaison_deputy_or_lord(previous_object(-1))) {
            unguarded((: log_file, "/log/CHEAT", ctime(time()) +
            ": illegal attempt to delete a player.\nTrace: " +
            back_trace() :))
            return notify_fail("Sorry: only directors can delete players.\n")



class Rmp_layer(MudObject):
