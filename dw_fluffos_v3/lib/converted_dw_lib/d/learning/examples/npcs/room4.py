# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/examples/npcs/room4.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light(70)
            set_short( "chatting NPC room" )
            add_property( "determinate", "the " )
            set_long( "The NPC in here gets to talk a little bit.  He has both random"
            " chats, and chats for use in combat which make him more entertaining.  "
            "Some chats appear more often than others.\n")
            add_exit("backwards", PATH +"room3", "door")
            add_exit("onwards", PATH +"room5", "door")


    def reset(self, ) -> None:
            if (!npc){
            npc = clone_object( PATH +"barley" )
            npc.move( self )



class Room4(Room):
