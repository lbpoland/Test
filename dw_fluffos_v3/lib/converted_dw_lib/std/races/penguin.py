# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/penguin.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "penguin" )
            set_long( "Penguins are always rather formal.\n" )
            set_weight( 600 )
            remove_bit( "gizzard" )
            set_stats( [2, 8, -4, -4, -6] )


    def query_desc(self, ob: MudObject) -> str:
            return "Penguins are always rather formally dressed.\n"



class Penguin(MudObject):
