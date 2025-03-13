# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/cupboards/pine_kitchen_cupboards.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("cupboard")
            set_short("set of white pine kitchen cupboards")
            add_adjective( ["set", "of", "white", "pine", "kitchen"] )
            set_long("This is a set of kitchen cupboards made from white "
            "pine.  Four sets of doors hide the shelves within, and fluted "
            "columns with triple crowned tops make the structure a little "
            "less plain.  A simple design which still "
            "manages to radiate elegance, this set of cupboards is practial "
            "and functional, but still manages to be pleasing to the senses.\n")
            set_weight(250)
            set_max_weight(100)
            set_value(80000)
            set_allowed_room_verbs((["hanging" : "hangs" ]))



class Pine_kitchen_cupboards(MudObject):
