# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/invite.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_invite(self, persons: MudObject, group: str) -> int:
            object person
            persons -= [this_player()]
            if( !sizeof( persons ) ) {
            return notify_fail( "I would come up with "
            "something witty, but I'm not going to "
            "bother.\n" )


    def query_help_string_for(self, sub: str) -> str:
            return "With this command the leader of a party can invite new "
            "members to the party.  A person who has been invited must then "
            "use the \"join\" command to actually become a member."



class Invite(MudObject):
