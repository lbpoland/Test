# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/valid_override.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def valid_override(self, file: str, func: str, filename: str) -> int:
            string *bing
            bing = explode(file, "/") - ["", "."]
            switch (bing[0]) {
            case "secure" :
            return 1
            case "std" :
            case "obj" :
            case "simul_efun" :
            case "global" :
            case "cmds" :
            return (func != "snoop")
            default :
            return 0



class Valid_override(MudObject):
