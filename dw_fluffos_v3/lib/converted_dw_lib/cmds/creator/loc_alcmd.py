# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/loc_alcmd.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            int flags, i, j, pos
            mixed flag_types
            object *obs
            string *coms, flag
            mixed *junk
            if (!str) str = ""
            flag_types = ["priority", "star", "function", "object"]
            while (strlen(str) && str[0] == '-') {
            if (sscanf(str, "-%s %s", flag, str) != 2) {
            flag = str[1..100]
            str = ""


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()



class Loc_alcmd(MudObject):
