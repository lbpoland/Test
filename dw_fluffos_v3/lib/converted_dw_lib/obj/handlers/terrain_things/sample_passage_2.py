# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/terrain_things/sample_passage_2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "rock-walled tunnel" )
            set_light( 20 )
            set_room_size( 5 )
            set_long( "You are tunnel with rough-hewn rock walls.  It looks as though "+
            "it has been deserted for a long time.\n" )
            add_item( ["rough-hewn rock wall", "rock"], "The walls are rough, "+
            "where the tunnel was hewn out of the rock." )



class Sample_passage_2(Room):
