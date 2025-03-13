# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/burnt_bamboo_screen.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "screen" )
            set_short( "burnt bamboo screen" )
            add_adjective( ["burnt", "bamboo"] )
            set_long( "This screen has been constructed by "
            "weaving hundreds of lashes of bamboo together to form a tight "
            "mesh that blocks out any chance of peeking through to see what's "
            "on the other side.  The bamboo, lovely in differing shades of "
            "tan through to chocolate brown, is supported by long poles which "
            "make up the frame and hinge the entire structure together.\n")
            set_allowed_positions( ["standing", "sitting"] )
            set_allowed_room_verbs((["standing" : "stands", "sitting" : "sits" ]) )
            set_weight(150)
            set_value(400000)



class Burnt_bamboo_screen(MudObject):
