# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/council_cases.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._types = ([ ])


    def __init__(self):
            self._types = ([ ])
            if (!query_punishment_type("dismissed")) {
            add_punishment_type("dismissed", NOMIC_PUNISHMENT_DIR + "dismissed")


    def add_punishment_type(self, name: str, file: str) -> None:
            _types[name] = file


    def query_punishment_type(self, name: str) -> str:
            return _types[name]


    def start_punishment(self, name: str, nomic_case: Any, finish: Any) -> None:
            string bing
            bing = query_punishment_type(name)
            if (bing) {
            bing.start_punishment(query_council_area(),
            the_case, name, finish)
            } else {
            write("Big hairy error.\n")


    def complete_punishment(self, name: str, nomic_case: Any, data: Any) -> None:
            string bing
            bing = query_punishment_type(name)
            if (bing) {
            bing.complete_punishment(query_council_area(),
            the_case, name, data)
            } else {
            write("Big hairy error.\n")


    def suspend_punishment(self, nomic_case: Any) -> None:
            string bing
            class nomic_case_event event
            string type
            mixed data
            foreach (event in the_case->events) {
            if (event->type == NOMIC_CASE_EVENT_CLOSE) {
            type = event->data[0]
            data = event->data[1]


    def query_extra_player_status(self, player: str) -> str:
            return 0


    def query_last_appealer(self, nomic_case: Any) -> str:
            class nomic_case_event event
            string ret
            ret = 0
            foreach (event in the_case->events) {
            if (event->type == NOMIC_CASE_EVENT_APPEAL) {
            ret = event->person


    def is_last_appealer(self, nomic_case: Any, person: str) -> int:
            return query_last_appealer(the_case) == person


    def query_last_closer(self, nomic_case: Any) -> str:
            class nomic_case_event event
            string ret
            ret = 0
            foreach (event in the_case->events) {
            if (event->type == NOMIC_CASE_EVENT_CLOSE) {
            ret = event->person


    def is_last_closer(self, nomic_case: Any, person: str) -> int:
            return query_last_closer(the_case) == person


    def do_list_punishments(self, ) -> int:
            string punish
            string file
            write("Punishments:\n")
            foreach (punish, file in _types) {
            write("   " + punish + "\n")


    def do_list_punishments_desc(self, type: str) -> int:
            string file
            write("Punishments:\n")
            file = _types[type]
            if (!file) {
            add_failed_mess("No punishment of type " + type + ".\n")
            return 0


    def do_open_case(self, people: str, short: str) -> int:
            string* bits
            string* bad
            string person
            people = replace_string(people, " and ", ",")
            people = replace_string(people, " ", "")
            bits = explode(lower_case(people), ",")
            bad = [})
            foreach (person in bits) {
            if (!PLAYER_HANDLER.test_user(person)) {
            bad += [person]


    def open_case_desc(self, desc: str, extra: Any) -> None:
            string* bits
            string short
            bits = extra[0]
            short = extra[1]
            if (!desc) {
            write("Aborted.\n")
            return


    def query_case_short(self, nomic_case: Any) -> str:
            string ret
            ret = "Case #" + the_case->id + " \"" +
            the_case->short + "\" opened by " + the_case->opener +
            " against " + query_multiple_short(the_case->people) + " at " +
            ctime(the_case->time_opened)
            return ret


    def do_list_open_cases(self, ) -> int:
            int* cases
            string ret
            class nomic_case the_case
            int id
            cases = NOMIC_HANDLER.query_open_cases(query_council_area())
            if (!sizeof(cases)) {
            add_failed_mess("There are no open cases.\n")
            return 0


    def do_list_closed_cases(self, ) -> int:
            int* cases
            string ret
            class nomic_case the_case
            int id
            cases = NOMIC_HANDLER.query_recently_closed_cases(query_council_area())
            if (!sizeof(cases)) {
            add_failed_mess("There are no recently closed cases.\n")
            return 0


    def do_list_case(self, case_id: int) -> int:
            string ret
            class nomic_case the_case
            class nomic_case_note note
            class nomic_case_event event
            int id
            ret = ""
            the_case = NOMIC_HANDLER.query_open_case(query_council_area(), case_id)
            if (!the_case) {
            add_failed_mess("Unable to find the case.\n")
            return 0


    def do_list_closed_case(self, case_id: int) -> int:
            string ret
            class nomic_case the_case
            class nomic_case_note note
            class nomic_case_event event
            int id
            int* cases
            ret = ""
            cases = NOMIC_HANDLER.query_recently_closed_cases(query_council_area())
            if (cases.index(case_id) if case_id in cases else -1 == -1) {
            add_failed_mess("Unable to find the case.\n")
            return 0


    def do_add_person(self, case_id: int, person: str) -> int:
            class nomic_case the_case
            the_case = NOMIC_HANDLER.query_open_case(query_council_area(), case_id)
            if (!the_case) {
            add_failed_mess("Unable to find the id of the case.\n")
            return 0


    def person_desc(self, desc: str, stuff: Any) -> None:
            int case_id
            string person
            string type
            class nomic_case the_case
            case_id = stuff[0]
            person = stuff[1]
            type = stuff[2]
            if (!desc) {
            write("Aborted " + type + "ing " + person + ".\n")
            return


    def do_remove_person(self, case_id: int, person: str) -> int:
            class nomic_case the_case
            the_case = NOMIC_HANDLER.query_open_case(query_council_area(), case_id)
            if (!the_case) {
            add_failed_mess("Unable to find the id of the case.\n")
            return 0


    def do_add_note(self, case_id: int) -> int:
            class nomic_case the_case
            the_case = NOMIC_HANDLER.query_open_case(query_council_area(), case_id)
            if (!the_case) {
            add_failed_mess("Unable to find the id of the case.\n")
            return 0


    def note_case_desc(self, desc: str, nomic_case: Any) -> None:
            if (!desc) {
            write("Aborted.\n")


    def close_case_bit(self, nomic_case: Any, type: str, data: Any) -> None:
            write("Please add in your closing summary.\n")
            this_player()->do_edit("", "close_case_desc", self, 0,
            [the_case, type, data])


    def do_close_case(self, case_id: int, type: str) -> int:
            class nomic_case the_case
            the_case = NOMIC_HANDLER.query_open_case(query_council_area(), case_id)
            if (!the_case) {
            add_failed_mess("Cannot find the case.\n")
            return 0


    def close_case_desc(self, desc: str, extra: Any) -> None:
            class nomic_case the_case
            string type
            mixed data
            if (!desc) {
            write("Aborted.\n")
            return


    def do_appeal_case(self, case_id: int) -> int:
            class nomic_case the_case
            the_case = NOMIC_HANDLER.query_recently_closed_case(query_council_area(),
            case_id)
            if (!the_case) {
            add_failed_mess("Cannot find the case.\n")
            return 0


    def appeal_case_desc(self, desc: str, case_id: int) -> None:
            class nomic_case the_case
            if (!desc) {
            write("Aborted.\n")
            return


    def appeal_case_desc_confirm(self, response: str, case_id: int, desc: str) -> None:
            class nomic_case the_case
            string* people
            response = lower_case(response)
            if (!strlen(response) || response[0] != 'y') {
            write("Aborting the closing of the note.\n")
            return


    def do_player_status(self, person: str) -> int:
            int* cases
            class nomic_case the_case
            int id
            int found
            int *open_defendant
            int *open_opener
            int *open_appealed
            int *closed_defendant
            int *closed_opener
            int *closed_closed
            string ret
            string bing
            person = lower_case(person)
            cases = NOMIC_HANDLER.query_open_cases(query_council_area())
            if (!sizeof(cases)) {
            add_failed_mess("There are no open cases.\n")
            return 0


    def init(self, ) -> None:
            add_command("list", "", (: do_list_open_cases() :))
            add_command("list", "[case] <number>", (: do_list_case($4[0]) :))
            add_command("list", "closed", (: do_list_closed_cases() :))
            add_command("list", "{punishments|results}", (: do_list_punishments :))
            add_command("list", "{punishment|punishments|results} <string'type'>", (: do_list_punishments_desc($4[1]) :))
            add_command("list", "closed [case] <number>", (: do_list_closed_case($4[0]) :))
            add_command("case", "add person <string'person'> to <number'case id'>",
            (: do_add_person($4[1], $4[0]) :))
            add_command("case", "remove person <string'person'> from <number'case id'>",
            (: do_remove_person($4[1], $4[0]) :))
            add_command("case", "[add] note <number'case id'>", (: do_add_note($4[0]) :))
            add_command("case", "open [with] <string'people'> about <string'short descripion'>",
            (: do_open_case($4[0], $4[1]) :))
            add_command("case", "close <number'case id'> result <string'result'>",
            (: do_close_case($4[0], $4[1]) :))
            add_command("case", "appeal <number'case id'>",
            (: do_appeal_case($4[0]) :))
            add_command("status", "[of] <string'player'>",
            (: do_player_status($4[0]) :))



class Council_cases(MudObject):

    _types = '([ ])'
