# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/examples/exa2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            {
            set_short("second simple room")
            set_long("This is the second example room. It introduces items, and " +
            "aliasing - again use 'more here' to look at it. Over by the " +
            "north wall you can see a table.\n")
            set_light(90)
            add_item("table",
            "The table is one step away from being firewood. Upon it rests " +
            "a blotter.\n")
            add_item( ["north wall", "wall"],
            "It is very flat and is holding up rather a ricketty table.\n")
            add_item("blotter",
            "It is covered in random ink blots.\n")
            add_exit("west", ROOM + "exa1", "door")
            add_exit("east", ROOM + "exa3", "door")
            set_zone("examples")



class Exa2(Room):
