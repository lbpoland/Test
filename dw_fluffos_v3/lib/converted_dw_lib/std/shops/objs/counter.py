# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/objs/counter.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def clear_item(self, item: MudObject) -> None:
            if( environment( item ) == self
            && !sizeof( all_inventory( item ) ) )
            item.move( "/room/rubbish" )


    def event_enter(self, ob: MudObject, mess: str, from: MudObject) -> None:
            if( ob.query_property( "pub item" )
            && !sizeof( all_inventory( ob ) ) )
            asyncio.create_task(self. "clear_item", 3, ob )



class Counter(MudObject):
