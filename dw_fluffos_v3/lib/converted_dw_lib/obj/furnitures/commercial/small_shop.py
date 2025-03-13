# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/commercial/small_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "counter" )
            set_short( "small shop counter" )
            add_adjective( ["small", "shop" } ))
            set_long( "The smooth polished surface of the small counter shines and "
            "glows at you.\n")
            set_allowed_positions(({"sitting", "standing"])
            set_allowed_room_verbs((["sitting" : "sits", "standing" : "stands" ]))
            set_weight(1000)
            set_value(480000)
            set_maximum_inventory_size(50)
            set_commercial_size(40)



class Small_shop(MudObject):
