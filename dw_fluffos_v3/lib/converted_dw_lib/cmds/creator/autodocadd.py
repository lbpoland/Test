# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/autodocadd.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> int:
            string *files
            string file
            files = this_player()->get_files(str)
            if (!sizeof(files)) {
            notify_fail("Unable to find the files " + str + ".\n")
            return 0



class Autodocadd(MudObject):
