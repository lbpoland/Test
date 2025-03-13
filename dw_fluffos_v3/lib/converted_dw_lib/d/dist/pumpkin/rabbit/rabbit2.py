# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/rabbit/rabbit2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Rabbit Lane")
            set_long("This is the middle of Rabbit Lane where a bunch of "
            "books and things seem to be.\n")
            set_light( 80 )
            add_exit("east", RABBIT + "rabbit3", "road")
            add_exit("west", RABBIT + "rabbit1", "road")
            add_exit("north", RABBIT + "bookshop", "door")



class Rabbit2(MudObject):
