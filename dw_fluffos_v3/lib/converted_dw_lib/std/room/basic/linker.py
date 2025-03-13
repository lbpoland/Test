# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/basic/linker.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def destruct_shadow(self, thing: MudObject) -> None:
            if(thing == self) {
            destruct(self)
            } else {
            thing.destruct_shadow(thing)


    def query_dynamic_preposition(self, ) -> str:
            return d_prep


    def query_static_preposition(self, ) -> str:
            return s_prep


    def query_room_name(self, ) -> str:
            return r_name


    def area_name(self, ) -> str:
            string *bits
            if(r_name) {
            return r_name


    def compose_start(self, ) -> str:
            if(s_prep == "") {
            return capitalize((string)room.the_short())


    def event_exit(self, person: MudObject, message: str, to: MudObject) -> None:
            int ad_flag, rm_flag, i
            string arrive, direc, *exits, link_mess, *link_array
            room.event_exit(person, message, to)
            if(!message) {
            return


    def event_enter(self, person: MudObject, message: str, from: MudObject) -> None:
            int ad_flag, rm_flag, i
            string direc, *exits, link_mess, *link_array
            room.event_enter(person, message, from)
            if(!message || !from) {
            return



class Linker(MudObject):
