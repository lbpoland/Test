# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/terrain_map/region_rect.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def add_feature_position(self, x: int, y: int, width: int, height: int) -> None:
            class feature_pos pos
            pos = new(class feature_pos, xstart : x, ystart : y,
            width : width, height : height)
            _positions += [pos]


    def dest_me(self, ) -> None:
            destruct(self)


    def is_inside_region(self, x1: int, y1: int, x2: int, y2: int, range: int) -> int:
            class feature_pos position
            int height
            int width
            foreach (position in _positions) {
            height = position->height
            width = position->width
            if (position->xstart >= x1 && position->xstart <= x2 &&
            position->ystart >= y1 && position->ystart <= y2) {
            return 1



class Region_rect(MudObject):
