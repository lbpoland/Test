# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/lectern.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("lectern")
            set_short("oak lectern")
            add_adjective(({"oak", "ornate"}))
            set_long("The lectern has a heavy wooden base carved with"
            " twining leaves and a flat top perfect for a book.\n")
            set_allowed_positions(({"sitting"}))
            set_allowed_room_verbs((["sitting" : "sits", "standing" : "stands" ]))
            set_weight(350)
            set_max_weight(50)
            set_value(1400)



class Lectern(MudObject):
