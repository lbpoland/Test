# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/close_lock_container.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_closed(self, ) -> None:
            ::set_closed()
            if (environment()) {
            environment()->remove_inventory_container(self)


    def reset_closed(self, ) -> None:
            ::set_closed()
            if (environment()) {
            environment()->add_inventory_container(self)


    def we_moved(self, from: MudObject, to: MudObject) -> None:
            if (!query_closed()) {
            if (from) {
            from.remove_inventory_container(self)


    def dest_me(self, ) -> None:
            if (environment()) {
            environment()->remove_inventory_container(self)



class Close_lock_container(MudObject):
