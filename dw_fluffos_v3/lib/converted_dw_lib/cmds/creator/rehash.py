# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/rehash.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            if (!str)
            return notify_fail("Syntax: rehash <path>\n")
            if (file_size(str) != -2)
            return notify_fail(str+": Path not found.\n")
            if (str[0..4] == "/doc/") {
            "/cmds/player/help"->rehash_specific_dir(str)
            write("Rehashed help dir: " + str + "\n")
            return 1


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()



class Rehash(MudObject):
