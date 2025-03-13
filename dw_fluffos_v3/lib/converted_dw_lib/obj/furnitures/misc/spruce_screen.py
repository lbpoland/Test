# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/spruce_screen.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "screen" )
            set_short( "double cross spruce screen" )
            add_adjective( ["double", "cross", "spruce"] )
            set_long( "This double-sided screen has been constructed by "
            "lashing pairs of long spruce strips together so that "
            "three distinct interconnected panels are hinged "
            "together when it is standing.  The frame, decorated with "
            "criss-crossed pairs of spruce poles, is covered by a "
            "thin layer of rice paper that breaks up light and "
            "sheds a warm glow on a room when a lamp is placed behind it.\n")
            set_allowed_positions( ["standing", "sitting"] )
            set_allowed_room_verbs((["standing" : "stands", "sitting" : "sits" ]) )
            set_weight(150)
            set_value(400000)



class Spruce_screen(MudObject):
