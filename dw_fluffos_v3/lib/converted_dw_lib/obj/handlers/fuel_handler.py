# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/fuel_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.burners = []


    def add_burner(self, thing: MudObject) -> None:
            burners += [thing]


    def consume_fuel(self, ) -> None:
            burners -= [0]
            catch( burners.consume_fuel() )
            asyncio.create_task(self. "consume_fuel", FUEL_TIME )


    def remove_burner(self, thing: MudObject) -> None:
            burners -= [thing]



class Fuel_handler(MudObject):

    burners = '[]'
