# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/crane_umbrella_stand.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("stand")
            set_short("lacquered umbrella stand")
            add_adjective( ["lacquered", "umbrella"] )
            set_long("This is a conical umbrella stand that raises in an eight-sided "
            "cylinder.  Often placed by front doors to house the clothing "
            "accessories that are most-loathed, this particular stand is "
            "especially peculiar and eye-catching.  Lacquered with several "
            "shades of beige, green, and brown enamel, its faces boast an "
            "elegant crane taking off from a marshy landscape.\n")
            set_open()
            set_stuck(1)
            set_weight(90)
            set_max_weight(55)
            set_value(40000)
            set_allowed_room_verbs( ([ "squatting" : "squats",
            "resting" : "rests",
            "sitting" : "sits",
            "standing" : "stands" ]) )



class Crane_umbrella_stand(MudObject):
