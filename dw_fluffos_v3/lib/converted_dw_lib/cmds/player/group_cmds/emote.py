# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/emote.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_group_emote(self, message: str, group: str) -> int:
            message = replace( message, ["%^", "",] )
            GROUP.notify_party( party, this_player(), ({
            "You emote: " + this_player()->query_cap_name() + " " + message,
            this_player()->query_cap_name() + " " + message
            }) )
            return 1


    def query_help_string_for(self, sub: str) -> str:
            return "This command allows you to emote on the party "
            "channel."



class Emote(MudObject):
