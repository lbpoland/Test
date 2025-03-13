# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/crumpt/crumpt7.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Crumpet Circle")
            set_long("This is the end of Crumpet Circle\n")
            set_light( 80 )
            add_exit("northeast", CRUMPT + "crumpt5", "road")
            add_exit("southwest", CRUMPT + "crumpt9", "road")
            add_exit("north", CRUMPT + "bank", "door")
            set_monster( 1, "city" )



class Crumpt7(MudObject):
