# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/valid_binary.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def valid_save_binary(self, fname: str) -> int:
            string *bits
            bits = explode(fname, "/")
            switch (bits[0]) {
            case "global" :
            case "std" :
            case "secure" :
            case "cmds" :
            case "d" :
            case "www" :
            return 1
            case "obj" :
            return 1



class Valid_binary(MudObject):
