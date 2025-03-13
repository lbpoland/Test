# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/delevent.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def delete_event(self, s1: str, s2: str, n: int) -> int:
            {
            string  who = lower_case(s1)
            string  event = lower_case(s2)
            if(!PLAYER_HANDLER.test_user(who)) {
            write("No such player: "+who+".  \n")
            return 1



class Delevent(MudObject):
