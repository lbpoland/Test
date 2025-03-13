# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/leader.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_leader(self, member: MudObject, group: str) -> int:
            if( member == this_player() ) {
            return notify_fail( "Oh, good thinking, sparky.\n" )


    def query_help_string_for(self, sub: str) -> str:
            return "This command allows you to relinquish command and "
            "appoint a new leader for the party.  It does not remove "
            "your membership of the party, but you lose all special "
            "privileges granted to leaders."



class Leader(MudObject):
