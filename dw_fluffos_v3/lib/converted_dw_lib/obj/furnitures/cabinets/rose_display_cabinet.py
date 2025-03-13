# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/cabinets/rose_display_cabinet.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("cabinet")
            set_short("rosewood display cabinet")
            add_adjective( ["rosewood", "display"] )
            set_long("This is a tall rosewood display cabinet that has a glass "
            "front to ensure that its contents are well protected.  Supported "
            "by various delicate geometric shelves on the inside, the outside "
            "is inlaid with mother of pearl that has been shaped into "
            "blossoming cherry trees.\n")
            set_transparent()
            set_weight(1200)
            set_max_weight(200)
            set_value(590000)
            set_allowed_room_verbs((["squatting" : "squats" ]))



class Rose_display_cabinet(MudObject):
