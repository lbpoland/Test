# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/join.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_join(self, member: MudObject) -> int:
            string his_party, my_party
            his_party = member.query_party()
            if( this_player() == member ) {
            return notify_fail( "I could come up with something witty, "
            "but I'm not going to bother.\n" )


    def query_help_string_for(self, sub_command: str) -> str:
            switch( sub_command ) {
            case "join":
            return "This command lets you join an existing party.  To join, "
            "type \"party join <existing member>\" where "
            "<existing member> is someone who is already a member of the "
            "party you wish to be a part of.  You must be invited to a "
            "party by its leader before you can join."
            default:
            return 0



class Join(MudObject):
