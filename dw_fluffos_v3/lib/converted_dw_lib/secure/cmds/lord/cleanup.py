# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/lord/cleanup.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, mess: str) -> Any:
            if("/secure/bulk_delete"->delete_files(mess))
            write("Ok.\n")
            else
            return notify_fail("Sorry.\n")



class Cleanup(MudObject):
