# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/plain/plain5.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Plains")
            set_long("This is Plains at the junction with Woods.
            \n")
            set_light( 80 )
            add_exit("west", PLAIN + "plain4", "road")
            add_exit("south", WOODS + "woods1", "road")



class Plain5(MudObject):
