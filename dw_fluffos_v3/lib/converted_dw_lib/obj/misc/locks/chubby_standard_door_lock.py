# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/locks/chubby_standard_door_lock.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("lock")
            set_short("chubby standard door lock")
            add_adjective( ["chubby", "standard", "door"])
            set_long("A chubby standard brass door lock.  These "
            "high-quality "
            "locks are made by Grabthroat Shinkicker and Sons.  "
            "Contrary to popular belief the locks are called "
            "chubby's not because of their thickness but because "
            "Grabthroat's real name is Charles and his "
            "nickname is Chubby.\n")
            add_property("difficulty", 6)
            set_weight(19)
            set_value(80000)


    def set_key_number(self, num: int) -> None:
            add_property("key prop", "door_lock_"+num)
            add_property("locktype", "door")



class Chubby_standard_door_lock(MudObject):
