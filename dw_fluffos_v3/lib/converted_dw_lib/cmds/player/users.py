# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/users.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> int:
            int players, logins, login_q, first, creators, total
            string output, *str, *logins_n
            object pl
            str = [})
            foreach(pl in users()) {
            if (pl.query_login_ob())
            logins++
            else {
            str += [pl.query_cap_name()]
            if (pl.query_creator())
            creators++
            else
            players++



class Users(MudObject):
