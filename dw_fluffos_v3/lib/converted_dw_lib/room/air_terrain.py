# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/room/air_terrain.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_long("Flying up high in the air.")
            set_short("air room")


    def terrain_setup(self, ) -> None:
            int* coords
            int* ground_coords
            string ground_room
            string ground_base_str
            coords = query_terrain_coords()
            ground_room = query_terrain_handler()->query_ground_room(coords[0], coords[1])
            ground_coords = ground_room.query_terrain_coords()
            switch (coords[2] - ground_coords[2]) {
            case 0..100 :
            ground_base_str = ground_room.query_long()
            set_long("Down below you see: " + ground_base_str)
            break
            case 101..200 :
            set_long("Flying up high above " + ground_room.query_short() + ".")
            break
            default :
            set_long("High up in the sky.")
            break


    def event_enter(self, ob: MudObject) -> None:
            if (ob.query_property("flying")) {
            return


    def plumet_down(self, ob: MudObject) -> None:
            int* coords
            int* ground_coords
            class coord coords_real
            class coord ground_coords_real
            int z
            int damage
            int dist
            object room
            if (environment(ob) != self || ob.query_property("flying")) {
            return


    def query_death_message(self, ) -> str:
            return "from forgetting they cannot fly"


    def query_theft_command(self, ) -> int:
            return 1


    def can_enter_from(self, key: str, direc: str) -> int:
            return 0


    def can_exit_to(self, key: str, direc: str) -> int:
            return 0



class Air_terrain(MudObject):
