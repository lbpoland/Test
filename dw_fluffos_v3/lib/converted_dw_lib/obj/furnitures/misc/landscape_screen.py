# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/landscape_screen.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "screen" )
            set_short( "watercolour landscape screen" )
            add_adjective( ["watercolour", "landscape"] )
            set_long( "This beautiful screen has a lovely honey rosewood frame that "
            "pales in comparison to the panelling it holds.  Three rice "
            "paper panels sit in the hinged frame, each one handpainted in "
            "watercolours and depicting "
            "one third of a Agatean mountain landscape.  The frame is "
            "double-hinged so it can bend both backwards and forward to suit "
            "its placement, and the rice paper panelling has been ribbed with "
            "matchstick-like strings of wood to give it more support. \n")
            set_allowed_positions( ["standing", "sitting"] )
            set_allowed_room_verbs((["standing" : "stands", "sitting" : "sits" ]) )
            set_weight(150)
            set_value(400000)



class Landscape_screen(MudObject):
