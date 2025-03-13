# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/loader.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.pre_load = []
            self.for (i = 0;i<sizeof(pre_load);i++) {


    def do_load(self, str: str) -> None:
            call_other(str, "??")


    def add_pre_load(self, str: str) -> int:
            if (pre_load.index(str) if str in pre_load else -1 == -1)
            pre_load += [str]
            save_object(file_name(self))
            return 1


    def remove_pre_load(self, str: str) -> int:
            int i
            if ((i=pre_load.index(str) if str in pre_load else -1) == -1)
            return 0
            pre_load = delete(pre_load, i, 1)
            save_object(file_name(self))



class Loader(MudObject):

    pre_load = '[]'

    for (i = '0;i<sizeof(pre_load);i++) {'
