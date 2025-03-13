# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/valid_to_c.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def valid_compile_to_c(self, ) -> int:
            if (previous_object() == self)
            return 1
            if (previous_object() != find_object("/secure/cmds/creator/compile"))
            return 0
            if (!interactive(previous_object(1)))
            return 0
            if (!self.query_lord(previous_object(-1)))
            return 0
            return 1



class Valid_to_c(MudObject):
