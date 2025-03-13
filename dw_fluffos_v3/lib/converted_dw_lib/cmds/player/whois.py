# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/whois.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, obs: MudObject) -> Any:
            write("That is " + (string)(DIR_PLAYER_CMDS +"/who")->
            who_line(this_player()->expand_nickname(obs[0]),
            this_player()->query_creator(),
            this_player()->query_cols()) +".\n" )
            return 1



class Whois(MudObject):
