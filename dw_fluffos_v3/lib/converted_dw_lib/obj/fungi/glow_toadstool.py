# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/fungi/glow_toadstool.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_adjs( "yellow spotted" )
            set_type( "toadstool" )
            set_extra( 0 )


    def next_stage(self, ) -> None:
            if ( stage == 8 ) {
            tell_room( environment(), "The yellow spots on the toadstool begin to "+
            "glow.\n" )
            set_light( 5 )
            set_long( query_long() +"The yellow spots are glowing.\n" )



class Glow_toadstool(MudObject):
