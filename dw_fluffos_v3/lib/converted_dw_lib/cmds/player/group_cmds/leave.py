# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/leave.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_leave(self, group: str) -> int:
            if( !GROUP.remove_member( this_player()->query_party(),
            this_player() ) ) {
            return notify_fail( "You failed to leave the party "
            "for some odd-ball reason.\n" )


    def query_help_string_for(self, sub: str) -> str:
            return "This command allows you to leave your current "
            "party.  If you're the leader, a new one will be "
            "chosen at random from the remaining members."



class Leave(MudObject):
