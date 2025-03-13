# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/room/morgue.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "morgue")
            add_property( "determinate", "the " )
            add_property( "no teleport", 1 )
            set_light( 100 )
            set_long("Lots of bodies stacked end on end in long rows.  It looks "
            "like they have stopped sleeping.\n")



class Morgue(MudObject):
