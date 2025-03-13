# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/mortar_pestle.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "pestle" )
            set_short( "mortar and pestle" )
            set_long( "Roughly hewn from stone, the mortar's bowl has been "
            "smoothed from long use.  The stone pestle used for grinding "
            "herbs within the bowl is smooth as well and hangs from a "
            "leather thong tied through a ring in the side of the bowl.\n" )
            set_main_plural( "mortars and pestles" )
            add_adjective( ["mortar and", "rough", "stone", "smooth"] )
            add_alias( ["mortar", "pestle", "bowl"] )
            set_value( 800 )
            set_weight( 44 )
            set_max_grindable( 8 )
            set_max_weight( 8 )



class Mortar_pestle(MudObject):
