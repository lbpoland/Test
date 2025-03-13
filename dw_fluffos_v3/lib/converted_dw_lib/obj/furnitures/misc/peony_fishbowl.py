# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/peony_fishbowl.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "fishbowl" )
            set_short( "gold-leafed peony fishbowl" )
            add_adjective( ["gold", "leafed", "leaf", "gold-leaf", "gold-leafed",
            "peony"] )
            add_plural( ["bowls", "fishbowls"] )
            add_alias("bowl")
            set_long( "Richly designed with blooming peonies, the flower that "
            "symbolizes peace and prosperity in Agatean culture, this grand "
            "16-inch fishbowl is carefully hand-layered with gold leaf over "
            "porcelain and hand-painted in exuberant colors.  This fishbowl "
            "matches any kind of foliage or simply stands alone as an art "
            "object.  Resting on a beautiful hand-polished rosewood base, "
            "the shapes of several goldfish can be seen swishing back and "
            "forth beneath the water it holds.\n" )
            set_weight( 110 )
            set_value( 51000 )
            set_allowed_positions(({"sitting"}))
            set_allowed_room_verbs((["sitting" : "sits",
            "standing" : "stands",
            "leaning" : "leans",
            "lying" : "lies",
            "squatting" : "squats" ]))



class Peony_fishbowl(MudObject):
