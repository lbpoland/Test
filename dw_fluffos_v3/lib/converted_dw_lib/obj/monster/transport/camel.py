# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/monster/transport/camel.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_race("camel")
            set_level(20)
            set_name("camel")
            set_long( "A ratty old camel with seemingly more knees than it should "
            "have.\n")
            set_inside_long( "Nothing smells worse than a camel.  Not even something "
            "from Dibbler's tray.\n")
            set_value(40000 * 12)
            set_maximum_speed(RIDE_GALLOP)
            set_transport_type( "camel" )
            set_default_mount_difficulty(150)
            set_default_direction_difficulty(150)
            set_wander_time( 60 + random(20) )
            set_gender( 1 + random(2) )
            set_transport_speed(1)
            set_maximum_exhaustion(400)
            set_transport_colour("off-yellow")



class Camel(MudObject):
