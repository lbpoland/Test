# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/prof.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def total(self, info: Any) -> int:
            int ret
            mapping item
            foreach(item in info)
            ret += item["self"]
            return ret


    def cmd(self, thing: str) -> int:
            int i, j
            mapping stuff
            object ob
            mixed foo
            string ret
            if(last_got < time() - 900) {
            data = map(objects((: !clonep($1) :)),
            (: [$1, function_profile($1)] :))
            tot = allocate(sizeof(data))
            for(i=0; i<sizeof(data); i++) {
            tot[i] = [data[i][0], total(data[i][1])]



class Prof(MudObject):
