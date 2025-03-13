# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/maptemp.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_map(self, ) -> int:
            string map
            int* coords
            object env
            string handler
            env = environment(this_player())
            if (!env)  {
            add_failed_mess("You are somewhere not on any map.\n")
            return 0



class Maptemp(MudObject):
