# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/rstats.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> int:
            mapping stats
            string obj, file
            int total, num
            stats = "/secure/master"->query_read_stats()
            if(str) {
            if(!stats[str])
            return notify_fail("No such file\n")
            foreach(file in keys(stats[str])) {
            if(stats[str][file] > 1)
            printf("%-60s %5d\n", file, stats[str][file])



class Rstats(MudObject):
