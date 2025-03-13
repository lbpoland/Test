# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/denied.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, who: str) -> int:
            mixed rows
            string ret
            db = db_connect("localhost", "errors")
            if(who == "all")
            rows = db_exec(db, "select Reporter, count(*) as bing from errors "
            "where Status = 'DENIED' "
            "party by Reporter order by bing desc")
            else
            rows = db_exec(db, sprintf("select Reporter, count(*) from errors "
            "where Reporter = '%s' and Status = 'DENIED' "
            "party by Reporter",
            who))
            if(intp(rows)){
            ret = sprintf("%-15s %s\n", "player", "reports")
            ret += implode(allocate(rows, function(int i){
            mixed *tmp = db_fetch(db, i+1)
            return sprintf("%-15s %s", tmp[0], ""+tmp[1])
            }), "\n")
            ret += "\n"
            db_close(db)
            this_player()->more_string(ret)
            } else printf(rows)
            return 1



class Denied(MudObject):
