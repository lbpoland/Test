# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/crockery/happiness_jar.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "happiness" )
            set_short( "jar of double happiness" )
            add_adjective( ["jar", "of", "double"] )
            set_long("In Agatea, this elegant blue and white porcelain jar is "
            "often presented as a wedding gift.  The pictogram for happiness "
            "is drawn twice in parallel to make the Double Happiness sign, "
            "which is used in wedding decorations.  With a tight lid, this "
            "porcelain jar is excellent for storing anything you wish.\n")
            set_weight( 140 )
            set_max_weight(27)
            set_value( 25000 )
            set_allowed_room_verbs(([ "sitting" : "sits",
            "standing" : "stands",
            "leaning" : "leans",
            "lying" : "lies",
            "squatting" : "squats" ]))



class Happiness_jar(MudObject):
