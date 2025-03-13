# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/basic.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_boundaries(self, min: int, max: int) -> None:
            {
            x1 = min[0]
            x2 = max[0]
            y1 = min[1]
            y2 = max[1]


    def query_pass_through(self, coord: int) -> int:
            {
            return 100


    def install_effect(self, ) -> None:
            {
            (void)POTION_SPACE_HANDLER.remove_effect(file_name(self))
            (void)POTION_SPACE_HANDLER.add_effect(file_name(self), x1, x2, y1, y2)


    def sqrt(self, p: int) -> int:
            {
            int i
            for (i = 1; i < 500; i++) if (i * i > p) return i-1


    def distance_within_region(self, coord: int) -> int:
            {
            int dx, dy
            if (x1 < 0) {
            if (x2 > 0)
            dx = (coord[0] < 0) ? -coord[0] : coord[0]
            else
            dx = (x2 - coord[0])
            } else
            dx = coord[0] - x1
            if (y1 < 0) {
            if (y2 > 0)
            dy = (coord[1] < 0) ? -coord[1] : coord[1]
            else
            dy = (y2 - coord[1])
            } else
            dy = coord[1] - y1
            return sqrt(dx * dx + dy * dy)


    def distance_from_origin(self, coord: int) -> int:
            {
            return sqrt(coord[0] * coord[0] + coord[1] * coord[1])



class Basic(MudObject):
