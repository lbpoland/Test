# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/crumpt/crumpt8.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Crumpet Circle")
            set_long("This is Crumpet Circle at the junction with Fruitbat Avenue.
            \n")
            set_light( 80 )
            add_exit("east", CRUMPT + "crumpt9", "road")
            add_exit("north", CRUMPT + "crumpt6", "road")
            add_exit("south", FRUITBAT + "fruitbat1", "road")
            set_monster( 1, "city" )



class Crumpt8(MudObject):
