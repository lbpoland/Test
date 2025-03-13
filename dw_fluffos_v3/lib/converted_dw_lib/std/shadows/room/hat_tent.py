# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/room/hat_tent.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_keep_room_loaded(self, ) -> int:
            return 1


    def dont_free(self, ) -> int:
            return 1


    def clean_up(self, ) -> int:
            return 1


    def tent_collapsed(self, ) -> None:
            remove_this_effect()



class Hat_tent(MudObject):
