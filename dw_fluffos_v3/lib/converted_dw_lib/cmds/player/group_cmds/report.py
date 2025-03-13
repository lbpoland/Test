# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/report.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_report(self, group: str) -> int:
            string message
            message = this_player()->query_cap_name() + " reports that " +
            this_player()->query_pronoun() + " is "
            message += GROUP_CMD_STATUS.generate_status_message( this_player() )
            GROUP.notify_party( party, this_player(), ({
            "You report:  " + message,
            message
            }) )
            return 1


    def query_help_string_for(self, sub_command: str) -> str:
            return "This command lets you report your current "
            "condition on the party's channel."



class Report(MudObject):
