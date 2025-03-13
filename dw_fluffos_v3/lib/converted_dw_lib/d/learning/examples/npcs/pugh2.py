# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/examples/npcs/pugh2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "pugh" )
            set_short( "Pugh" )
            add_property("determinate", "")
            add_alias( ({"npc", "warrior", "man"}) )
            set_long("This is Pugh.  He exists in a separate file, so can easily be "
            "loaded in a variety of locations at once.  Essentially, he is identical"
            " to Pugh in the other room.\n")
            basic_setup ("human", "warrior", 10)
            set_gender( 1 )



class Pugh2(MudObject):
