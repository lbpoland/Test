# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/cst_at.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            object *ob, thing
            mixed *ob1, *thing1
            string s, bing
            string long_fields, temp
            int long_length
            bing = ""
            str = (string)this_player()->expand_nickname(str)
            ob = WIZ_PRESENT.wiz_present(str, this_player())
            if (!sizeof(ob)) {
            write("No such object.\n")
            return 1


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()



class Cst_at(MudObject):
