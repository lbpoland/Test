# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/preload.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def preload(self, file: str) -> None:
            mixed e
            printf("Preloading: "+file+".\n")
            if ((e = catch(load_object(file)))) {
            printf("            "+e+"\n")



class Preload(MudObject):
