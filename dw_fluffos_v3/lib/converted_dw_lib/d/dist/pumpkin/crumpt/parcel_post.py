# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/crumpt/parcel_post.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Parcel Post")
            set_long(
            "Livid orange strips criss cross the room contrasting just beautifully "
            "against the black background.  The walls almost seem to be pulsing with "
            "colour.\n")
            set_light(70)
            add_exit("south", CRUMPT + "post_office", "south")
            add_property("place", "Pumpkin")



class Parcel_post(MudObject):
