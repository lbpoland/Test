# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/dividor_room.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_main_room(self, room: str) -> None:
            _main_room = room


    def query_main_room(self, ) -> str:
            return _main_room


    def query_parcel_post(self, ) -> str:
            return _main_room.query_parcel_post()



class Dividor_room(MudObject):
