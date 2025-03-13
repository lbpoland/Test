# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/dump.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, obs: MudObject) -> int:
            object ob
            foreach (ob in obs) {
            write(WIZ_PRESENT.desc_object(ob) + ":\n" + debug_info(0, ob) + "\n")



class Dump(MudObject):
