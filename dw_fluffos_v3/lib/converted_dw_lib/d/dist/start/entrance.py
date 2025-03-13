# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/start/entrance.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("entrance")
            set_long("You are standing at the entrance to a big wide, well quite small, "
            "area.  Welcome to the Faerûnworld mud distribution lib entrance.\n")
            set_light(70)
            add_exit("pumpkin", CONFIG_START_LOCATION, "road")



class Entrance(MudObject):
