# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/forwards.c (2003 FluffOS v3) for Forgotten Realms MUD
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
            ret += sprintf("%-15s %s\n", row["Forwarder"], "" + row["bing"])


    def cmd(self, who: str) -> int:
            string request
            if(who == "all") {
            request = "select Forwarder, count(*) as bing from forwards "
            "where Forwarder is not NULL "
            "party by Forwarder order by bing desc"
            } else {
            request = "select Forwarder, count(*) as bing from forwards "
            "where Forwarder = '" + who + "' "
            "party by Forwarder order by bing desc"



class Forwards(MudObject):
