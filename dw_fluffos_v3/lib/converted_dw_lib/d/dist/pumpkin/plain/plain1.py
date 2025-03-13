# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/plain/plain1.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Plains")
            set_long("This is Plains at the junction with Rabbit Lane.
            \n")
            set_light( 80 )
            add_exit("east", PLAIN + "plain2", "road")
            add_exit("west", RABBIT + "rabbit4", "road")



class Plain1(MudObject):
