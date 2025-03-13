# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/sideboards/marquetry_sideboard.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "sideboard" )
            set_short( "marquetry sideboard" )
            add_alias( "table" )
            add_adjective( ["marquetry"}) )
            set_long("This is a long table specifically designed to rest "
            "against a wall.  The marquetry effect on the top surface has been "
            "arranged to represent the Assassins' Guild coat of arms. \n")
            set_allowed_positions(["sitting", "lying", "squatting", "standing"}))
            set_allowed_room_verbs((["sitting" : "sits", "standing" : "stands"]))
            set_weight(360)
            set_max_weight(200)
            set_value(100000)
            set_allow_use_internals(1)



class Marquetry_sideboard(MudObject):
