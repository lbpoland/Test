# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/sqrt.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def sqrt(self, number: Any) -> Any:
            if (floatp(number))
            return efun::sqrt(number)
            if (!intp(number))
            error("Bad argument 1 to sqrt()\nExpected: int or float Got: "+
            typeof(number)+ ".\n")
            if ( number < 0 )
            return -1
            return to_int(efun::sqrt(to_float(number)))



class Sqrt(MudObject):
