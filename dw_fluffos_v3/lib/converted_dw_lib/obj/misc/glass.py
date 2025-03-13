# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/glass.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init_static_arg(self, map: Any) -> None:
            if (map["::"])
            ::init_static_arg(map["::"])
            if (!undefinedp(map["description"]))
            description = map["description"]
            if (!undefinedp(map["actual_drink"]))
            actual_drink = map["actual_drink"]
            if (!undefinedp(map["actual_glass_size"]))
            actual_glass_size = map["actual_glass_size"]
            set_long((: self.query_volume() ? description : "This is "
            "a dirty " + actual_glass_size + ", one that used to hold some "
            "sort of " + actual_drink + ".\n" :))


    def query_static_auto_load(self, ) -> Any:
            if (base_name(self) == "/obj/misc/glass" )
            return int_query_static_auto_load()
            return ([ ])



class Glass(MudObject):
