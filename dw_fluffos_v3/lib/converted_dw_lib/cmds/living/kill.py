# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/kill.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, things: Any) -> int:
            object thing
            object *fighting
            if ( !environment( this_player() ) ) {
            add_failed_mess( "You are in limbo...\n" )
            return 0



class Kill(MudObject):
