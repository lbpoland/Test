# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/export_inventory.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.registered_containers = []


    def add_inventory_container(self, cont: MudObject) -> None:
            if (registered_containers.index(cont) if cont in registered_containers else -1 == -1 &&
            environment(cont) == self) {
            registered_containers += [cont]


    def remove_inventory_container(self, cont: MudObject) -> None:
            if(!registered_containers || !cont)
            return
            registered_containers -= [cont]


    def set_can_export_inventory(self, ) -> None:
            can_export_inventory = 1


    def reset_can_export_inventory(self, ) -> None:
            can_export_inventory = 0


    def query_can_export_inventory(self, ) -> int:
            return can_export_inventory



class Export_inventory(MudObject):

    registered_containers = '[]'
