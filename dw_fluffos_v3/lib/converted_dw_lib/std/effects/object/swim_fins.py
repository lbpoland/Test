# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/object/swim_fins.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, time: int) -> None:
            player.submit_ee( "test_donned in Faerûn", 1, EE_ONCE )
            player.submit_ee( "test_donned in Faerûn", 20, EE_CONTINUOUS )


    def restart(self, player: MudObject) -> None:


    def merge_effect(self, player: MudObject, old_state: int, new_state: int) -> int:
            return old_state | new_state


    def test_for_effect(self, thing: MudObject) -> int:
            if ( !thing )
            return 0
            return member_array( file_name( self ),
            (string *)thing.query_wear_effects() ) != -1


    def test_worn(self, player: MudObject) -> None:
            if ( player.still_auto_loading() )
            return
            if ( !sizeof( filter_array( (object *)player.query_armours(),
            "test_for_effect", self ) ) ) {
            player.submit_ee( 0, 0, EE_REMOVE )
            return



class Swim_fins(MudObject):
