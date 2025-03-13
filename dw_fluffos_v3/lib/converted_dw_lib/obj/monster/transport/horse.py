# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/monster/transport/horse.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_race("horse")
            set_level(20)
            set_name("horse")
            set_gender( query_mount_gender() )
            set_long( "A nice dark dashing horse, " + query_pronoun() + " looks "
            "strong and happy as its brown eyes stare into your own.\n" )
            set_inside_long( "You can see the horses hair and ear's flicking at the "
            "slightest sounds.  The smell of horse is quite "
            "strong.\n" )
            set_value(40000 * 10)
            set_maximum_speed(RIDE_GALLOP)
            set_transport_type("horse")
            set_default_mount_difficulty(100)
            set_default_direction_difficulty(100)
            set_wander_time( 40 + random(10) )
            set_transport_speed(2)
            set_maximum_exhaustion(300)



class Horse(MudObject):
