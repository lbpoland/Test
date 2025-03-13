# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/gnome.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "gnome" )
            set_long( "This is the race for gnomes.\n" )
            set_desc( "a short-looking gnome" )
            set_weight( 25 )
            set_height( 20 )
            set_sight( [0, 5, 150, 200] )
            set_stats( [-2, 8, 0, 6, 0] )



class Gnome(MudObject):
