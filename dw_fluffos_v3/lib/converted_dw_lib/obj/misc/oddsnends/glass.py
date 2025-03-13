# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/oddsnends/glass.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("glass")
            set_short("glass")
            set_long("This is a limited edition authentic "
            "scumble measure glass, as produced by the "
            "ancient scumble brewers.  It is very exclusive.\n")
            set_max_volume(VOLUME_HALFPINT)
            set_max_weight(10)
            set_leak_rate(0)
            set_value(30)
            set_weight(5)
            set_stuck(1)



class Glass(MudObject):
