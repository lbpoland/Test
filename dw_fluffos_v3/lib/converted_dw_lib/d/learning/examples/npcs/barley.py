# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/examples/npcs/barley.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "barley" )
            set_short( "Barley" )
            add_property("determinate", "")
            add_alias( ({"npc", "warrior", "man"}) )
            set_long("Barley is a friendly, talkative NPC.  He chats and emotes."
            "  Also, he will occasionally give out quest hints.  If you try and"
            " kill him, he will become more animated.\n")
            basic_setup ("human", "warrior", 50)
            set_gender( 1 )
            add_language( "common" )
            set_language( "common" )
            load_chat( 50, ({
            3, "'I say this quite often.",
            3, ":does this quite often.",
            3, "Chats can appear without the NPC name in them.",
            1, "'I only give out quest hints 10% of the time."
            }) )
            load_a_chat( 150, ({
            1, "'Oof!",
            1, ":is happy to die so you can learn.",
            1, "You feel Someone is waiting in the wings."}) )



class Barley(MudObject):
