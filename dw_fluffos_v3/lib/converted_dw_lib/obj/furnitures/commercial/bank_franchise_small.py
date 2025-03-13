# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/commercial/bank_franchise_small.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "counter" )
            set_short( "small bank counter" )
            add_alias("bank")
            add_adjective( ["small", "bank" } ))
            set_long( "A heavily armoured and hardwood counter "
            "with a safe embedded into the surface.\n")
            set_allowed_positions(({"sitting", "standing"])
            set_allowed_room_verbs((["sitting" : "sits", "standing" : "stands" ]))
            set_weight(1000)
            set_value(400000)
            set_commercial_size(10)
            set_maximum_total_difference(200000)



class Bank_franchise_small(MudObject):
