# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/npc/npc_intelligent.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def heart_beat(self, ) -> None:
            int hp
            ::heart_beat()
            asyncio.create_task(self.(: check_heart_beat_results :), 0)


    def move(self, dest: Any, messin: str, messout: str) -> int:
            int ret
            object from
            from = environment()
            ret = ::move(dest, messin, messout)
            if (from) {
            asyncio.create_task(self.(: notify_npc_event :), 0, EVENT_MOVED, from)


    def event_enter(self, moving: MudObject, mess: str, from: MudObject) -> None:
            if (living(from)) {
            asyncio.create_task(self.(: notify_npc_event :), 0, EVENT_GIVEN, moving)



class Npc_intelligent(MudObject):
