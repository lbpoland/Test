# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/pumpkin/pumpkin2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Pumpkin Way")
            set_long("This is middle of Pumpkin Way just north of Crumpt Circle.\n")
            set_light( 80 )
            add_exit("west", PUMPKIN + "pumpkin1", "road")
            add_exit("south", PUMPKIN + "pumpkin3", "road")
            set_monster(2, "pumpkin")



class Pumpkin2(MudObject):
