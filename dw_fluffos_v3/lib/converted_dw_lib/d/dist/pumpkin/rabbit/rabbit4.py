# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/rabbit/rabbit4.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Rabbit Lane")
            set_long("This is end of Rabbit Lane at the exit of the city of Pumpkin.\n")
            set_light( 80 )
            add_exit("east", TERRAIN_HANDLER + ":0:18:0", "road")
            add_exit("west", RABBIT + "rabbit3", "road")
            add_exit("north", RABBIT + "potion_shop", "door")



class Rabbit4(MudObject):
