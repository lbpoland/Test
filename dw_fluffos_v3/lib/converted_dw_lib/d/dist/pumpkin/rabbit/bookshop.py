# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/rabbit/bookshop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Bugs Bookstore")
            set_long(
            "The distinctly carroty atmosphere of the store makes you feel like "
            "saying 'Whats up doc?'\n")
            add_exit("south", RABBIT + "rabbit2", "door")
            set_light(70)
            set_cut(10)
            set_when_sold_function( (: $1.set_open_page(0) :) )
            set_allowed_to_sell( (: $1.query_book() || $1.query_paper() :) )
            set_minimum_cost(400)
            set_save_dir(SAVE + "bookshop")
            add_property("place", "Pumpkin")



class Bookshop(MudObject):
