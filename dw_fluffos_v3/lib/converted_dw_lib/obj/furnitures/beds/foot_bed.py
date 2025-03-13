# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/beds/foot_bed.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("bed")
            set_short ("duck-footed bed")
            add_alias ("duck-footed")
            set_long(
            "A fairly solid timber bed, with intricate scrollwork around the "
            "headboard.  It is supported by four duck's feet, presumably made from "
            "painted wood.  The dark wood that form its sides is inset with short "
            "strips made from a lighter wood, creating an interestingly random "
            "pattern.\n")
            set_weight( 800 )
            set_value( 100000 )
            set_allowed_positions(({"sitting", "meditating", "lying", "standing",
            "kneeling", "crouching"}))
            set_allowed_room_verbs((["sitting" : "sits" ]))



class Foot_bed(MudObject):
