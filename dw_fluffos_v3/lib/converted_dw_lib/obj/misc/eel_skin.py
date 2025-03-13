# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/eel_skin.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            {
            set_name( "skin" )
            set_short( "eel skin" )
            add_adjective( "eel" )
            set_main_plural( "eel skins" )
            set_long( "This is the skin of an eel.  It is very greasy and "
            "glistens prettily when you tilt it towards the light.\n" )
            set_weight( 3 )
            set_value( 100 )



class Eel_skin(MudObject):
