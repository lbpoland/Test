# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/mem_stat.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            int memtotal, limit, i = TP.query_cols() -7 -1, j
            string ret, str2, str3
            object *objlist
            if (!str || str == "")
            return notify_fail(help())
            while (strlen(str) && str[0] == ' ')
            str = str[1..]
            if (sscanf(str, "-%s%d %s", str3, limit, str2) == 3) {
            if (str3[0..0] != "l")
            return notify_fail("Error: Only valid character following '-' is 'l' at "
            "this time.\n")
            str = str2


    def help(self, ) -> str:
            return "Usage: memstat [-l<number>] [<filename(s)>|<wiz_present syntax>]\n\n"
            "Memstat lists the guestimated amount of memory the specified object(s) use. "
            "Using the -l option, a maximum amount of objects to be listed may be "
            "specified otherwise a default limit of "+ OBJ_LIMIT +" objects are listed. "
            "Paths including wildcards are taken as a way of specifying more than one "
            "file.\n"



class Mem_stat(MudObject):
