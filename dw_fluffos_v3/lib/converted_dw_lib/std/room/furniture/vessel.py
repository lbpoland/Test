# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/vessel.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            item_chat::init()


    def get(self, dest: Any) -> int:
            if(!move_check(dest)) {
            write("You feel it would be wrong to take " + the_short() + ".\n")
            return 2


    def query_static_auto_load(self, ) -> Any:
            if ( base_name(self) + ".c" == __FILE__ ) {
            return int_query_static_auto_load()


    def query_dynamic_auto_load(self, ) -> Any:
            mapping junk
            junk = vessel::query_dynamic_auto_load()
            if (!junk) {
            junk = ([ ])


    def init_dynamic_arg(self, map: Any) -> None:
            vessel::init_dynamic_arg(map)
            set_bonded(map["bonded"])


    def query_help_file_directory(self, ) -> str:
            return "/doc/furniture/"



class Vessel(MudObject):
