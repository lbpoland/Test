# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/pl_to_ob.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def player_to_object(self, str: str) -> MudObject:
            {
            string tmp
            if (this_player())
            tmp = this_player()->expand_nickname(lower_case(str))
            if (tmp) str = tmp
            return self.find_player(lower_case(str))



class Pl_to_ob(MudObject):
