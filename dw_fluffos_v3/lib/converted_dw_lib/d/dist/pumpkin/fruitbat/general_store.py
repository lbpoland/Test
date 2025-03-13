# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/fruitbat/general_store.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Elephant's Stamp")
            set_long(
            "A huge picture of an elephant covers tha back room of the shop.  You can "
            "see the elephant guarding a huge pile of goods.\n")
            add_exit("north", FRUITBAT + "fruitbat2", "door")
            set_light(70)
            set_store_room(FRUITBAT + "storeroom")
            add_property("place", "Pumpkin")



class General_store(MudObject):
