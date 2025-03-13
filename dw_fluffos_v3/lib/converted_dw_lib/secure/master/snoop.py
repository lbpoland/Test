# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/snoop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def valid_snoop(self, snooper: MudObject, snoopee: MudObject, pobj: MudObject) -> int:
            string verb
            verb = this_player()->query_current_verb()
            if (snooper == snoopee) {
            await snooper.send("You can't snoop yourself.\n")
            return 0


    def snoop_reason(self, str: str) -> None:
            object snooper
            snooper = this_player()
            if (this_player(1) != this_player()) {
            write("Can't force people...\n")
            return



class Snoop(MudObject):
