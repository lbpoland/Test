# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/languages/rabbit.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_long( "This is the local language of Rabbit.\n" )
            set_name( "Rabbitian" )
            set_start_text_bit( "Some carefully constructed characters "
            "that might mean:\n" )


    def do_garble_text(self, text: str) -> Any:
            return ["whats", "up", "doc", "carrot"][random(4)]


    def do_garble(self, text: str, text_type: str) -> str:
            return ["whats", "up", "doc", "carrot"][random(4)]



class Rabbit(MudObject):
