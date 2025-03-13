# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/TinyTown/buildings/shop-upstairs.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "bedroom" )
            set_long( "This is a small bedroom above the shop.  There is a window "
            "in the north wall.\n")
            set_light( 60 )
            set_room_size( 10 )
            set_zone( "Tiny Town")
            add_exit("window", PATH+"shop-ledge", "window")
            add_exit("down", PATH +"item-shop", "stair" )
            modify_exit("down", ["downgrade", 9])



class Shop-upstairs(MudObject):
