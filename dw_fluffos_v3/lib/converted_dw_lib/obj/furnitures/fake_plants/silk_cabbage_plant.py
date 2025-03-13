# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/fake_plants/silk_cabbage_plant.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "plant" )
            add_adjective( ["silk", "potted", "cabbage"] )
            set_short( "potted silk cabbage plant" )
            add_alias( "cabbage" )
            set_main_plural ( "potted silk cabbage plants" )
            add_property( "determinate", "a " )
            set_long( "Rare and magnificent!  Strange and exotic!  Potted in a "
            "subtley plain pot, this fine silk-leafed brassica has been "
            "created in Sum Dim by none other than Brown Fingers Dibbler, "
            "purveyor of the finest silken forn plants.  Its leaves even look "
            "as though they have been nibbled slightly by a caterpillar, "
            "for the authentic touch.\n" )
            set_value( 35000 )
            set_weight( 150 )
            set_allowed_room_verbs(([ "sitting" : "sits",
            "standing" : "stands",
            "lying" : "lies" ]))



class Silk_cabbage_plant(MudObject):
