# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/lo_se.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, obs: MudObject, str: str) -> Any:
            object *ok, ob
            string s
            if (str == "everyone")
            obs = this_player()->query_followers()
            if (!sizeof(obs)) {
            write("You are not being followed by anyone.\n")
            return 1



class Lo_se(MudObject):
