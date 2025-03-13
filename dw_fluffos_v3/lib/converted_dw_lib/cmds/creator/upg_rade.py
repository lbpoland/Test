# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/upg_rade.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            seteuid(geteuid(this_player()))
            (clone_object("/secure/login"))->do_upgrade(this_player())
            return 1


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()



class Upg_rade(MudObject):
