# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/fungi/magic_mushroom.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_adjs( "checkered" )
            set_type( "mushroom" )
            set_extra( "The checks are nice pastel shades of peach and mauve." )
            set_messages( ({
            "A small $type$ pushes up through the soil.\n",
            "The $type$ seems to be a bit larger now.\n",
            "The $type$ looks nice and large now.\n",
            "The $type$ jumps up and down very quickly, and then burps.\n",
            "You hear a small voice say: Goodbye, cruel world!\nThe $type$ "+
            "falls over and disintegrates.\n"
            }) )


    def next_stage(self, ) -> None:
            if ( stage == 8 )
            add_eat_effect( "/std/effects/ingested/hallucination", 150 +
            random( 150 ) )
            ::next_stage()



class Magic_mushroom(MudObject):
