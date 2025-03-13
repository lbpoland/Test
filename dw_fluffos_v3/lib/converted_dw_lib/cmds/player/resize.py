# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/resize.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            printf("%c%c%c", IAC, DO, TELOPT_NAWS)
            write("Okay, resizing your terminal...\n")
            return 1



class Resize(MudObject):
