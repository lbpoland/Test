# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/latticed_screen.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "screen" )
            set_short( "latticed shoji screen" )
            add_adjective( ["latticed", "shoji"] )
            set_long( "This double-sided shoji screen has a latticed "
            "wood pattern made of ramin hardwood.  A lovely honey "
            "oak colour, the panelling is broken up by rice paper "
            "dividers which checker the screen from the top all "
            "the way down to the solid kick panel which runs along "
            "the bottom.\n")
            set_allowed_positions( ["standing", "sitting"] )
            set_allowed_room_verbs((["standing" : "stands", "sitting" : "sits" ]) )
            set_weight(20)
            set_value(400000)



class Latticed_screen(MudObject):
