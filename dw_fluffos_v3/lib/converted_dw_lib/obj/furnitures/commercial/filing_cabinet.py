# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/commercial/filing_cabinet.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("filing cabinet")
            set_name("cabinet")
            add_alias("filing")
            set_long("A big grey wooden box with draws that slide in and out.  It "
            "looks like it could hold bunches of documents, nicely order "
            "and available for quick retrieval.")
            set_allowed_positions(({"sitting", "lying", "kneeling", "meditating"}))
            set_allowed_room_verbs((["sitting" : "sits" ]))
            set_weight(2000)
            set_value(240000)
            set_commercial_size(5)
            set_commercial_type("utility")



class Filing_cabinet(MudObject):
