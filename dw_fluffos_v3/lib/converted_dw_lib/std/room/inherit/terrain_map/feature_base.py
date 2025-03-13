# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/terrain_map/feature_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_region(self, region: Any) -> None:
            if (_region) {
            _region.dest_me()


    def query_region_ob(self, ) -> MudObject:
            return _region


    def set_range_offset(self, offset: int) -> None:
            _range_offset = offset


    def query_range_offset(self, ) -> int:
            return _range_offset


    def set_max_day_range(self, range: int) -> None:
            _max_day_range = range
            if (_max_day_range > _max_range) {
            _max_range = _max_day_range


    def query_max_day_range(self, ) -> int:
            return _max_day_range


    def set_max_night_range(self, range: int) -> None:
            _max_night_range = range
            if (_max_night_range > _max_range) {
            _max_range = _max_night_range


    def query_max_night_range(self, ) -> int:
            return _max_night_range


    def set_min_range(self, range: int) -> None:
            _min_range = range


    def query_min_range(self, ) -> int:
            return _min_range


    def query_max_range(self, ) -> int:
            return _max_range


    def set_blocking(self, blocking: int) -> int:
            _blocking = blocking


    def query_blocking(self, ) -> int:
            return _blocking


    def calc_feature_desc(self, direc: Any, night: int, visibility: int) -> str:
            return "This needs to be set."


    def is_inside_region(self, x1: int, y1: int, x2: int, y2: int) -> int:
            return _region.is_inside_region(x1, y1, x2, y2, query_max_range())


    def dest_me(self, ) -> None:
            if (_region) {
            _region.dest_me()



class Feature_base(MudObject):
