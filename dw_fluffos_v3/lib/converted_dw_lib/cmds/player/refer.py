# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/refer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> int:
            string ret
            str = lower_case(str)
            str = (string)this_player()->expand_nickname(str)
            ret = (string)"/secure/finger"->refer_info(str)
            if (ret) {
            this_player()->more_string( this_player()->fit_message(ret),
            "refer: "+str )
            return 1



class Refer(MudObject):
