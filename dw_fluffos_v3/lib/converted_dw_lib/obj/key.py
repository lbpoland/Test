# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/key.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_type(self, str: str) -> None:
            remove_adjective(type)
            type = str
            add_adjective(type)
            set_main_plural(type + " keys")
            set_short(type + " key")


    def query_type(self, ) -> str:
            return type


    def __init__(self):
            self.type = "normal"



class Key(MudObject):

    type = '"normal"'
