# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/examples/npcs/macgrew.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "macgrew" )
            set_short( "MacGrew" )
            add_property("determinate", "")
            add_alias( ({"npc", "warrior", "man"}) )
            set_long("MacGrew is a warm, armed NPC.  He models some of the latest "
            "fashions, but beware of mentioning them in the long() because he may "
            "have them stolen, or broken.  Let players look at him.\n")
            basic_setup ("human", "warrior", 50)
            set_gender( 1 )
            add_language( "common" )
            set_language( "common" )
            load_chat( 50, ({
            1, ":checks his equipment.",
            1, ":feels all snuggly and warm in his new clothes."
            }) )
            load_a_chat( 150, ({
            1, "'Oof!",
            1, ":is happy to die so you can learn.",
            1, "You feel Someone is waiting in the wings."}) )
            ARMOURY->request_item( "short sword",
            70+random(30))->move(self)
            ARMOURY->request_item( "baggy leather loincloth",
            70+random(30))->move(self)
            ARMOURY->request_item( "metal helmet",
            70+random(30))->move(self)
            init_equip()
            give_money( 10, 30, "Waterdeep pence" )



class Macgrew(MudObject):
