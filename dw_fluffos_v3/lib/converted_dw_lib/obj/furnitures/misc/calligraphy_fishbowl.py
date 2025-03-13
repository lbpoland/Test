# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/calligraphy_fishbowl.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "fishbowl" )
            set_short( "calligraphised fishbowl" )
            add_adjective( ["calligraphised", "fish"] )
            add_alias("bowl")
            add_plural( ["bowls", "fishbowls"] )
            set_long("Calligraphy is the soul of Agatean culture.  On this 16-inch "
            "fishbowl a Zing Dynasty poem is strikingly carved in "
            "and then gold leafed against an equally striking black background.  "
            "The black lacquer is hand-painted over porcelain to create a matte "
            "effect.  A matching solid wood stand holds the bowl's weight, "
            "and several goldfish swim quietly beneath the water it holds.\n" )
            set_weight( 110 )
            set_value( 48000 )
            set_allowed_positions(({"sitting"}))
            set_allowed_room_verbs(([ "sitting" : "sits",
            "standing" : "stands",
            "leaning" : "leans",
            "lying" : "lies",
            "squatting" : "squats" ]))



class Calligraphy_fishbowl(MudObject):
