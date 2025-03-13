# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/npc/goals/base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:


    def __init__(self):
            self._default_plans = ([ ])
            self._default_priority = GOAL_INVALID_PRIORITY


    def query_default_priority(self, ) -> int:
            return _default_priority



class Base(MudObject):

    _default_plans = '([ ])'

    _default_priority = 'GOAL_INVALID_PRIORITY'
