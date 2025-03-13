# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/site.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, address: str, level: str, reason: str) -> Any:
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
            case "authnew":
            level = "4"
            break
            case "normal":
            level = "1"
            break


    def access(self, filter: str) -> int:
            string addr, ret
            mapping list
            int found
            seteuid("Root")
            if (this_player() != this_player(1))
            return 0
            list = "/secure/bastards"->query_all_access()
            ret = ""
            foreach(addr in keys(list)) {
            if(!filter || filter == "" || strsrch(addr, filter) != -1) {
            found = 1
            ret += sprintf("%-20s %-18s %-=39s\n", addr,
            PERM_NAMES[list[addr][ACCESS_LEVEL]],
            list[addr][ACCESS_REASON])


    def multi(self, allow: int, address: str) -> int:
            if("/secure/bastards"->change_multi(address, allow, 0)) {
            if(allow)
            write("Site " + address + " has been permitted for multiplayers.\n")
            else
            write("Site " + address + " has been blocked for multiplayers.\n")
            } else
            write("Error multiplayer settings for site " + address + ".\n")
            return 1


    def list_multi(self, filter: str) -> int:
            string addr, ret
            mapping list
            int found
            list = "/secure/bastards"->query_all_multi()
            ret = ""
            foreach(addr in keys(list)) {
            if(!filter || filter == "" || strsrch(addr, filter) != -1) {
            found = 1
            ret += sprintf("%-30s\n", addr)


    def help(self, ) -> int:
            return notify_fail(
            "Syntax: site access\n"+
            "            site ban <ip number|site name> <level> <reason>\n"+
            "                     <level> := normal normal access,\n"+
            "                                nonew no new players, \n"+
            "                                authnew authorised new players\n"+
            "                                noaccess no access.\n")



class Site(MudObject):
