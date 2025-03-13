# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/examples/npcs/room2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light(70)
            set_short( "seperate file NPC room" )
            add_property( "determinate", "the " )
            set_long( "The NPC in here is cloned from another file, and brought here."
            "  This method means the same NPC can easily be loaded into a variety "
            "of locations, without the need to repeat much code.  The npc file is "
            "in /d/learning/examples/npcs/pugh2.c.\n")
            add_exit("backwards", PATH +"room1", "door")
            add_exit("onwards", PATH +"room3", "door")


    def reset(self, ) -> None:
            if (!npc){
            npc = clone_object( PATH +"pugh2" )
            npc.move( self )



class Room2(Room):
