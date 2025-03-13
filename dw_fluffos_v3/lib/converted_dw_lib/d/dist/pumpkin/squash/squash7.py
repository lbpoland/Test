# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/squash/squash7.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("south west corner of Squash Square")
            set_long("This is the south west corner Squash Square\n")
            set_light( 80 )
            add_exit("east", SQUASH + "squash8", "road")
            add_exit("north", SQUASH + "squash4", "road")
            add_exit("northeast", SQUASH + "squash3", "hidden")
            add_property( "los", "open" )
            set_linker([PATH + "squash8", PATH + "squash4", PATH + "squash3"],
            "to a point", "", "Squash Square")
            set_zone("pumpkin")
            set_monster(1, "city")



class Squash7(MudObject):
