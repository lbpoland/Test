# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/joing_roup.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            object owner, person
            int policy
            if(!str)
            return notify_fail("Syntax: joinparty <party name>\n")
            if(TEAM_HANDLER.query_party(this_player()))
            return notify_fail("You are already a member of a party.\n")
            if(!TEAM_HANDLER.test_party(str))
            return notify_fail("Sorry, there is no party by that name.\n")
            owner = TEAM_HANDLER.query_owner(str)
            if(!owner || environment(owner) != environment(this_player()))
            return notify_fail("Sorry, the owner of "+str+" is not here.\n")
            if(TEAM_HANDLER.query_full(str))
            return notify_fail("Sorry, that party is full, you cannot join.\n")
            if(TEAM_HANDLER.query_locked(str))
            return notify_fail("Sorry, that party is locked, you cannot join.\n")
            policy = TEAM_HANDLER.query_policy(str)
            if(!TEAM_HANDLER.join_party(str, this_player()))
            return notify_fail("Ack, something went wrong.\n")
            foreach(person in TEAM_HANDLER.query_members(str)) {
            if(person && present(person, environment(this_player())) &&
            person != this_player()) {
            this_player()->add_protector(person)
            person.add_protector(this_player())
            if(policy == 1)
            this_player()->add_follower(person)
            if((policy == 1) || (person == owner))
            person.add_follower(this_player())



class Joing_roup(MudObject):
