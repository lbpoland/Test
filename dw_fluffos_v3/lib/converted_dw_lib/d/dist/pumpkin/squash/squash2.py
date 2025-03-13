# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/squash/squash2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("north edge of Squash Square")
            set_long("This is the north of Squash Square at the "
            "junction with Pumpkin Way.\n")
            set_light( 80 )
            add_exit("east", SQUASH + "squash3", "road")
            add_exit("west", SQUASH + "squash1", "road")
            add_exit("north", PUMPKIN + "pumpkin6", "road")
            add_exit("south", SQUASH + "squash5", "road")
            add_exit("southwest", SQUASH + "squash4", "hidden")
            add_exit("southeast", SQUASH + "squash6", "hidden")
            set_linker([PATH + "squash3", PATH + "squash1", PATH + "squash5",
            PATH + "squash4", PATH + "squash6"],
            "into", "", "Squash Square")
            set_zone("pumpkin")
            set_monster(1, "city")



class Squash2(MudObject):
