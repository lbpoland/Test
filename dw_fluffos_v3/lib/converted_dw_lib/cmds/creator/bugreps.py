# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/bugreps.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def finish_request(self, type: int, data: Any, person: MudObject) -> None:
            string ret
            mapping row
            if (type == DB_SUCCESS) {
            ret = ""
            foreach (row in data) {
            ret += sprintf("%-15s %s\n", row["Reporter"], "" + row["bing"])


    def cmd(self, who: str) -> int:
            string request
            if(who == "all") {
            request = "select Reporter, count(*) as bing from errors "
            "party by Reporter order by bing desc"
            } else {
            request = "select Reporter, count(*) as bing from errors "
            "where Reporter = '" + who + "'"
            "party by Reporter order by bing desc"



class Bugreps(MudObject):
