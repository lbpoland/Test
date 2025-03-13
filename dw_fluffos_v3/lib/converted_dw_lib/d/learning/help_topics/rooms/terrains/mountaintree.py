# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/terrains/mountaintree.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_room_size( 20 )
            set_terrain( "tutorial_mountain" )
            set_short( "tree in the mountains" )
            set_long( "This tree has defied all the odds, and grows straight and "
            "tall in the blustery wastes." )
            add_extra_look( self )
            add_property( "climate", [-40, 50, 40] )


    def extra_look(self, ) -> str:
            if ( co_ord[ 2 ] < 800200 )
            return "\n"
            else
            return "  You can just make out a cabin in the snows to your "
            "northeast.\n"



class Mountaintree(MudObject):
