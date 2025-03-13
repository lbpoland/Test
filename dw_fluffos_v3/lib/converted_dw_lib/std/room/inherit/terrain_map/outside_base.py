# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/terrain_map/outside_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            terrain_room::init()
            outside::init()


    def stats(self, ) -> Any:
            return outside::stats() + terrain_room::stats()


    def dest_me(self, ) -> None:
            terrain_room::dest_me()
            outside::dest_me()



class Outside_base(MudObject):
