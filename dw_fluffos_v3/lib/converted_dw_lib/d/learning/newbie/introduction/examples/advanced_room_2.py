# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/newbie/introduction/examples/advanced_room_2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("road to the market")
            add_property("determinate", "the ")
            set_day_long("This is a quiet road.  Absolutely nothing of interest is "
            "here..\n")
            set_night_long("This is a quiet road.  But at night!.\n")
            set_linker(({PATH + "advanced_room_1", PATH + "advanced_room_3"}),
            "onto", "on", "the newbie creator marketplace")
            set_light(80)
            add_zone("my rooms")
            add_item("road", "I *said*, there's nothing interesting at all here.")
            add_exit("north", PATH + "advanced_room_1", "road")



class Advanced_room_2(MudObject):
