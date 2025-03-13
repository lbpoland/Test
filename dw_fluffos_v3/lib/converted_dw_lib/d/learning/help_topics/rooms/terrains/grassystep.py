# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/terrains/grassystep.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_terrain( "tutorial_grassy_field" )
            set_short( "doorstep")
            set_long( "This is the doorstep to a small cottage.  All around "
            "here is a field covered with nicely cut grass.\n" )
            add_item( "grass", "It's grass.  There isn't much to say about it." )
            add_item( "cottage", "A plain, one-room cottage, painted white, "
            "with pink shutters on both the windows.  *hack* *cough*" )
            add_exit( "cottage", PATH "foyer", "corridor" )



class Grassystep(MudObject):
