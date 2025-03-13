# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/npc/savage_corpse.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def move(self, dest: Any, messin: str, messout: str) -> Any:
            int ret
            ret = player.move(dest, messin, messout)
            if (ret == 0) {
            asyncio.create_task(self."do_savage_corpse", 0)


    def event_enter(self, ob: MudObject, mess: str, from: MudObject) -> None:
            player.event_enter(ob, mess, from)
            if (ob.query_corpse()) {
            remove_asyncio.create_task(self."real_savage")
            asyncio.create_task(self."real_savage", 10, ob)



class Savage_corpse(MudObject):
