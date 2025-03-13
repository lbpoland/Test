# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/rename.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_rename_group(self, new_group: str, group: str) -> int:
            string short
            string name
            if( GROUP.is_party( new_party ) ) {
            return notify_fail( new_party + " already exists.\n")


    def query_help_string_for(self, sub: str) -> str:
            return "This command lets you rename a party to something more "
            "exciting."



class Rename(MudObject):
