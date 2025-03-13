# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/council_chambers.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_list_rules(self, ) -> int:
            class nomic_rule* rules
            class nomic_rule rule
            string ret
            int cur_type
            rules = NOMIC_HANDLER.query_all_nomic_rules(query_council_area())
            if (!sizeof(rules)) {
            add_failed_mess("There are no rules, oh no!  Lawlessness!\n")
            return 0


    def do_list_one_rule(self, num: int) -> int:
            class nomic_rule rule
            string ret
            rule = NOMIC_HANDLER.query_nomic_rule(query_council_area(), num)
            if (!rule) {
            add_failed_mess("There is no rule number " + num + ".\n")
            return 0


    def do_list_single_motion(self, num: int) -> int:
            class nomic_motion* rules
            class nomic_motion rule
            int is_mag
            string ret
            rules = NOMIC_HANDLER.query_all_motions(query_council_area())
            is_mag = NOMIC_HANDLER.is_magistrate_of(query_council_area(),
            this_player()->query_name())
            if (!is_mag) {
            rules = filter(rules, (: $1->state == NOMIC_STATE_CITIZEN_VOTE :))


    def do_list_motions(self, brief: int) -> int:
            class nomic_motion* rules
            class nomic_motion rule
            int is_mag
            string ret
            rules = NOMIC_HANDLER.query_all_motions(query_council_area())
            is_mag = NOMIC_HANDLER.is_magistrate_of(query_council_area(),
            this_player()->query_name())
            if (!is_mag) {
            rules = filter(rules, (: $1->state == NOMIC_STATE_CITIZEN_VOTE :))


    def do_comment_on(self, num: int) -> int:
            class nomic_motion rule
            int is_mag
            rule = NOMIC_HANDLER.query_motion(query_council_area(), num)
            is_mag = NOMIC_HANDLER.is_magistrate_of(query_council_area(),
            this_player()->query_name())
            if (!rule || !is_mag && rule->state != NOMIC_STATE_CITIZEN_VOTE) {
            add_failed_mess("Could not find the motion " + num + ".\n")
            return 0


    def finish_comment_on(self, comment: str, nomic_motion: Any) -> None:
            if (!comment) {
            write("Aborting comment.\n")
            return


    def do_amend_motion(self, num: int) -> int:
            class nomic_motion rule
            int is_mag
            is_mag = NOMIC_HANDLER.is_magistrate_of(query_council_area(),
            this_player()->query_name())
            if (!is_mag) {
            add_failed_mess("You cannot amend rules.\n")
            return 0


    def finish_amend_motion(self, amendment: str, nomic_motion: Any) -> None:
            if (!amendment) {
            write("Aborting amendment.\n")
            return


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


    def do_amend_current_rule(self, num: int) -> int:
            class nomic_rule rule
            rule = NOMIC_HANDLER.query_nomic_rule(query_council_area(), num)
            if (!rule) {
            add_failed_mess("The rule " + num + " does not exist.\n")
            return 0


    def amend_current_rule(self, str: str, nomic_rule: Any) -> None:
            if (!str) {
            write("Aborting the addition of an amendment.\n")
            return


    def do_remove_current_rule(self, num: int) -> int:
            class nomic_rule rule
            rule = NOMIC_HANDLER.query_nomic_rule(query_council_area(), num)
            if (!rule) {
            add_failed_mess("The rule " + num + " does not exist.\n")
            return 0


    def do_create_motion(self, type: str) -> int:
            int type_no
            type_no = NOMIC_HANDLER.query_type_number(type)
            if (type_no == NOMIC_ERROR ||
            type_no == NOMIC_TYPE_IMMUTABLE) {
            add_failed_mess("The type " + type + " is invalid.\n")
            return 0


    def create_motion(self, str: str, type_no: int) -> None:
            if (!str) {
            write("Aborting the creation of the rule.\n")
            return


    def do_transmogrify_current_rule(self, num: int, new_type: str) -> int:
            class nomic_rule rule
            int new_type_no
            if (!NOMIC_HANDLER.is_magistrate_of(query_council_area(),
            this_player()->query_name())) {
            add_failed_mess("You cannot do this until you are a magistrate.\n")
            return 0


    def init(self, ) -> None:
            ::init()
            add_command("list", "[rules]", (: do_list_rules() :) )
            add_command("list", "rule <number>", (: do_list_one_rule($4[0]) :) )
            add_command("list", "motion <number'motion id'>",
            (: do_list_single_motion($4[0]) :))
            add_command("list", "motions", (: do_list_motions(1) :))
            add_command("list", "motions {verbose|brief}",
            (: do_list_motions($4[0] == "brief") :))
            add_command("comment", "on <number'motion id'>",
            (: do_comment_on($4[0]) :) )
            add_command("amend", "motion <number'motion id'>",
            (: do_amend_motion($4[0]) :) )
            add_command("vote", "{yes|no|abstain} for <number'motion id'>",
            (: do_vote_on($4[1], $4[0]) :))
            add_command("motion", "amend rule <number'rule id'>",
            (: do_amend_current_rule($4[0]) :) )
            add_command("motion", "create new rule <string'type'>",
            (: do_create_motion($4[0]) :) )
            add_command("motion", "remove rule <number'rule id'>",
            (: do_remove_current_rule($4[0]) :) )
            add_command("motion", "move rule <number'rule id'> to <string'type'>",
            (: do_transmogrify_current_rule($4[0], $4[1]) :) )



class Council_chambers(MudObject):
