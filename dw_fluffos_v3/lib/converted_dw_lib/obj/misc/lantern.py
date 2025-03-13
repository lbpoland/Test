# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/lantern.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            fuel_left = 3600
            is_lit    = 0
            set_name( "lantern" )
            set_main_plural( "lanterns")
            set_short( "lantern" )
            add_help_file("torch")
            set_long(function() {
            string str
            str = "This is a camping lantern, which smells of lamp oil.\n"
            if ( is_lit ) {
            return str + "The wick flickers inside spreading a dull "
            "glow.\n"



class Lantern(MudObject):
