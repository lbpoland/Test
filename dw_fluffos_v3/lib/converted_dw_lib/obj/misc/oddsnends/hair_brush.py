# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/oddsnends/hair_brush.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("brush")
            set_short("stiff hair brush")
            add_adjective("hair")
            add_adjective("stiff")
            set_long("This is a small brush with rather stiff tines "
            "sticking out from it.  It looks like just the thing to "
            "straighten out your hair after a sandstorm.\n")
            set_value(10)
            set_weight(20)



class Hair_brush(MudObject):
