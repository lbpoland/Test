# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/crumpt/bank.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Pumpkin's Bank")
            set_long(
            "The room is full of pumpkins with little dollar signs carved in the side.  "
            "There is a wooden counter running across the room with some telers peering "
            "through the wooden grill into the main room.\n")
            add_item("counter", ["long", "It is wooden and has a grill on top to "
            "seperate the tellers from the unwashed masses.",
            "position", "the counter"])
            add_item("teller", "They peer out at through the grill wondering who has "
            "come to give them money.\n")
            add_item("pumpkin", "There are little pumpkins everywhere in the room.")
            set_light(70)
            set_percentage(95)
            set_place("Pumpkin")
            add_exit("south", CRUMPT + "crumpt7", "door")
            add_property("place", "Pumpkin")



class Bank(MudObject):
