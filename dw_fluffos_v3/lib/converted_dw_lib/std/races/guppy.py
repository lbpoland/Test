# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/guppy.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "guppy" )
            set_long( "Fish,  yes.  A fish.  Nice generic standard fish thing.\n" )
            set_height( 15 )
            set_weight( 40 )
            set_desc( "a beautiful looking guppy" )
            set_stats( [-2, 14, -4, -4, -6] )


    def start_player(self, thing: MudObject) -> None:
            ::start_player( thing )
            thing.add_property( "gills", 1 )
            thing.tactics( "response dodge" )



class Guppy(MudObject):
