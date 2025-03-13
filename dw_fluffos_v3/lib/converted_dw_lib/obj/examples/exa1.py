# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/examples/exa1.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            {
            set_short("first simple room")
            set_long("This is a simple room, have fun with it. To read the code " +
            "simply type 'more here'. For help with more, type 'h' in it.\n")
            set_light(90)
            add_exit("east", ROOM + "exa2", "door")
            set_zone("examples")



class Exa1(Room):
