# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/holdable.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def dest_me(self, ) -> None:
            holdable::dest_me()
            object::dest_me()


    def query_dynamic_auto_load(self, ) -> Any:
            return ([ "::" : object::query_dynamic_auto_load(),
            "hold" : holdable::query_dynamic_auto_load(),
            ])


    def init_dynamic_arg(self, arg: Any) -> None:
            if (arg["hold"]) {
            holdable::init_dynamic_arg(arg["hold"], arg["is lit"])


    def init_static_arg(self, map: Any) -> None:
            if ( !mapp( map ) ) {
            return



class Holdable(MudObject):
