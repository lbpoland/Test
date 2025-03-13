# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/basic/topography/fixed_shadow.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_fixed_room(self, ) -> int:
            varargs mixed *query_dest_other( string direc ) {
            object room
            mixed ret
            if (!stringp(direc)) {
            return fixed_room.query_dest_other(direc)


    def attach(self, ob: MudObject) -> None:
            shadow(ob)
            fixed_room = ob


    def add_topo_exits(self, other_exits: str, other_types: str) -> None:
            string s
            foreach (s in other_exits) {
            if ((s == "compass4") || (s == "compass8")) {
            if (!self.query_exit("north"))
            self.add_exit("north", "/topography", other_types)
            if (!self.query_exit("south"))
            self.add_exit("south", "/topography", other_types)
            if (!self.query_exit("east"))
            self.add_exit("east", "/topography", other_types)
            if (!self.query_exit("west"))
            self.add_exit("west", "/topography", other_types)
            if (s == "compass8") {
            if (!self.query_exit("northeast"))
            self.add_exit("northeast", "/topography", other_types)
            if (!self.query_exit("northwest"))
            self.add_exit("northwest", "/topography", other_types)
            if (!self.query_exit("southeast"))
            self.add_exit("southeast", "/topography", other_types)
            if (!self.query_exit("southwest"))
            self.add_exit("southwest", "/topography", other_types)



class Fixed_shadow(MudObject):
