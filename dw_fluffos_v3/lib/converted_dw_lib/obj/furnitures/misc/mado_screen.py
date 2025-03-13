# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/mado_screen.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "screen" )
            set_short( "mado screen" )
            add_adjective( "mado" )
            set_long( "This traditional mado screen has a double-sided "
            "latticework frame made of lacquered red cedar.  Between "
            "the two sides of the frame lies a large sheet of smooth "
            "white rice paper that looks quite delicate and "
            "fragile.  \n")
            set_allowed_positions( ["standing", "sitting"] )
            set_allowed_room_verbs((["standing" : "stands", "sitting" : "sits" ]) )
            set_weight(150)
            set_value(350000)



class Mado_screen(MudObject):
