# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/outdoor/bird_bath.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "birdbath" )
            set_short( "stone bird bath" )
            add_adjective( ["stone", "bird", "bath"] )
            add_alias( ["bath", "bird bath"] )
            set_long( "This is a block of stone that has been chiseled and hacked into "
            "a vaguely bird bath shape.  It is really quite ugly.  Fortunately, birds "
            "don't seem to be art critics.  The base of the bird bath is made of some "
            "sort of porous stone that resembles Dwarf Bread in texture.\n" )
            set_allowed_positions(({"sitting","standing"}))
            set_allowed_room_verbs((["standing" : "stands" ]))
            set_weight(200)
            set_value(4000)



class Bird_bath(MudObject):
