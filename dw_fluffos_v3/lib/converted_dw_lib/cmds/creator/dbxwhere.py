# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/dbxwhere.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            mapping error
            object ob
            if (str) {
            str = this_player()->expand_nickname(str)
            ob = find_player(str)
            if (!ob) {
            write("No such player.\n")
            return 1



class Dbxwhere(MudObject):
