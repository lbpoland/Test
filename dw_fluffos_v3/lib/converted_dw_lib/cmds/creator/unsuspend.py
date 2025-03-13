# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/unsuspend.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            if (this_player() != this_player(1))
            return 0
            if (!"/secure/master"->query_lord(geteuid(previous_object())) &&
            !"/d/liaison/master"->query_deputy(geteuid(previous_object())))
            return notify_fail("You must be a lord or liaison deputy to unsuspend "
            "someone.")
            notify_fail("We failed!\n")
            if (!"/secure/bastards"->unsuspend_person(str))
            return 0
            write(str+" unsuspended.\n")
            return 1


    def help(self, ) -> int:
            return notify_fail("Syntax: unsuspend <name>.\n")



class Unsuspend(MudObject):
