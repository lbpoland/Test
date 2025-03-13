# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/flip.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, things: MudObject) -> Any:
            int *effect
            object place
            mixed *stuff, *details
            if ( sizeof( things ) > 1 ) {
            add_failed_mess("You can only flip one thing at once.\n")
            return 0



class Flip(MudObject):
