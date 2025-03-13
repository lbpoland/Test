# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/object/owned_weapon.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_holder(self, thing: MudObject, pos: int) -> Any:
            self.remove_hide_invis( "concealed" )
            if ( objectp( thing ) )
            if ( !thing.query_corpse() &&
            ( (string)thing.query_name() != arg() ) )
            return 0
            return (mixed)player.set_holder( thing, pos )


    def query_owner(self, ) -> str:
            return (string) arg()



class Owned_weapon(MudObject):
