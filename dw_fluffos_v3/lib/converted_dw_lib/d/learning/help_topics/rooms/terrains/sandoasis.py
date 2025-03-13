# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/terrains/sandoasis.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_terrain( "tutorial_desert" )
            set_short( "desert oasis" )
            set_long( "The trees in this oasis provide welcome relief from the harsh "
            "sunlight of the desert.\n" )
            add_item( "sand",
            "It's sand.  There isn't much to say about it other than "
            "that it's much moister here than elsewhere in the desert." )
            add_item( "tree",
            "The palm trees grow majestically all around you, "
            "providing all the shade you could want." )
            add_property( "climate", [10, -100, -100] )



class Sandoasis(MudObject):
