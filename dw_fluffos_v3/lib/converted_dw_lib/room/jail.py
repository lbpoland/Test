# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/room/jail.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "jail" )
            add_property( "determinate", "the " )
            add_property("no teleport", 1)
            add_property("no godmother", 1)
            set_light( 100 )
            set_long("This is where you are put when you've been a naughty boy (or "
            "girl).  It's a very boring place with nothing to do.\n")


    def init(self, ) -> None:
            ::init()
            if (!this_player()) return
            this_player()->command_override((: squish :))


    def squish(self, cmd: str) -> int:
            string *bits
            if(this_player()->query_creator())
            return 0
            bits = explode(cmd, " ")
            if(BLOCKED_COMMANDS.index(bits[0]) if bits[0] in BLOCKED_COMMANDS else -1 != -1) {
            write( "I don't think so.\n" )
            return 1
            } else {
            return 0



class Jail(MudObject):
