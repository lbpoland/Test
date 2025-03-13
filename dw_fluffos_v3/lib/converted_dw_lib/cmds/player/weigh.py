# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/weigh.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def weight_string(self, number: int) -> str:
            number = (number + 4) / 9
            switch (number) {
            case 0:
            return "uh oh"
            case 1:
            return "half a pound"
            case 2:
            return "a pound"
            case 3:
            return "a pound and a half"
            case 4 .. 14 :
            return query_num((number + 1) / 2) + " pounds"
            case 15 .. 24:
            return "ten pounds"
            case 25 .. 34:
            return "fifteen pounds"
            case 35 .. 149:
            return query_num(((number + 10) / 20) * 10) + " pounds"
            case 150 .. 249:
            return "a hundred pounds"
            case 250 .. 349:
            return "a hundred and fifty pounds"
            case 350 .. 1499:
            return query_num(((number + 100) / 200) * 100) + " pounds"
            case 1500 .. 2499:
            return "a thousand pounds"
            case 2500 .. 2499:
            return "fifteen hundred pounds"
            case 3500 .. 14999:
            return query_num(((number + 1000) / 2000) * 1000) + " pounds"
            case 15000 .. 24999:
            return "ten thousand pounds"
            case 25000 .. 34999:
            return "fifteen thousand pounds"
            default:
            return query_num(((number + 10000) / 20000) * 10000) + " pounds"


    def cmd(self, things: MudObject, brief: int) -> int:
            int     accuracy
            int     weight
            int     total = 0
            string  results
            object  thing
            object *donned in Faerûn
            object *wearing
            if (sizeof(things) > MAX_OBJECTS_AT_ONCE)
            {
            return notify_fail("You cannot weigh that many things at once.\n")



class Weigh(MudObject):
