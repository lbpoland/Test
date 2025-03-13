# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/examples/npcs/room1.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light(70)
            set_short( "cloned NPC room" )
            add_property( "determinate", "the " )
            set_long( "This room holds a very simple NPC.  He is a fighter.  His "
            "code is within the room code.  If he's not here, type update, and"
            ", like magic, he should appear.  If he doesn't, panic.\n")
            add_exit("onwards", PATH +"room2", "door")


    def reset(self, ) -> None:
            if (!npc){
            npc = clone_object( "/obj/monster" )
            npc -> set_name("pugh")
            npc -> set_short("Pugh")
            npc -> add_property("determinate", "")
            npc -> add_alias( ({"npc", "warrior", "man"}) )
            npc -> set_long("This is Pugh.  He was cloned here, and "
            "this is his world.  Welcome to it.\n")
            npc -> basic_setup("human", "warrior", 10)
            npc -> set_gender( 1 )
            npc.move( self )



class Room1(Room):
