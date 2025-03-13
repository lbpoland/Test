# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/delalt.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def delete_alt(self, s1: str, s2: str) -> int:
            string *alts, alt
            s1 = this_player()->expand_nickname(lower_case(s1))
            alts =  explode(lower_case(s2)," ") - [""] - [0]
            foreach(alt in alts)
            write(PLAYERINFO_HANDLER.delete_alt(this_player(), s1, alt))
            return 1



class Delalt(MudObject):
