# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/data.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, obs: MudObject, var: str) -> int:
            object ob
            foreach (ob in obs) {
            if ( userp(ob) && !master()->query_lord( this_player()->query_name() ) ) {
            write("You cannot dump a player object.\n")
            continue



class Data(MudObject):
