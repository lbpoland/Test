# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/bamboo_screen.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "screen" )
            set_short( "bamboo matchstick screen" )
            add_adjective( ["bamboo", "matchstick"] )
            set_long( "This double-sided screen has been constructed by "
            "lashing long bamboo poles together so that "
            "four distinct interconnected panels are hinged "
            "together when it is standing.  A lovely tan colour, "
            "the texture is rough and the knots in the wood give it "
            "a rustic minimalist look.\n")
            set_allowed_positions( ["standing", "sitting"] )
            set_allowed_room_verbs((["standing" : "stands", "sitting" : "sits" ]) )
            set_weight(20)
            set_value(400000)



class Bamboo_screen(MudObject):
