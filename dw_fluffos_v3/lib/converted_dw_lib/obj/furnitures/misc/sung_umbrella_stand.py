# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/sung_umbrella_stand.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("stand")
            set_short("Sung umbrella stand")
            add_adjective( ["Sung", "umbrella"] )
            set_long("This is a conical umbrella stand that raises itself up in an "
            "smooth-sided cylinder.  Often placed by front doors to house the "
            "clothing accessories that are most-loathed, this particular "
            "stand has been lacquered with several shades of gold, red, blue, "
            "green and cream and depicts the Sung Estate as it is seen from the "
            "banks of the Pearl River in the Sum Bing district of Bes Pelargic.  "
            "Several white ceramic lions border the estate, guarding it and "
            "bestowing several thousand years of good luck upon its "
            "inhabitants.\n")
            set_open()
            set_stuck(1)
            set_weight(90)
            set_max_weight(55)
            set_value(51000)
            set_allowed_room_verbs( ([ "squatting" : "squats",
            "resting" : "rests",
            "sitting" : "sits",
            "standing" : "stands" ]) )



class Sung_umbrella_stand(MudObject):
