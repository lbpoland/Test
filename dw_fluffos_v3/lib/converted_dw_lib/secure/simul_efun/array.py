# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/array.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def delete(self, arr: Any, start: int, len: int) -> Any:
            return arr[0..start-1] + arr[start+len..]


    def insert(self, arr: Any, el: Any, pos: int) -> Any:
            if (stringp(arr))
            return arr[0..pos-1] + el + arr[pos..]
            return arr[0..pos-1] + [el] + arr[pos..]



class Array(MudObject):
