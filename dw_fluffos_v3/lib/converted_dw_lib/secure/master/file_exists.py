# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/file_exists.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def file_exists(self, path: str) -> int:
            if ( file_size( path ) < 0 )
            return 0
            return 1



class File_exists(MudObject):
