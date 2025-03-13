# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/terrain_map/region_poly.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_inside(self, flag: int) -> None:
            _inside = flag


    def add_vertex(self, x: int, y: int) -> None:
            class vertex vertex
            vertex = new(class vertex, x : x, y : y)
            _vertexes += [vertex]


    def is_inside_region(self, x1: int, y1: int, x2: int, y2: int, range: int) -> int:
            class vertex vertex
            class vertex vert1
            class vertex vert2
            int i
            foreach (vertex in _vertexes) {
            if (vertex->x >= x1 && vertex->x <= x2 &&
            vertex->y >= y1 && vertex->y <= y2) {
            return 1


    def dest_me(self, ) -> None:
            destruct(self)



class Region_poly(MudObject):
