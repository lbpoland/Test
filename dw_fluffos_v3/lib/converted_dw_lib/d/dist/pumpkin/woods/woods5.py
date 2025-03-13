# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/woods/woods5.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Woods")
            set_long("This is Woods at the junction with Desert.
            \n")
            set_light( 80 )
            add_exit("north", WOODS + "woods4", "road")
            add_exit("south", DESERT + "desert10", "road")



class Woods5(MudObject):
