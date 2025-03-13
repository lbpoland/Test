# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/mailinfo.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            if (!str || str=="")
            str = this_player()->query_name()
            else
            str = this_player()->expand_nickname(str)
            if (!PLAYER_HANDLER.test_user(lower_case(str)))
            {
            write("Sorry, but I don't know any "+capitalize(str)+".\n")
            return 1


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()



class Mailinfo(MudObject):
