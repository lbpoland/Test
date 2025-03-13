# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/terrain_map/factory_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._adjacent_items = ([ ])


    def set_room_jump_size(self, jump: int) -> None:
            _room_jump_size = jump


    def query_room_jump_size(self, ) -> int:
            return _room_jump_size


    def set_follow_road(self, follow: int) -> None:
            _follow_road = follow


    def query_follow_road(self, ) -> int:
            return _follow_road


    def set_default_height(self, height: int) -> None:
            _default_height = height


    def set_adjacent_description(self, desc: str) -> None:
            _adjacent_desc = desc


    def query_adjacent_description(self, ) -> str:
            return _adjacent_desc


    def query_default_height(self, ) -> int:
            return _default_height


    def set_minimum_height(self, height: int) -> None:
            _min_height = height


    def query_minimum_height(self, ) -> int:
            return _min_height


    def set_height_rooms(self, map: Any) -> None:
            _height_info = map


    def find_base_terrain_room(self, x: int, y: int, z: int, base_name: str, map_room: int, ref: str) -> str:
            if (_height_info && _height_info[z]) {
            return _height_info[z]


    def add_adjacent_item(self, name: str, desc: str) -> None:
            _adjacent_items[name] = desc


    def stats(self, ) -> Any:
            return ({
            ["room jump", _room_jump_size],
            ["follow road", _follow_road],
            ["adjacent desc", _adjacent_desc]]



class Factory_base(MudObject):

    _adjacent_items = '([ ])'
