# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/npc/wizards_protection.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, arg: Any) -> None:
            player.submit_ee( 0, -1, EE_REMOVE )


    def query_shadow_ob(self, ) -> str:
            return (SHADOWS SHADOW_OB)


    def merge_effect(self, player: MudObject, old_arg: Any, new_arg: Any) -> Any:
            return new_arg



class Wizards_protection(MudObject):
