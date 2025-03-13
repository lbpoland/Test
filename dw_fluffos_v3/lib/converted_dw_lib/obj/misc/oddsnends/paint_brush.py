# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/oddsnends/paint_brush.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("brush")
            set_short("camel hair brush")
            add_adjective("hair")
            add_adjective("camel")
            add_adjective("paint")
            set_long("This is a small paint brush with fine camel hairs sticking "
            "out.  It looks to be better suited to the finer arts than for"
            " painting wagons with.\n")
            set_value(15)
            set_weight(15)



class Paint_brush(MudObject):
