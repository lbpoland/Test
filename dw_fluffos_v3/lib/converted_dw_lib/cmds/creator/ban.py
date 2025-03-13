# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/ban.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ip: str, reason: str) -> Any:
            seteuid("Root")
            if (this_player() != this_player(1))
            return 0
            if(!"/secure/master"->query_lord(geteuid(previous_object())) &&
            !"/d/liaison/master"->query_deputy(geteuid(previous_object())))
            return notify_fail("Only lords or liaison deputies can do that.\n")
            if(strsrch(ip, "*") != -1)
            return notify_fail("This command does not take wildcards.\n")
            if (!"/secure/bastards"->change_access(ip, 2, reason,
            time() + (60*60*2))) {
            write("Error changing permissions.\n")
            return 0


    def help(self, ) -> int:
            return notify_fail(
            "Syntax: ban <ip number> <reason>\n")



class Ban(MudObject):
