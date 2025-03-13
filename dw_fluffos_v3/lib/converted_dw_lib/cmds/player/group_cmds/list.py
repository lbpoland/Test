# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/list.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_list_groups(self, person: str) -> int:
            string party, *partys, prefix, suffix, message, adjective, colour, stats
            object *members, leader
            int num_partys, num_members
            object person_ob
            partys = sort_array( GROUP.query_partys(),
            (: strcmp( lower_case(GROUP.query_party_short( $1 )),
            lower_case(GROUP.query_party_short( $2 )) ) :) )
            num_partys = sizeof( partys )
            if (person) {
            person = this_player()->expand_nickname(person)
            person_ob = find_player(person)
            if (!person_ob) {
            add_failed_mess("Sorry, " + person + " is not logged on.\n")
            return 0


    def query_help_string_for(self, sub: str) -> str:
            return "This command lets you list all currently active "
            "partys and their members and leaders."



class List(MudObject):
