# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/curses/alone.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, time: int) -> int:
            player.add_extra_look( self )


    def merge_effect(self, player: MudObject, time1: int, time2: int) -> None:


    def end(self, player: MudObject) -> None:
            player.remove_extra_look( self )


    def extra_look(self, player: MudObject) -> str:
            if ( player == this_player() )
            return ""
            return capitalize( (string)player.query_pronoun() )+
            " can't see you.\n"



class Alone(MudObject):
