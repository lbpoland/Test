# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/fo_llow.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, obs: MudObject) -> int:
            object *ok, ob
            object *already
            string s
            mapping hide_invis
            int hiding, sneaking
            ok = [})
            already = [})
            foreach (ob in obs) {
            if (ob.query_followers(.index(TP) if TP in ob.query_followers( else -1) == -1) {
            if (ob.add_follower(TP)) {
            ok += [ob]



class Fo_llow(MudObject):
