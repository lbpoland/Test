# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/attached/riding.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def extra_look(self, player: MudObject) -> str:
            return player.query_pronoun() + " is riding on " +
            environment(player)->the_short()


    def query_classification(self, ) -> str:
            return "mudlib.riding.transport"


    def query_indefinate(self, ) -> int:
            return 1


    def restart(self, player: MudObject, riding: Any) -> None:



class Riding(MudObject):
