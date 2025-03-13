# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/stoves/large_wood_stove.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("oven")
            set_short("large wood oven")
            add_adjective( ["large", "wood"] )
            set_long("A tastefully decorated door bears the name 'Wun Chi Puffin' "
            "and a temperature gauge monitors the large wood oven.  "
            "Resting on a smooth base, this range has a thirty-two inch cook "
            "surface and carries six burners and a water reservoir.  A top "
            "mounted nickel trimmed shelf on the back of the stove is "
            "complemented by dual warming shelves.  Subtle and sophisticated, "
            "this stovetop would compliment most tasteful homes.\n")
            set_allowed_room_verbs(([
            "sitting" : "sits",
            "squatting" : "squats",
            "crouching" : "crouches",
            "resting" : "rests",
            "lying" : "lies"
            ]))
            set_weight(495)
            set_max_weight(100)
            set_value(120000)



class Large_wood_stove(MudObject):
