# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/tra_ns.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            object *obs, ob
            if (!str || !(sizeof(obs = WIZ_PRESENT.wiz_present(str, this_player())))) {
            write("Transport who ?\n")
            return 1


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()



class Tra_ns(MudObject):
