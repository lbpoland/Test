# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/chests/pine_chest_of_drawers.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("chest")
            set_short("Agatean pine chest of drawers")
            add_adjective(({"agatean", "pine", "chest", "of", "drawers"}))
            add_alias("chest of drawers")
            set_long("A simple chest of drawers formed of genuine Agatean pine, "
            "sturdy and functional.  The grain of the wood is a little "
            "mismatched testifying to the desire of the manufacturer to "
            "create something functional rather than beautiful.  Five drawers "
            "are set into the front each bearing two knobs of the same "
            "material. Very slight ornamentation has been added in the form "
            "of gentle curves deliniating the edges and unornamented top.\n")
            set_weight(900)
            set_max_weight(400)
            set_value(200000)
            set_allowed_room_verbs((["squatting" : "squats" ]))
            set_pick_skill("covert.lockpick.doors")
            set_difficulty(4)


    def init(self, ) -> None:
            string key_id
            object key
            if(!query_key()) {
            key_id = "furniture_lock_"+random(1000)
            set_key(key_id)
            key = clone_object("/std/key")
            key.set_key("small iron", key_id)
            key->set_long("This small, yet sturdy, key looks like it is for a "
            "piece of furniture.\n")
            key.move(self)
            set_closed()



class Pine_chest_of_drawers(MudObject):
