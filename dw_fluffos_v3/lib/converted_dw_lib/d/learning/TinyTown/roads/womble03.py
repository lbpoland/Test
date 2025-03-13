# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/TinyTown/roads/womble03.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            add_property( "determinate", "the " )
            set_short( "northwestern corner of Womble square" )
            set_long("This is the western edge of Tiny Town, a small "
            "town built as an example for new creators who might want to see "
            "how to make rooms, npc's and such without the complexity of "
            "the \"real\" domains.\n")
            set_zone( "Tiny Town")
            set_linker([PATH +"womble01", PATH +"womble03", PATH +"womble04",],
            "into", "", "Womble Square" )
            add_exit( "south", PATH +"womble01", "road" )
            add_exit( "southeast", PATH +"womble02", "hidden" )
            add_exit( "east", PATH +"womble04", "road" )



class Womble03(MudObject):
