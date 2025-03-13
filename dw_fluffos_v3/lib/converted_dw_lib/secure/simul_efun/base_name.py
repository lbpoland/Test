# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/base_name.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def base_name(self, val: Any) -> str:
            string name, base
            if(!val)
            return ""
            if (stringp(val))
            name = val
            else
            name = file_name(val)
            if (sscanf(name, "%s#%*d", base) == 2)
            return base
            return name



class Base_name(MudObject):
