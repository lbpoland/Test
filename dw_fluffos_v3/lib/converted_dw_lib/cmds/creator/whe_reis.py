# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/whe_reis.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, indirect_obs: MudObject) -> int:
            object ob, e
            int described
            string txt
            if ( !sizeof( indirect_obs ) ) {
            add_failed_mess( "Where is what?\n" )
            return 0



class Whe_reis(MudObject):
