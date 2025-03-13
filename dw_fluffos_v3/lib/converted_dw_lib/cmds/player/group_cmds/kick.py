# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/kick.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_kick_member(self, member: MudObject, group: str) -> int:
            if( this_player() == member ) {
            this_player()->new_parser(
            "skick " + this_player()->query_name() )
            return 1


    def query_help_string_for(self, sub: str) -> str:
            return "This command lets you boot out offending members in "
            "your party."



class Kick(MudObject):
