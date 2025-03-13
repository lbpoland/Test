# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/shelves/pine_nightstand.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "nightstand" )
            set_short( "pine nightstand" )
            add_adjective( ["pine", "bedside"] )
            add_alias("cabinet")
            set_long( "This is a small bedside cabinet, made of thick hublandish "
            "pine planks.  The wood is oiled, to bring out the characteristic "
            "colour, and the stripes and knots texture in it.  It's just the "
            "kind of thing that is thought to have a rustic look, by "
            "people who don't have much of a clue what rustic is.\n" )
            add_drawer( "top", 50 )
            set_weight(135)
            set_value(10000)
            set_allowed_positions(({"sitting"}))
            set_allowed_room_verbs((["sitting" : "sits" ]))


    def init(self, ) -> None:
            string key_id
            object key
            if(!query_key()) {
            key_id = "nightstand_"+random(100)
            set_key(key_id)
            set_difficulty(1)
            key = clone_object("/std/key")
            key.set_key("small", key_id)
            key->set_long("This small key looks like it is probably for a piece of "
            "furniture.\n")
            key.move(self)
            set_closed()



class Pine_nightstand(MudObject):
