# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/invcheck.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, filename: str, switch_on: str) -> int:
            switch (switch_on) {
            case "ban":
            INV_CHECK->ban_object (filename)
            break
            case "unban":
            INV_CHECK->unban_object (filename)
            break
            default:
            tell_object (this_player(), INV_CHECK.list_banned())
            break



class Invcheck(MudObject):
