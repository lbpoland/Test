# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/fruitbat/fruitbat1.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Fruitbat Avenue")
            set_long("This is Fruitbat Avenue at the junction with Crumpet Circle.\n")
            set_light( 80 )
            add_exit("east", FRUITBAT + "fruitbat2", "road")
            add_exit("north", CRUMPT + "crumpt8", "road")
            set_monster(1, "city")



class Fruitbat1(MudObject):
