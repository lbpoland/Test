# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/fungi/blue_nightcap.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_adjs( "blue capped" )
            set_type( "mushroom" )
            set_extra( "The shape of it reminds you of someone wearing a nightcap." )


    def next_stage(self, ) -> None:
            if ( stage == 8 )
            add_eat_effect( "/std/effects/ingested/tranquil_sleep", 60 +
            random( 60 ) )
            ::next_stage()



class Blue_nightcap(MudObject):
