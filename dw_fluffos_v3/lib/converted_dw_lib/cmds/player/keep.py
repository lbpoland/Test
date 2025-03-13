# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/keep.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, obs: MudObject) -> int:
            object thing
            foreach(thing in obs) {
            thing.add_effect( EFFECT, ([ "keep" : 1 ]) )


    def cmd_list(self, ) -> int:
            object* obs
            obs = all_inventory(this_player())
            obs = filter(obs, (: $1.query_keep() :) )
            if (!sizeof(obs)) {
            add_failed_mess("You are not keeping anything.\n")
            return 0



class Keep(MudObject):
