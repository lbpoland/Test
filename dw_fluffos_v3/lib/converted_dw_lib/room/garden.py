# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/room/garden.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light(70)
            set_short("Statue garden")
            set_long(
            "This is a nice garden.  Scattered amongst the garden you notice amazingly "+
            "accurate statues of people.\n")
            add_exit("drum", CONFIG_START_LOCATION, "path")
            add_item("garden",
            "It is a lovely garden, nice little walk ways drifting off into "+
            "the distance.  Lovely little sheltered groves and grotos.")
            add_item("statue",
            "Very life like statues of people.  Amazing what they can do "+
            "these days.")



class Garden(MudObject):
