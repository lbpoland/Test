# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/dup_licate.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            object *val
            notify_fail("No such object.\n")
            val = WIZ_PRESENT.wiz_present(str, this_player())
            if(!sizeof(val)) {
            notify_fail("No matching objects\n")
            return 0



class Dup_licate(MudObject):
