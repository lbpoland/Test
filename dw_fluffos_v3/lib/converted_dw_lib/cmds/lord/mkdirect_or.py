# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/mkdirect_or.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, creator: str) -> Any:
            seteuid("Root")
            if ( !PLAYER_HANDLER.test_user( creator ) ||
            !"/secure/master"->query_trustee( previous_object( -1 ) ) )
            return notify_fail("You must be a trustee to add a director.\n")
            if("/secure/master"->add_director(creator)) {
            write(creator + " promoted to directorship.\n")
            return 1
            } else
            return notify_fail("Call to add_director failed.\n")



class Mkdirect_or(MudObject):
