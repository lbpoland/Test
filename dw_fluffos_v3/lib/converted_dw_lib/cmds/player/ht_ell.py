# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/ht_ell.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, arg: str, brief: int) -> int:
            function bing
            bing = this_player()->get_htell_func()
            arg = this_player()->expand_nickname(arg)
            return evaluate(bing, arg, brief)



class Ht_ell(MudObject):
