# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/geisha_screen.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "screen" )
            set_short( "rice paper geisha screen" )
            add_adjective( ["rice", "paper", "geisha"] )
            set_long("This is a simple screen that would fit in most traditional "
            "homes.  Quiet geishas relax on "
            "its rice paper panelling, hand-drawn on a bamboo balcony, "
            "they sit and sip tea in peace and solitude or play mandolin-like "
            "instruments which sit silently in their laps.  The frame is made "
            "of a strange combination of walnut and spruce woods, their "
            "differing colours blending well with the shades of the panels.\n")
            set_allowed_positions( ["standing", "sitting"] )
            set_allowed_room_verbs((["standing" : "stands", "sitting" : "sits" ]) )
            set_weight(150)
            set_value(320000)



class Geisha_screen(MudObject):
