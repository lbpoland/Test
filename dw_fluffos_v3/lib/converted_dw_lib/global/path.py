# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/path.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def get_path(self, str: str) -> str:
            string *array
            string *array1
            string temp
            int i
            if (!str) {
            if(!home_dir) {
            home_dir = "/w/" + this_player()->query_name()


    def query_current_path(self, ) -> str:
            return current_path


    def query_home_dir(self, ) -> str:
            return home_dir


    def set_current_path(self, str: str) -> None:
            current_path = str



class Path(MudObject):
