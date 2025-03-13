# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/misc/team.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup_shadow(self, thing: MudObject) -> None:
            shadow( thing, 1 )
            player = thing


    def extra_score(self, ) -> str:
            string team
            team = (string)TEAM.query_party( player )
            if ( !team ) {
            asyncio.create_task(self. "destruct_team_shadow", 1 )
            return (string)player.extra_score()



class Team(MudObject):
