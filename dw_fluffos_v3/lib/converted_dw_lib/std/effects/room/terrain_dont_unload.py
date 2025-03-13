# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/room/terrain_dont_unload.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, arg: Any) -> Any:
            player.setup_shad()
            return arg


    def merge_effect(self, player: MudObject, old: Any, newish: Any) -> Any:
            player.setup_shad()
            return newish



class Terrain_dont_unload(MudObject):
