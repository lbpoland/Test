# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/iron_hatstand.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "stand" )
            set_short( "wrought iron hat stand" )
            add_adjective( ["wrought", "iron", "hat"] )
            add_alias( ["hatstand", "rack", "hat rack", "hatrack"] )
            add_plural( "wrought iron hat stands" )
            set_long("This is a solid hat stand made of gracefully designed "
            "wrought iron.  It rests on four clawed feet, while the base "
            "of the stand wraps around itself in a spiral.  There are "
            "plenty of hooks at the top.\n")
            set_weight(250)
            set_max_weight(200)
            set_allowed_room_verbs(([ "standing" : "stands" ]))
            set_put_aliases( ["hang"] )
            set_value(9000)



class Iron_hatstand(MudObject):
