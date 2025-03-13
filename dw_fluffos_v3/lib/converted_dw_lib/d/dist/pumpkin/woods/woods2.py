# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/woods/woods2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Woods")
            set_long("This is the end of Woods\n")
            set_light( 80 )
            add_exit("north", WOODS + "woods1", "road")
            add_exit("south", WOODS + "woods3", "road")



class Woods2(MudObject):
