# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/amtime.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def ordinal(self, number: int) -> str:
            if ( ( number % 100 > 10 ) && ( number % 100 < 14 ) )
            return number +"th"
            if ( number % 10 == 1 )
            return number +"st"
            if ( number % 10 == 2 )
            return number +"nd"
            if ( number % 10 == 3 )
            return number +"rd"
            return number +"th"



class Amtime(MudObject):
