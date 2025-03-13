# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/dry.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, things: Any) -> Any:
            {
            int pwet
            int twet
            int max
            int *enums
            object thing
            object with
            thing = things[0][0]
            with = things[1][0]
            if (!with.id("towel") && !with.query_property("dryer")) {
            return notify_fail("You can't dry anyone with " +
            (string) with.the_short() + ".\n")



class Dry(MudObject):
