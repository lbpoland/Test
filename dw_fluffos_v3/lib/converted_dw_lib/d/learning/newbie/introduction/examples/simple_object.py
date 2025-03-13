# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/newbie/introduction/examples/simple_object.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("dungarees")
            set_short("pair of waterproof dungarees")
            add_adjective(({"pair of", "waterproof"}))
            set_long("This is a pair of waterproof dungarees.  Luckily they "
            "are also ooze proof.\n")
            add_adjective(({"pair of", "waterproof"}))
            set_weight(45)
            set_value(4000)
            setup_clothing(50000)
            set_type("robe")



class Simple_object(MudObject):
