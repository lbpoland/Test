# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/create.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_create(self, name: str) -> int:
            string short
            name = strip_colours(name)
            if( this_player()->query_party() ) {
            return notify_fail( "You are already a member of " +
            this_player()->query_party() + ".\n" )


    def query_help_string_for(self, sub_command: str) -> str:
            if( sub_command != "create" ) {
            return 0



class Create(MudObject):
