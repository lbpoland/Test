# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/em_ote.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, words: str) -> Any:
            string pad = " "
            if(!environment(this_player())) {
            return notify_fail("You are in limbo, you cannot emote.\n")



class Em_ote(MudObject):
