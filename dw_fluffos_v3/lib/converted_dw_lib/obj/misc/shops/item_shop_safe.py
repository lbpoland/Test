# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/shops/item_shop_safe.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "safe" )
            set_short( "cash safe" )
            set_long( "This safe is used to keep the shop's float in.  It's securely set "
            "in the wall.\n" )
            add_adjective( "float" )
            add_property( "there", "in the wall" )
            set_difficulty( 10 )
            reset_get()
            set_closed()
            set_locked()
            set_key( "non-existent key" )
            add_property( "no recycling", 1 )
            set_pick_skill( "covert.lockpick.safes" )
            set_weight( 2000 )
            set_max_weight( 5000 )
            set_value( 120000 )


    def pick_unlock(self, player: MudObject) -> int:
            self.set_unlocked()
            return 1


    def query_accept_money(self, ) -> int:
            return 1



class Item_shop_safe(MudObject):
