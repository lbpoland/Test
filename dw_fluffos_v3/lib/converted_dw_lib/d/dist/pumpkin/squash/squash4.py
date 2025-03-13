# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/squash/squash4.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("west edge of Squash Square")
            set_long("This is the west side of Squash Square at the junction "
            "with Fruitbat Avenue.\n")
            set_light( 80 )
            add_exit("east", SQUASH + "squash5", "road")
            add_exit("west", FRUITBAT + "fruitbat4", "road")
            add_exit("north", SQUASH + "squash1", "road")
            add_exit("south", SQUASH + "squash7", "road")
            add_exit("northeast", SQUASH + "squash2", "hidden")
            add_exit("southeast", SQUASH + "squash8", "hidden")
            add_property( "los", "open" )
            set_linker([PATH + "squash5", PATH + "squash1", PATH + "squash7",
            PATH + "squash2", PATH + "squash8"],
            "into", "", "Squash Square")
            set_zone("pumpkin")
            set_monster(1, "city")



class Squash4(MudObject):
