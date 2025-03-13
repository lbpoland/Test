# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/council_vote.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_status(self, ) -> int:
            string person
            string* nominated
            string* magistrates
            string ret
            if (!NOMIC_HANDLER.is_citizen_of(query_council_area(),
            this_player()->query_name())) {
            add_failed_mess("You must be a citizen to see this information.\n")
            return 0


    def do_vote(self, person: str, force: int) -> int:
            string* bits
            if (!NOMIC_HANDLER.is_citizen_of(query_council_area(),
            this_player()->query_name())) {
            add_failed_mess("You must be a citizen to vote.\n")
            return 0


    def do_nominate(self, person: str) -> int:
            person = lower_case(person)
            if (!NOMIC_HANDLER.is_citizen_of(query_council_area(),
            this_player()->query_name())) {
            add_failed_mess("You must be a citizen to nominate someonej.\n")
            return 0


    def do_list_motions(self, ) -> int:
            class nomic_motion* rules
            class nomic_motion rule
            int is_mag
            string ret
            rules = NOMIC_HANDLER.query_all_motions(query_council_area())
            is_mag = NOMIC_HANDLER.is_magistrate_of(query_council_area(),
            this_player()->query_name())
            if (!is_mag) {
            rules = filter(rules, (: $1->state == NOMIC_STATE_CITIZEN_VOTE :))


    def do_vote_on(self, num: int, vote: str) -> int:
            class nomic_motion rule
            int is_mag
            int vote_id
            rule = NOMIC_HANDLER.query_motion(query_council_area(), num)
            is_mag = NOMIC_HANDLER.is_magistrate_of(query_council_area(),
            this_player()->query_name())
            if (!rule || (!is_mag && rule->state != NOMIC_STATE_CITIZEN_VOTE)) {
            add_failed_mess("Could not find the motion " + num + ".\n")
            return 0


    def add_vote(self, type: str, description: str, choices: str, ending: int) -> None:
            string mess
            ::add_vote(type, description, choices, ending)
            mess = "New vote on:\n" + description + "\nWith choices of " +
            query_multiple_short(choices) + ".\n",
            NOMIC_HANDLER.post_citizen_message(query_council_area(), "New vote by " +
            this_player()->query_cap_name(),
            mess)


    def init(self, ) -> None:
            basic_room::init()
            voting_room::init()
            add_command("list", "elections", (: do_status() :))
            add_command("list", "motions", (: do_list_motions() :))
            add_command("information", "", (: do_status() :))
            add_command("status", "", (: do_status() :))
            add_command("vote", "{yes|no|abstain} in [motion] <number'id'>",
            (: do_vote_on($4[1], $4[0]) :))
            add_command("vote", "for <string'people'>", (: do_vote($4[0], 0) :))
            add_command("vote", "force for <string'people'>", (: do_vote($4[0], 1) :))
            add_command("nominate", "<string'person'>", (: do_nominate($4[0]) :))
            if (NOMIC_HANDLER.is_magistrate_of(query_council_area(),
            this_player()->query_name())) {
            init_add_vote()



class Council_vote(MudObject):
