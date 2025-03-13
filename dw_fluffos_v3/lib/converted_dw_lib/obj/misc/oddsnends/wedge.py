# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/oddsnends/wedge.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("wedge")
            set_short("door wedge")
            add_adjective("door")
            set_main_plural("door wedges")
            set_long("A common wooden door wedge.  "
            "You use them to hold a door open.\n")
            set_value(10)
            set_weight(10)



class Wedge(MudObject):
