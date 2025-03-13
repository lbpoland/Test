# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/bathroom/bath.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("bathtub")
            set_short("cast iron bathtub")
            add_adjective(({"cast", "iron"}))
            add_alias( ["tub", "bath"] )
            set_long("The white porcelain sparkles on this cast iron bathtub, it looks "
            "heavy but large enough for a couple of people to have a nice "
            "bath in.\n")
            set_allowed_positions( ({"sitting", "standing", "lying"] )
            set_allowed_room_verbs((["sitting" : "sits", "standing" : "stands" ]))
            set_weight(350)
            set_value(14000)



class Bath(MudObject):
