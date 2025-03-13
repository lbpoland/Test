# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/gumboot/gumboot1.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Gumboot Road")
            set_long("This is north end of Gumboot Road at the junction with Squash Square.\n")
            set_light( 80 )
            add_exit("north", SQUASH + "squash8", "road")
            add_exit("south", GUMBOOT + "gumboot2", "road")
            set_monster(1, "city")



class Gumboot1(MudObject):
