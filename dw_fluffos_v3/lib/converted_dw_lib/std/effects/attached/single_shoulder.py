# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/attached/single_shoulder.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def merge_effect(self, object, old_arg: int, new_arg: int) -> int:
            if (objectp(new_arg)) {
            new_arg = 0


    def restart(self, player: MudObject, handicap: int) -> None:
            player.adjust_bonus_dex( -handicap )


    def end(self, player: MudObject, handicap: int) -> None:
            if (intp(handicap)) {
            player.adjust_bonus_dex( handicap )



class Single_shoulder(MudObject):
