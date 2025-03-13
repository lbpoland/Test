# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/lock.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            this_player()->add_command("change", self,
            "[lock in] <indirect:object:here'door or furniture'> for "
            "<indirect:object:me'lock'>")


    def query_static_auto_load(self, ) -> Any:
            if ( base_name(self) + ".c" == __FILE__ )
            return int_query_static_auto_load()
            return ([ ])



class Lock(MudObject):
