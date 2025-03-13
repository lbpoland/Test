# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/setmmout.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            if(TP.query_creator() || TP.query_property("setm")) {
            str = str + " "
            if (sizeof(explode("^"+str, "$N")) < 2)
            return notify_fail("Must have a $N in your teleport exit message.\n")
            TP.set_mmsgout(str)
            write("Ok.\n")
            return 1



class Setmmout(MudObject):
