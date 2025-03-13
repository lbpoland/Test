# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/terrain_things/sample_room_2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "largish room" )
            set_light( 20 )
            set_room_size( 25 )
            set_long( "You are in a largish room.  The walls, floor and ceiling are "+
            "comprised of large stone blocks.  The room is quite bare.\n" )
            add_item( ["wall", "floor", "ceiling"], "The walls, floor and "+
            "ceiling of the room are formed from large stone blocks." )
            add_item( "large stone block", "The blocks of stone that make up the "+
            "surfaces of this room are not too rough, but they were never "+
            "polished smooth either." )



class Sample_room_2(Room):
