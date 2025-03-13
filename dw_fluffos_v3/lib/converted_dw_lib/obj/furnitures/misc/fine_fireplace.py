# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/fine_fireplace.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_allowed_positions(({"sitting"}))
            set_allowed_room_verbs((["sitting" : "sits" ]))
            set_weight(700)
            set_max_weight(100)
            set_short("finely crafted fireplace")
            set_long("This fireplace is surrounded by an ornately carved mahogany "
            "framework and has a beautifully finished brass hearth.\n")
            set_value(900000)



class Fine_fireplace(MudObject):
