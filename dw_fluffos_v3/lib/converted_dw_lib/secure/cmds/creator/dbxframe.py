# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/dbxframe.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def print_vars(self, vars: Any) -> str:
            string *result = allocate(sizeof(vars))
            int i
            for (i=0; i<sizeof(vars); i++) {
            if (mapp(vars[i]))
            result[i] = "([ ... ])"
            else if (functionp(vars[i]))
            result[i] = "(: ... :)"
            else if (intp(vars[i])) {
            if (vars[i]) result[i]=vars[i]+""
            else if (nullp(vars[i])) result[i]="NULL"
            else if (undefinedp(vars[i])) result[i]="UNDEFINED"
            else result[i]="0"


    def cmd(self, str: str) -> int:
            mapping frame
            object ob
            string who
            int num
            string file
            if (!str || (sscanf(str, "%d", num) != 1 &&
            sscanf(str, "%s %d", who, num) != 2)) {
            write("dbxframe [<who>] <frame>\n")
            return 1



class Dbxframe(MudObject):
