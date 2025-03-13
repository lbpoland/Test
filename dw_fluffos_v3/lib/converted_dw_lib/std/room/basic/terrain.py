# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/basic/terrain.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup_shadow(self, thing: MudObject, word: str) -> None:
            shadow(thing, 1)
            TERRAIN_MAP.setup_location(thing, word)
            thing.add_property("terrain name", word)
            terrain_name = word
            room = thing


    def destruct_shadow(self, thing: MudObject) -> None:
            if (thing == self) {
            TERRAIN_MAP.delete_cloned_location(terrain_name, file_name(room))
            destruct(self)
            } else {
            thing.destruct_shadow( thing )


    def event_exit(self, thing: MudObject, message: str, to: MudObject) -> None:
            if (!objectp(room)) {
            room = query_shadowing(self)


    def free_location(self, ) -> None:
            if (sizeof(all_inventory(room)) || (int)self.dont_free())
            return
            TERRAIN_MAP.delete_cloned_location(terrain_name, file_name(room))
            room.dest_me()


    def set_destination(self, direc: str) -> None:
            int i, j, delta, *co_ords, *new_co_ords = allocate(3)
            string dest_name
            object destination
            if ((i = STD_ORDERS.index(direc) if direc in STD_ORDERS else -1) == -1) {
            return


    def query_quit_handler(self, ) -> str:
            mixed *query_cloning_info() {
            return [TERRAIN_MAP, "find_location",
            terrain_name, (int *)room.query_co_ord()]



class Terrain(MudObject):
