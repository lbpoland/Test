# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/cushions/frog_cushion.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "cushion" )
            set_short( "frog cushion" )
            add_adjective( ["frog", "green"] )
            add_alias( "pillow" )
            set_long( "This is a cushion that is the approximate shape of a "
            "frog that has been flattened by a cart.  It is covered in vivid "
            "green cordueroy.\n" )
            set_allowed_positions(({"sitting", "lying", "kneeling", "meditating",
            "crouching", "standing"}))
            set_allowed_room_verbs((["lying" : "lays", "hanging" : "hangs"]))
            set_weight(2)
            set_value(8000)



class Frog_cushion(MudObject):
