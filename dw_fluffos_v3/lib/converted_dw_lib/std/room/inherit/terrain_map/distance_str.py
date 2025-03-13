# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/terrain_map/distance_str.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_distance_str(self, dist: int) -> str:
            return query_distance_str_int(dist, 1)


    def query_distance_str_no_ones(self, dist: int) -> str:
            return query_distance_str_int(dist, 0)



class Distance_str(MudObject):
