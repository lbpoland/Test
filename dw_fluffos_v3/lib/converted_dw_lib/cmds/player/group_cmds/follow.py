# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/follow.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_group_follow(self, who: MudObject, group: str, unfollow: int) -> int:
            int size
            string fault_message
            object *what_not, *follow, *already_following
            fault_message = ""
            who -= [0]
            if( who .index( this_player()) if  this_player() in who  else -1 != -1 ) {
            who -= [this_player()]
            fault_message += "You cannot follow yourself.  "


    def query_help_string_for(self, sub: str) -> str:
            switch( sub ) {
            case "follow":
            return "This command lets you follow your fellow "
            "party members.  Using \"all\" will only target "
            "all party members, not all people, in the room.\n"
            case "unfollow":
            return "This command lets you stop following your fellow "
            "party members.  Using \"all\" will only target "
            "all party members, not all people, in the room.\n"



class Follow(MudObject):
