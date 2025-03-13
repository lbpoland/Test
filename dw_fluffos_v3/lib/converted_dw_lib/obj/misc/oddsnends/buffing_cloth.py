# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/oddsnends/buffing_cloth.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("cloth")
            set_short("buffing cloth")
            set_main_plural("buffing cloths")
            add_adjective( "buffing" )
            set_long("This is a small, soft cloth that might be used for polishing"
            " metal objects.\n" )
            set_value(32)
            set_weight(2)



class Buffing_cloth(MudObject):
