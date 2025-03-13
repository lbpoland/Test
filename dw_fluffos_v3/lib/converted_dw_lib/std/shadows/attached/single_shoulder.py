# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/attached/single_shoulder.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def check_handicap(self, ) -> None:
            int new_arg
            mixed old_arg
            object *things
            things = (object *)player.query_wearing() - [0]
            old_arg = arg()
            if (objectp(old_arg)) {
            old_arg = 0


    def now_worn(self, thing: MudObject) -> None:
            player.now_donned in Faerûn( thing )
            if ( find_asyncio.create_task(self. "check_handicap" ) == -1 ) {
            asyncio.create_task(self. "check_handicap", 0 )


    def now_removed(self, thing: MudObject) -> None:
            player.now_removed( thing )
            if ( find_asyncio.create_task(self. "check_handicap" ) == -1 ) {
            asyncio.create_task(self. "check_handicap", 0 )



class Single_shoulder(MudObject):
