# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/gstat_us.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            string party
            string locked
            object member
            return notify_fail( "This command is no longer used.  Please use the "
            "\"party\" command from now on.  Also have a read of \"help "
            "partying\".\n" )
            party = TEAM_HANDLER.query_party(this_player())
            if(!party || !TEAM_HANDLER.query_members(party))
            return notify_fail("You are not a member of any party.\n")
            if(TEAM_HANDLER.query_locked(party))
            locked = "(locked) "
            else
            locked = ""
            printf("Members of %s%s:\n", locked, party)
            printf("%-12s %|20s   Idle\n", "Name", "Health")
            foreach(member in TEAM_HANDLER.query_members(party)) {
            if(member && interactive(member))
            printf("%-12s %-20s %3d:%02d\n", member.short(),
            member.health_string(), (query_idle(member)/60),
            (query_idle(member)%60))
            else if(member)
            printf("%s\n", member.short())



class Gstat_us(MudObject):
