# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/clock.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def chime(self, mess: str) -> None:
            int *co_ords
            if(environment(self)) {
            co_ords = (int *)environment(self)->query_co_ord()
            "/obj/handlers/broadcaster"->broadcast_event(users(), co_ords,
            mess, 20, 1, 0 )
            tell_room(environment(self), mess)


    def __init__(self):


    def get(self, dest: Any) -> int:
            if(!move_check(dest)) {
            write("You feel it would be wrong to take " + the_short() + ".\n")
            return 2


    def query_static_auto_load(self, ) -> Any:
            if ( base_name(self) + ".c" == __FILE__ ) {
            return int_query_static_auto_load()



class Clock(MudObject):
