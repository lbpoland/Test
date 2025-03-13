# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/object/horse.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, amount: int) -> None:
            player.submit_ee(0, amount, EE_REMOVE)
            player.add_extra_look(self)


    def merge_effect(self, player: MudObject, old_amount: int, new_amount: int) -> int:
            if (old_amount > new_amount)
            return old_amount
            return new_amount


    def query_shadow_ob(self, ) -> str:
            return SHADOWS+"shadow_horse"


    def survive_death(self, ) -> int:
            return 0


    def extra_look(self, player: MudObject) -> str:
            return capitalize((string)player.the_short()) +
            " is mounted on a large, black horse.\n"


    def end(self, player: MudObject, amount: int, id: int) -> None:
            player.remove_extra_look(self)



class Horse(MudObject):
