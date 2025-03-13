# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/unh_old.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, obs: MudObject) -> int:
            object *ok, *zip, *failed, ob, *using
            string s
            mixed ret
            using = TP.query_holding()
            failed = ok = zip = [})
            foreach (ob in obs) {
            if (using.index(ob) if ob in using else -1 != -1) {
            if (!sizeof(ret = TP.set_unhold(ob)) || !ret)
            failed += [ob]
            else
            ok += [ob]



class Unh_old(MudObject):
