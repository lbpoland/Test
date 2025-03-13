# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/arguments.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> int:
            string *args
            args = PHILOSOPHY_HANDLER.query_all_known(this_player()->query_name())
            if (!sizeof(args)) {
            write("You do not know any theological arguments.\n")
            } else {
            write("You know the following theological arguments:\n" +
            query_multiple_short(args) + ".\n")



class Arguments(MudObject):
