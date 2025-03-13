# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/item_shop_outside.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            outside::init()
            item_shop::init()


    def dest_me(self, ) -> None:
            item_shop::dest_me()
            outside::dest_me()



class Item_shop_outside(MudObject):
