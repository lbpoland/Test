# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/suspend.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def help(self, ) -> int:
            if(!"/secure/master"->query_lord(geteuid(previous_object())) &&
            !LIAISON.query_member(this_player()->query_name()))
            return notify_fail("You cannot use suspend.\n")
            if(this_player()->query_lord() ||
            master()->query_senior(geteuid(previous_object())) ||
            LIAISON.query_member(geteuid(previous_object())))
            write("suspend <name> <reason> -- will suspend a player for 2 hours.\n")
            #ifdef SUSPEND_MULTI
            if(this_player()->query_lord() ||
            LIAISON.query_deputy(geteuid(this_player())))
            write("suspend <name> multiplaying -- will suspend a multiplayer for "
            "2 weeks.\n")
            #endif
            if (LIAISON.query_deputy(geteuid(this_player()))) {
            write("suspend <name> <time> <reason> where time is in hours.\n")
            write ("You may suspend people for a maximum of "
            + query_num (MULTI_SUSPEND) + " hours as a liaison deputy.\n")



class Suspend(MudObject):
