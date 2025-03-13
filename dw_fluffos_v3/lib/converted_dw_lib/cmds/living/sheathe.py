# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/sheathe.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, : MudObject, : MudObject) -> int:
            object weapon
            object scabbard
            if( sizeof(weapons) > 1 ) {
            add_failed_mess( "You can only sheathe one thing at a time.\n" )
            return 0



class Sheathe(MudObject):
