# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/curses/no_player_title.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, ob: MudObject, time: int, id: int) -> None:
            if ( time > 0 ) {
            ob.submitt_ee( 0, time, EE_REMOVE )


    def end(self, ob: MudObject, time: int, id: int) -> None:


    def query_classification(self, ) -> str:
            return "player.no-title-allowed"


    def query_shadow_ob(self, ) -> str:
            return SHADOWS + "no_player_title"


    def spam(self, player: MudObject, args: Any, id: int) -> None:
            tell_creator ("taffyd", "Spam\n" )



class No_player_title(MudObject):
