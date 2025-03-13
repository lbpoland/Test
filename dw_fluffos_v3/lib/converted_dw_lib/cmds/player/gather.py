# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/gather.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> int:
            object *items, *moved = [}), *left = [})
            int i
            if( !stringp(str) || (str == "" )) {
            add_failed_mess("Syntax: gather <plant>\n")
            return 0


    def query_patterns(self, ) -> Any:
            return ["<string>", (: cmd( $4[0] ) :)]



class Gather(MudObject):
