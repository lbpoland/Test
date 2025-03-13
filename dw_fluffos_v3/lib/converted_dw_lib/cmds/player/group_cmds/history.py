# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/history.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_channel_history(self, ) -> int:
            this_player()->display_party_history()
            return 1


    def query_help_string_for(self, sub: str) -> str:
            return "This command lets you recap what has been said on your "
            "party's channel."



class History(MudObject):
