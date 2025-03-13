# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/leaveg_roup.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            object member, *members
            string party
            int disband
            party = TEAM_HANDLER.query_party(this_player())
            if(!party)
            return notify_fail("You are not a member of any party.\n")
            members = TEAM_HANDLER.query_members( party )
            if ( !members) {
            TEAM_HANDLER.leave_party(party, this_player())
            TEAM_HANDLER.end_party( party )
            write( "Somehow your party has no members.  "
            "Your party has been ended.  "
            "I hope this is okay.\n" )
            return 1
            } else if(!(TEAM_HANDLER.query_owner(party))) {
            TEAM_HANDLER.leave_party( party, member )
            TEAM_HANDLER.end_party( party )
            write( "Somehow your party has no leader.  "
            "Your party has been ended.  "
            "I hope this is okay.\n" )
            return 1


    def do_leave(self, group: str, member: MudObject) -> int:
            object person
            if(!TEAM_HANDLER.leave_party(party, member))
            return notify_fail("Ack, something went wrong.\n")
            if ( !sizeof( (object *)TEAM_HANDLER.query_members( party ) ) )
            return 0
            foreach(person in TEAM_HANDLER.query_members(party)) {
            if(person) {
            member.remove_protector(person)
            person.remove_protector(member)
            member.remove_follower(person)
            person.remove_follower(member)



class Leaveg_roup(MudObject):
