# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/monster/transport/warhorse.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_race("horse")
            set_level(50)
            set_name("horse")
            add_adjective("war")
            set_gender( query_mount_gender() )
            set_long( "This horse has an air of calmness about " + query_objective() + ", "
            + query_pronoun() + " just stands there and looks very calm.\n" )
            set_inside_long( "You can see the horses mane and " + query_objective() + " "
            "looking calmly as possible into the distance.\n")
            set_value(40000 * 10)
            set_maximum_speed(RIDE_GALLOP)
            set_transport_type("horse")
            set_default_mount_difficulty(100)
            set_default_direction_difficulty(20)
            set_wander_time( 50 + random(10) )
            set_transport_speed(3)
            set_maximum_exhaustion(600)
            adjust_bonus_str(5)
            adjust_bonus_con(5)



class Warhorse(MudObject):
