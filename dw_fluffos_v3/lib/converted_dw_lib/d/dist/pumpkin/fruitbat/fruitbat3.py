# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/fruitbat/fruitbat3.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Fruitbat Avenue")
            set_long("This is the middle of Fruitbat Avenue just south of the "
            "vault.\n")
            set_light( 80 )
            add_exit("east", FRUITBAT + "fruitbat4", "road")
            add_exit("west", FRUITBAT + "fruitbat2", "road")
            add_exit("north", FRUITBAT + "walrus_vault_entry", "door")
            set_monster(1, "city")



class Fruitbat3(MudObject):
