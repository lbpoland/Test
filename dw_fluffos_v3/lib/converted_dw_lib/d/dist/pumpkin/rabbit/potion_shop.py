# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/rabbit/potion_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Carrot's Potion Store")
            set_long(
            "This is a bright orange room with a green ceiling.\n")
            set_light(70)
            add_exit("south", RABBIT + "rabbit4", "door")
            set_save_dir(SAVE + "potions")
            set_cut(10)
            add_property("place", "Pumpkin")



class Potion_shop(MudObject):
