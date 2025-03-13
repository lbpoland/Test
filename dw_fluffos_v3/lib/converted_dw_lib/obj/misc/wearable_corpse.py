# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/wearable_corpse.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def long(self, word: str, dark: int) -> str:
            return corpse::long( word, dark ) + wearable::long( word, dark )


    def init_static_arg(self, map: Any) -> None:
            if ( map[ "corpse" ] )
            corpse::init_static_arg( map[ "corpse" ] )
            if ( map[ "wearable" ] )
            corpse::init_static_arg( map[ "wearable" ] )


    def init_dynamic_arg(self, map: Any) -> None:
            if ( !undefinedp( map[ "corpse" ] ) )
            corpse::init_dynamic_arg( map[ "corpse" ] )
            if ( !undefinedp( map[ "wearable" ] ) )
            wearable::init_dynamic_arg( map[ "wearable" ] )



class Wearable_corpse(MudObject):
