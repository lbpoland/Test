# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/conv.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ip: str, ident: str, level: str, reason: str) -> Any:
            seteuid("Root")
            if (this_player() != this_player(1))
            return 0
            switch(level) {
            case "nonew":
            level = "2"
            break
            case "noacccess":
            level = "3"
            break
            case "normal":
            level = "1"
            break


    def access(self, filter: str) -> int:
            mixed bing
            seteuid("Root")
            if (this_player() != this_player(1))
            return 0
            bing = (mixed)"/secure/bastards.old"->query_all_access()
            if (!m_sizeof(bing)) {
            notify_fail("No access control defined.\n")
            return 0


    def help(self, ) -> int:
            return notify_fail(
            "Syntax: site access\n"+
            "            site ban <ip number> <ident> <level> <reason>\n"+
            "                         <level> := normal [1] normal access,\n"+
            "                                          nonew [2] no new players, \n"+
            "                                          noaccess [3] no access.\n")



class Conv(MudObject):
