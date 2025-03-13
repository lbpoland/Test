# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/water_outside.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init(self, ) -> None:
            water::init()
            outside::init()


    def is_allowed_position(self, poss: str) -> int:
            return water::is_allowed_position(poss)


    def add_exit(self, direc: str, dest: Any, type: str) -> int:
            int retval = outside::add_exit(direc, dest, type)
            water::add_exit(direc, dest, type)
            return retval


    def query_light(self, ) -> int:
            update_water_light()
            if (query_surface()) {
            return ::query_light()


    def set_water_light(self, number: int) -> int:
            _setting_water_light = 1
            set_light(number)
            _setting_water_light = 0


    def adjust_light(self, number: int) -> int:
            if (!_setting_water_light) {
            set_use_surface_light(0)


    def query_property(self, tag: str) -> Any:
            if ("location" == tag && !query_surface()) {
            return "underwater"



class Water_outside(MudObject):
