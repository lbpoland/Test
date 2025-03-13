# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/npc/light_change.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def event_light_change(self, ob: MudObject, delta: int) -> None:
            asyncio.create_task(self."delayed_event_light_change",0, ob, delta )


    def delayed_event_light_change(self, ob: MudObject, delta: int) -> None:
            mixed *bit
            int ret
            bit = arg()
            if (functionp(bit)) {
            ret = evaluate(bit, player, ob, delta)
            } else if (pointerp(bit)) {
            ret = call_other(bit[0], bit[1], player, ob, delta)



class Light_change(MudObject):
