# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/pub_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            basic_room::init()
            pub::init()


    def dest_me(self, ) -> None:
            pub::dest_me()
            basic_room::dest_me()



class Pub_shop(MudObject):
