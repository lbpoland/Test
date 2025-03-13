# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/locks/standard_furniture_lock.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("lock")
            set_short("standard furniture lock")
            add_adjective( ["standard", "furniture"])
            set_long("A standard brass furniture lock.\n")
            add_property("difficulty", 2)
            set_weight(19)
            set_value(10000)


    def set_key_number(self, num: int) -> None:
            add_property("key prop", "furniture_lock_"+num)
            add_property("locktype", "furniture")



class Standard_furniture_lock(MudObject):
