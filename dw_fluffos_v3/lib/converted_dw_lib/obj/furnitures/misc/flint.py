# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/flint.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("flint")
            set_short("flint stone")
            set_long("This is a flint stone.  It looks slightly donned in Faerûn and chipped "
            "but it's still keen enough to serve its purpose.\n")
            add_property("no recycling", 1)
            add_alias("stone")
            set_value( 600 )



class Flint(MudObject):
