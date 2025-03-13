# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/give.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, indir: Any, indir_match: str) -> Any:
            string sh
            string s1
            string failmess
            int tot
            int max
            int ok
            object *per
            object *ret
            object *fail
            object pobj
            object ob
            object *obs
            object *succ
            object *keep
            per = indir[1]
            succ = [})
            keep = [})
            failmess = ""
            foreach(pobj in per) {
            obs = indir[0]
            obs -= per
            if (pobj.query_property("player") && !interactive(pobj)) {
            failmess = pobj.the_short()+" seems too chalky to accept your "
            "gift.\n"
            continue



class Give(MudObject):
