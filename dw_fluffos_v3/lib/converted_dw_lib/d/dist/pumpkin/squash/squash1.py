# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/squash/squash1.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("northwest corner of Squash Square")
            set_long("This is the north west corner of Squash Square\n")
            set_light( 80 )
            add_exit("east", SQUASH + "squash2", "road")
            add_exit("south", SQUASH + "squash4", "road")
            add_exit("southeast", SQUASH + "squash5", "hidden")
            add_property( "los", "open" )
            set_linker([PATH + "squash2", PATH + "squash4", PATH + "squash5"],
            "to a point", "", "Squash Square")
            set_zone("pumpkin")
            set_monster(1, "city")



class Squash1(MudObject):
