# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/log.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("log")
            set_shorts( ["small log",
            "slightly burnt log",
            "blackened log",
            "black, charred log"] )
            set_longs( ({
            "This is a small dumpy log.  It looks as though it would burn well.\n",
            "This is a small dumpy log.  It has been charred around the edges "
            "but would still burn for a while yet.\n",
            "This is a black lump of charred wood, which is just about holding "
            "its shape together as a log.\n"] )
            set_weight( WEIGHT )
            set_value( 400 )



class Log(MudObject):
