# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/chairs/chintz_chair.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "chair" )
            set_short( "overstuffed chintz chair" )
            add_adjective( ["overstuffed", "chintz"] )
            set_long("This is the type of fat, comfortable chair typically found "
            "in the parlours of fat, comfortable ladies.  The fabric covering "
            "it is bright yellow decorated with a rather aggressive-looking "
            "rose and cabbage design.\n")
            set_allowed_positions(["sitting", "meditating", "lounging"])
            set_allowed_room_verbs(([
            "sitting" : "sits",
            ]))
            set_weight(400)
            set_value(6000)



class Chintz_chair(MudObject):
