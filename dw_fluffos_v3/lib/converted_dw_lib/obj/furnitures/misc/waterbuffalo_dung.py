# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/waterbuffalo_dung.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("dung")
            set_shorts( ["small lump of dried waterbuffalo dung",
            "slightly burnt lump of waterbuffalo dung",
            "blackened lump of waterbuffalo dung",
            "black, charred lump of dung"] )
            set_longs( ({
            "This is a small lump of dried waterbuffalo dung.  It looks as "
            "though it would burn well.\n",
            "This is a small lump of dried waterbuffalo dung.  It has been "
            "charred around the edges but would still burn for a while yet.\n",
            "This is a black lump of charred dung, which is barely able to still "
            "hold itself together.\n"] )
            set_weight( 9 )
            set_value( 200 )



class Waterbuffalo_dung(MudObject):
