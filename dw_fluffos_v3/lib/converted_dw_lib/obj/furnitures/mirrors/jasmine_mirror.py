# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/mirrors/jasmine_mirror.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "mirror" )
            set_short( "jasmine mirror" )
            add_adjective( ["jasmine", "flower", "oval"] )
            set_long("Delicately carved jasmine flowers and bead trim surround this "
            "oval mirror.  The flowers are so detailed that they almost "
            "appear to be real.\n")
            set_allowed_room_verbs( (["hanging" : "hangs",
            "gracing"  : "graces"   ]) )
            set_weight(60)
            set_value(50000)



class Jasmine_mirror(MudObject):
