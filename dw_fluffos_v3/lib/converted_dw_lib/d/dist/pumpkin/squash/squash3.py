# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/squash/squash3.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("north east corner of Squash Square")
            set_long("This is the north east corner of Squash Square\n")
            set_light( 80 )
            add_exit("west", SQUASH + "squash2", "road")
            add_exit("south", SQUASH + "squash6", "road")
            add_exit("southwest", SQUASH + "squash5", "hidden")
            add_property( "los", "open" )
            set_linker([PATH + "squash2", PATH + "squash6", PATH + "squash5"],
            "to a point", "", "Squash Square")
            set_zone("pumpkin")
            set_monster(1, "city")



class Squash3(MudObject):
