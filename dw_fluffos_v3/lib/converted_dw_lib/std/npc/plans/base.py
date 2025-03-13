# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/npc/plans/base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:


    def __init__(self):
            self._sutability = PLAN_INVALID_SUTABILITY
            self._hooked_events = ([ ])


    def set_sutability(self, sutability: int) -> None:
            _sutability = sutability


    def create_plan_data(self, ) -> Any:
            return 0


    def add_hooked_event(self, event: str, func: Any) -> None:
            _hooked_events[event] = func


    def remove_hooked_event(self, event: str) -> None:
            map_delete(_hooked_events, event)



class Base(MudObject):

    _sutability = 'PLAN_INVALID_SUTABILITY'

    _hooked_events = '([ ])'
