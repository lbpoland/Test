# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/open_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_open_function(self, func: Any) -> None:
            _open_func = func


    def is_open(self, player: MudObject, type: int) -> int:
            if (_open_func) {
            return evaluate(_open_func, player, type)


    def test_open(self, ) -> int:
            return is_open( this_player(), 0 )



class Open_shop(MudObject):
