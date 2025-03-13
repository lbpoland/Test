# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/health.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, who: MudObject, wounded: int) -> Any:
            object person
            string health
            int level
            int found
            if(this_player()->check_dark((int)environment(this_player())->
            query_light())) {
            add_failed_mess("You cannot see well enough to examine someone's "
            "health.\n")
            return 0



class Health(MudObject):
