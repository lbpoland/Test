# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/clubs.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, command: str, extra: str, rest: str) -> Any:
            if (this_player() != this_player(1))
            return 0
            switch(command) {
            case "list":
            do_list(extra, this_player()->query_cols())
            break
            case "invalid":
            do_invalid(extra, this_player()->query_cols())
            break



class Clubs(MudObject):
