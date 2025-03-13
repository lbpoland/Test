# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/mks_enior.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, creator: str) -> Any:
            seteuid("Root")
            if ( !PLAYER_HANDLER.test_user( creator ) ||
            !"/secure/master"->query_lord( previous_object( -1 ) ) )
            return notify_fail("You must be a lord to create a senior creator.\n")
            if("/secure/master"->add_senior(creator)) {
            write(creator + " promoted to senior.\n")
            return 1
            } else
            return notify_fail("Call to add_senior failed.\n")



class Mks_enior(MudObject):
