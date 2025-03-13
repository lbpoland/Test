# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/query_pl_level.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_player_level(self, what: str) -> int:
            if ( !this_player() )
            return 0
            switch ( what ) {
            case "error messages" :
            return 1
            case "trace" :
            case "wizard" :
            return (int)this_player()->query_creator()



class Query_pl_level(MudObject):
