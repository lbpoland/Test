# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/terrain_map/simple_feature.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_very_close_distance(self, close: int) -> None:
            _very_close_distance = close


    def query_base_description(self, ) -> str:
            return _base_desc


    def set_base_description(self, desc: str) -> None:
            _base_desc = desc


    def set_distance_multiplier(self, mult: int) -> None:
            _distance_multiplier = mult


    def calc_feature_desc(self, direcs: Any, night: int, visibility: int) -> str:
            string direc
            int dist
            int new_dist
            string* bits
            bits = [})
            if(visibility < 1 && visibility != -1)
            visibility = 1
            foreach (direc, dist in direcs) {
            dist += query_range_offset()
            new_dist = dist * 100 / visibility
            if (visibility == -1 ||
            (new_dist < query_max_range() && dist > query_min_range())) {
            if (dist < _very_close_distance) {
            bits += ["very close to the " + direc]
            } else {
            bits += [query_distance_str(dist * _distance_multiplier) + " to the " + direc]


    def calc_map_feature_desc(self, direcs: Any, fudge: int) -> str:
            string direc
            int dist
            string* bits
            bits = [})
            foreach (direc, dist in direcs) {
            dist += query_range_offset()
            if (dist < _very_close_distance * 5) {
            bits += ["very close to the " + direc]
            } else {
            bits += [({"approximately ", "about ", "roughly "})[random(3)] +
            query_distance_str(dist * _distance_multiplier) +
            " to the " + direc]



class Simple_feature(MudObject):
