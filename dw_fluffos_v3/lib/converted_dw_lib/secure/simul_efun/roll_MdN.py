# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/roll_MdN.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def roll_MdN(self, dice: int, sides: int) -> int:
            int roll
            if ( ( dice > 0 ) && ( sides > 0 ) ) {
            while ( dice ) {
            roll += 1 + random( sides )
            dice--



class Roll_mdn(MudObject):
