# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/council_citizenship.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._waiting_approval = ([ ])
            self._blacklist = ([ ])
            self._denied = ([ ])
            self._approved = ([ ])
            self._last_posted = time()


    def init(self, ) -> None:
            add_command("apply", "[for] [citizenship]", (: do_apply() :))
            add_command("sponsor", "<string'person'> for citizenship",
            (: do_sponsor($4[0]) :))
            add_command("deny", "<string'person'> for citizenship because <string'reason'>",
            (: do_deny($4[0], $4[1]) :))
            add_command("list", "", (: do_list() :))
            add_command("expression", "list",
            (: do_list_expression() :))
            if (NOMIC_HANDLER.is_magistrate_of(query_council_area(),
            this_player()->query_name()) ||
            master()->query_lord(this_player()->query_name())) {
            add_command("blacklist", "add <string'person'> for <string'reason'>",
            (: do_add_blacklist($4[0], $4[1]) :))
            add_command("blacklist", "remove <string'person'>",
            (: do_remove_blacklist($4[0]) :))
            add_command("blacklist", "list {verbose|brief}",
            (: do_list_blacklist($4[0] == "verbose") :))
            add_command("expression", "citizen <string'citizenship'>",
            (: do_set_expression($4[0], 0) :))
            add_command("expression", "sponsor <string'citizenship'>",
            (: do_set_expression($4[0], 1) :))
            add_command("list", "denied", (: do_list_denied :))
            add_command("approve", "<string'person'> for citizenship",
            (: do_approve($4[0]) :))


    def set_save_file(self, fname: str) -> None:
            _save_file = fname
            load_me()


    def query_save_file(self, ) -> str:
            return _save_file


    def load_me(self, ) -> None:
            if (!_save_file) {
            return


    def save_me(self, ) -> None:
            if (!_save_file) {
            return


    def post_weekly_results(self, ) -> None:
            string post
            string* cit
            string person
            string denied
            cit = sort_array(keys(_approved), 1)
            if (sizeof(cit) > 0) {
            post = "Here are the weekly citizenship application results:\n\n"
            denied = ""
            foreach (person in cit) {
            if (!_approved[person]->denied) {
            if (sizeof(_approved[person]->info->sponsors)) {
            post += "  " + capitalize(person) + " " +
            ctime(((class approval_list)_approved[person]->info)->time_added)[4..9] +
            " sponsors " +
            query_multiple_short(map(_approved[person]->info->sponsors,
            (: capitalize($1) :)))
            } else {
            post += "  " + person + " no sponsor"


    def do_apply(self, ) -> int:
            class approval_list womble
            string str
            if (NOMIC_HANDLER.is_citizen_of(query_council_area(),
            this_player()->query_name())) {
            add_failed_mess("You are already a citizen.\n")
            return 0


    def do_sponsor(self, person: str) -> int:
            string str
            if (!PLAYER_HANDLER.test_user(person)) {
            add_failed_mess("Sorry, " + person + " is not a player.\n")
            return 0


    def do_approve(self, person: str) -> int:
            person = lower_case( person )
            if (!PLAYER_HANDLER.test_user(person)) {
            add_failed_mess("Sorry, " + person + " is not a player.\n")
            return 0


    def do_deny(self, person: str, reason: str) -> int:
            class denied fluff
            if (!PLAYER_HANDLER.test_user(person)) {
            add_failed_mess("Sorry, " + person + " is not a player.\n")
            return 0


    def do_list(self, ) -> int:
            string ret
            string ret_tmp
            string ret_no_sponsor
            int magistrate
            string* people
            string person
            string denier
            string reason
            int index
            int last
            int no_sponsor
            if (!sizeof(_waiting_approval)) {
            add_failed_mess("No one is waiting for citizenship approval.\n")
            return 0


    def do_list_denied(self, ) -> int:
            string* people
            string person
            string ret
            if (!sizeof(_denied)) {
            add_failed_mess("No one has been denied yet.\n")
            return 0


    def do_list_expression(self, ) -> int:
            string str
            str = query_expression_string(_expression, 0)
            write("The expression to check to make sure someone is allowed to "
            "apply for citizenship is:\n" + str + "\n")
            str = query_expression_string(_sponsor_expression, 0)
            write("The expression to check to make sure someone is allowed to "
            "sponsor an application for citizenship is:\n" + str + "\n")
            return 1


    def do_set_expression(self, expression: str, sponsor_expr: int) -> int:
            class parse_node* expr
            if (!NOMIC_HANDLER.is_magistrate_of(query_council_area(),
            this_player()->query_name())) {
            add_failed_mess("Only magistrates can set an expression string.\n")
            return 0


    def do_add_blacklist(self, person: str, reason: str) -> int:
            class blacklist bing
            if (!NOMIC_HANDLER.is_magistrate_of(query_council_area(),
            this_player()->query_name())) {
            add_failed_mess("Only magistrates can manipulate the blacklist.\n")
            return 0


    def do_remove_blacklist(self, person: str) -> int:
            if (!NOMIC_HANDLER.is_magistrate_of(query_council_area(),
            this_player()->query_name())) {
            add_failed_mess("Only magistrates can manipulate the blacklist.\n")
            return 0


    def do_list_blacklist(self, verbose: int) -> int:
            string ret
            string* people
            string person
            people = keys(_blacklist)
            people = sort_array(people, 1)
            if (!sizeof(people)) {
            add_failed_mess("There is no one in the blacklist currently.\n")
            return 0


    def variable_age_in_days(self, player: MudObject) -> int:
            int bing
            bing = -player.query_time_on()
            return bing / (60 * 60 * 24)


    def variable_age_in_hours(self, player: MudObject) -> int:
            int bing
            bing = -player.query_time_on()
            return bing / (60 * 60)


    def variable_level(self, player: MudObject) -> int:
            return player.query_level()


    def variable_denied_in_days(self, player: MudObject) -> int:
            if (_denied[player.query_name()]) {
            return (time() - _denied[player.query_name()]->time_denied) / (60 * 60 * 24)


    def function_citizen_of(self, area: str, player: MudObject) -> int:
            return NOMIC_HANDLER.is_citizen_of(area, player->query_name())


    def function_magistrate_of(self, area: str, player: MudObject) -> int:
            return NOMIC_HANDLER.is_magistrate_of(area, player->query_name())


    def is_allowed_to_change(self, person: str) -> int:
            return NOMIC_HANDLER.is_magistrate_of(query_council_area(), person)



class Council_citizenship(MudObject):

    _waiting_approval = '([ ])'

    _blacklist = '([ ])'

    _denied = '([ ])'

    _approved = '([ ])'

    _last_posted = 'time()'
