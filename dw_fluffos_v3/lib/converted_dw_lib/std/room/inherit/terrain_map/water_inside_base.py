# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/terrain_map/water_inside_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            terrain_room::init()
            water_inside::init()


    def stats(self, ) -> Any:
            return water_inside::stats() + terrain_room::stats()


    def query_terrain_map_walk_exit(self, ) -> str:
            return "swim "


    def query_surface_room(self, ) -> MudObject:
            string dest_path
            object destination
            if (query_surface()) {
            return self


    def get_water_surface_light(self, ) -> int:
            float their_light, their_clarity, our_depth
            string above_path = file_name(self)
            object above
            above_path = implode(explode(above_path, ":")[0..<2], ":")+":0"
            above = load_object(above_path)
            if (!above) {
            return 0



class Water_inside_base(MudObject):
