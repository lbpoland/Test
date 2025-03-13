# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/virtual/data_compiler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def initialize_methods(self, ) -> None:
            SERVER.add_method("s",  file_name(self), "compile_soul", 1)
            SERVER.add_method("r_n",  file_name(self), "compile_random_name", 1)


    def compile_soul(self, name: str, int) -> MudObject:
            object ob
            if (name[0] != '/')
            name = "/"+name
            if (name[0..strlen(SOUL_DIR)-1] != SOUL_DIR) {
            return 0


    def compile_random_name(self, name: str, clone: int) -> MudObject:
            object ob
            if (name[0] != '/')
            name = "/"+name
            if (name[0..strlen(RANDOM_NAME_DATA_DIR)-1] != RANDOM_NAME_DATA_DIR) {
            return 0



class Data_compiler(MudObject):
