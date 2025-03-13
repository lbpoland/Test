# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/locks/brass_door_key.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_key_number(self, num: int) -> None:
            set_key("small brass", "door_lock_" + num)
            set_long("A small brass key.  It has a serial number " +
            num + " engraved on it.\n")
            set_value(10)


    def query_duplicatable_key(self, ) -> int:
            return 1



class Brass_door_key(MudObject):
