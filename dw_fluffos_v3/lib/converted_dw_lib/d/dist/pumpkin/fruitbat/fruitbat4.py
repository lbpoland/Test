# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/fruitbat/fruitbat4.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Fruitbat Avenue")
            set_long("This is east end of Fruitbat Avenue at the junction "
            "with Squash Square.\n")
            set_light( 80 )
            add_exit("east", SQUASH + "squash4", "road")
            add_exit("west", FRUITBAT + "fruitbat3", "road")
            set_monster(1, "city")



class Fruitbat4(MudObject):
