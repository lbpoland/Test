# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/safes/small_safe.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("safe")
            set_short("small iron safe")
            add_adjective(({"small", "iron"}))
            set_long("This is a small iron safe.  It bears the logo of "
            "Joseph Thighbiter a renowned safe maker.  It appears "
            "to feature one of his patented locks.\n")
            add_drawer("top", 50)
            add_drawer("middle", 25)
            add_drawer("bottom", 25)
            set_drawers_inside(1)
            set_weight(900)
            set_value(120000)
            set_allowed_room_verbs((["squatting" : "squats" ]))
            set_pick_skill("covert.lockpick.safes")
            set_difficulty(4)
            setup_trap(300, "pick",
            "Hidden inside the lock is a small ampule which, if touched by "
            "an unwary tool would trigger a puff of poisonous gas.",
            ({"A small cloud of gas puffs out of the safe.\n",
            "A small cloud of gas puffs out of the safe.\n"}),
            ({"/std/effects/poisons/poison_gas", 600}))


    def init(self, ) -> None:
            string key_id
            object key
            if(!query_key()) {
            key_id = "safe"+random(10000)
            set_key(key_id)
            key = clone_object("/std/key")
            key.set_key("small iron", key_id)
            key->set_long("This small, yet sturdy, key looks like it is for a "
            "safe.\n")
            key.move(self)
            set_closed()



class Small_safe(MudObject):
