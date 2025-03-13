# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/traps/fast_acting_needle_trap.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("trap")
            set_weight(1)
            set_short("fast-acting needle trap")
            add_adjective(["fast-acting", "fast", "acting", "needle"])
            set_long("This is a needle trap suitable for rigging inside "
            "the lock of a door. It uses a small needle that "
            "will inject a fast acting poison into anyone "
            "clumsily picking "
            "the lock.\n")
            make_trap(250, "pick",
            "Hidden inside the lock is a small mechanism "
            "which, if touched by an clumsily wielded tool "
            "will cause a small needle to swing out and poison "
            "an unwary thief.\n",
            ({"A small needle swings out of the lock injecting "
            "poison.\n",
            "A small needle sings out of the lock.\n"],
            500)
            set_value(80000)



class Fast_acting_needle_trap(MudObject):
