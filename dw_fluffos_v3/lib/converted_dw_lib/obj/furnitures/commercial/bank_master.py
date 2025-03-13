# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/commercial/bank_master.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "counter" )
            set_short( "master bank counter" )
            add_alias("bank")
            add_adjective( ["master", "bank" } ))
            set_long( "A heavily armoured and hardwood counter "
            "with a safe embedded into the surface.\n")
            set_allowed_positions(({"sitting", "standing"])
            set_allowed_room_verbs((["sitting" : "sits", "standing" : "stands" ]))
            set_weight(1000)
            set_value(16000000)
            set_commercial_size(91)
            set_shop_use_types(["bank", "withdraw", "deposit"])



class Bank_master(MudObject):
