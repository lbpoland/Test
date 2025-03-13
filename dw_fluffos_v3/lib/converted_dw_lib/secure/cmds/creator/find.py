# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/find.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            string func, thing, s, ping
            object *obs, fish, user = this_player()
            object *list
            mixed *fnd
            int i, flags
            int k
            notify_fail("Usage: find [-a] [-d] [-n] function() <object(s)>\n")
            if (!str)
            return 0
            while (sscanf(str, "-%s %s", s, str) == 2)
            switch (s) {
            case "d":
            flags |= EXTRACT_CODE
            flags &= ~FIND_ALL
            break
            case "n":
            flags |= (LINE_NUMBERS | EXTRACT_CODE)
            flags &= ~FIND_ALL
            break
            case "a":
            flags = FIND_ALL
            break
            default:
            return notify_fail("Unknown option '"+ s +"'.\n")



class Find(MudObject):
