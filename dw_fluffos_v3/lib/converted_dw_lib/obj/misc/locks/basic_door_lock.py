# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/locks/basic_door_lock.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("lock")
            set_short("basic door lock")
            add_adjective( ["basic", "door"])
            set_long("A basic brass door lock.\n")
            add_property("difficulty", 2)
            set_weight(19)
            set_value(20000)


    def set_key_number(self, num: int) -> None:
            add_property("key prop", "door_lock_"+num)
            add_property("locktype", "door")



class Basic_door_lock(MudObject):
