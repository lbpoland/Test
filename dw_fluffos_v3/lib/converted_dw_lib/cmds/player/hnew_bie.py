# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/hnew_bie.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> int:
            mixed *history
            string result
            history = HIST.query_chat_history("newbie")
            if ( !arrayp( history ) || !sizeof( history ) ) {
            tell_object(this_player(), "Nothing has been said on the newbie "
            "channel.\n")



class Hnew_bie(MudObject):
