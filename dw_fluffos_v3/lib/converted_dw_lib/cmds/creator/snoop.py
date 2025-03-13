# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/snoop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_snoop_cancel(self, ) -> int:
            seteuid(geteuid(this_player()))
            if (!query_snooping(this_player()))
            write("You aren't snooping anyone.\n")
            else  {
            snoop(this_player(), 0)
            write("Ok, snoop cancelled.\n")


    def do_snoop(self, obs: MudObject) -> int:
            object targ
            targ = obs[0]
            if(!snoop(this_player(), targ)) {
            notify_fail("You fail to snoop " + targ.the_short() + ".\n")
            return 0



class Snoop(MudObject):
