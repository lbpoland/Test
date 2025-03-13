# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/clothing_transport.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def set_worn_by_race(self, race: str) -> None:
            _race = race


    def query_worn_by_race(self, ) -> str:
            return _race


    def set_mount_difficulty_modifier(self, diff: int) -> None:
            _mount_difficulty_modifier = diff


    def query_mount_difficulty_modifier(self, ) -> int:
            return _mount_difficulty_modifier


    def set_direction_difficulty_modifier(self, diff: int) -> None:
            _direction_difficulty_modifier = diff


    def query_direction_difficulty_modifier(self, ) -> int:
            return _direction_difficulty_modifier


    def init_static_arg(self, map: Any) -> None:
            if (map["::"]) {
            clothing::init_static_arg(map["::"])



class Clothing_transport(MudObject):
