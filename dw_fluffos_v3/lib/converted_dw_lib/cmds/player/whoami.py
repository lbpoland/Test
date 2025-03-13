# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/whoami.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> Any:
            write( "You are "+ (string)( DIR_PLAYER_CMDS +"/who" )->
            who_line(this_player(), this_player()->query_creator(),
            this_player()->query_cols(), 1) +".\n" )
            return 1



class Whoami(MudObject):
