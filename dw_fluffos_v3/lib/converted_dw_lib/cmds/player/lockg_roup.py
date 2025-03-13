# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/lockg_roup.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            object owner
            int locked
            str = TEAM_HANDLER.query_party(this_player())
            if(!str)
            return notify_fail("You are not a member of any party.\n")
            owner = TEAM_HANDLER.query_owner(str)
            if(!owner || owner != this_player())
            return notify_fail("Sorry, you are not the owner of "+str+".\n")
            locked = TEAM_HANDLER.query_locked(str)
            if(locked) {
            TEAM_HANDLER.set_locked(str, 0)
            write("Team "+str+" unlocked for new members.\n")
            } else {
            TEAM_HANDLER.set_locked(str, 1)
            write("Team "+str+" locked to new members.\n")



class Lockg_roup(MudObject):
