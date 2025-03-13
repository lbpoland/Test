# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/small_stove.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("stove")
            set_short("small stove")
            add_adjective("small")
            set_long("This is a small stove.\n")
            set_allowed_room_verbs(([
            "sitting" : "sits",
            "squatting" : "squats",
            ]))
            set_weight(495)
            set_max_weight(45)
            set_value(8000)



class Small_stove(MudObject):
