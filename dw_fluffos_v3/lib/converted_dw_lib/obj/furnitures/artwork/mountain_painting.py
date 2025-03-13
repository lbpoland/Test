# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/artwork/mountain_painting.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "painting" )
            set_short( "painting of a misty mountain range" )
            add_adjective( ["of", "a", "misty", "mountain", "range"] )
            set_long( "This is a watercolour painting of a range of "
            "mountains skirting a misty lake.  Fiery red trees "
            "border the indescript water's edge, snaking their "
            "branches out horizontally more than vertically.  "
            "The mountains have been painted complementing "
            "shades of steel grey and persian blue, while the "
            "water itself is a strangely creamy white.\n" )
            set_weight( 40 )
            set_value( 46775 )
            set_allowed_positions( ({"hanging"}) )
            set_allowed_room_verbs((["hanging" : "hangs",
            "sitting" : "sits",
            "dangling" : "dangles",
            "standing" : "stands" ]))



class Mountain_painting(MudObject):
