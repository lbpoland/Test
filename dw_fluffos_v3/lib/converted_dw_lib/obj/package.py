# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/package.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_value(self, ) -> int:
            int value
            object ob
            value = ::query_value()
            foreach(ob in all_inventory())
            value += ob.query_value()
            return value


    def query_static_auto_load(self, ) -> Any:
            if ( base_name(self) + ".c" == __FILE__ )
            return int_query_static_auto_load()
            return ([ ])



class Package(MudObject):
