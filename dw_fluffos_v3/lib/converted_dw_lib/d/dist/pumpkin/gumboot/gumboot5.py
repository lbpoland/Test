# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/gumboot/gumboot5.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Gumboot Road")
            set_long("This is end of Gumboot Road at the edge of the city of Pumpkin.\n")
            set_light( 80 )
            add_exit("east", TERRAIN_HANDLER + ":0:1:0", "road")
            add_exit("north", GUMBOOT + "gumboot4", "road")
            set_monster(1, "city")



class Gumboot5(MudObject):
