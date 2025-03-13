# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/squash/squash8.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("south edge of Squash Square")
            set_long("This is south side of Squash Square at the "
            "junction with Gumboot Road.\n")
            set_light( 80 )
            add_exit("east", SQUASH + "squash9", "road")
            add_exit("west", SQUASH + "squash7", "road")
            add_exit("north", SQUASH + "squash5", "road")
            add_exit("south", GUMBOOT + "gumboot1", "road")
            add_exit("northwest", SQUASH + "squash4", "hidden")
            add_exit("northeast", SQUASH + "squash6", "hidden")
            add_property( "los", "open" )
            set_linker( [PATH + "squash9", PATH + "squash7", PATH + "squash5",
            PATH + "squash4", PATH + "squash6"],
            "into", "", "Squash Square")
            set_zone("pumpkin")
            set_monster(1, "city")



class Squash8(MudObject):
