# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/tray.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def setup(self, ) -> None:
            set_name( "tray" )
            set_short( "wooden tray" )
            set_long( "This is a small wooden tray, similar in style to the ones used by "
            "many vendors and travelling salespeople. Only a small quantity of items will "
            "fit on top of it.\n" )
            add_adjective(["small", "wooden"])
            set_material("wood")
            set_weight(5)
            set_max_weight(40)
            set_no_limbs(2)
            set_type("sash")
            set_cond(1000)
            set_max_cond(1000)
            add_wear_effect( "/std/effects/attached/single_shoulder" )


    def long(self, word: str, dark: int) -> str:
            return surface::long() + wearable::long()


    def init_static_arg(self, map: Any) -> None:
            if (!undefinedp( map["holdable"] ) )
            holdable::init_static_arg( map["holdable"] )
            if ( !undefinedp( map["surface"] ) && map["surface"] )
            surface::init_static_arg( map["surface"] )
            if ( !undefinedp( map["wearable"] ) && map["wearable"] )
            surface::init_static_arg( map["wearable"] )


    def dest_me(self, ) -> None:
            holdable::dest_me()
            surface::dest_me()


    def stats(self, ) -> Any:
            return surface::stats() + wearable::stats()



class Tray(MudObject):
