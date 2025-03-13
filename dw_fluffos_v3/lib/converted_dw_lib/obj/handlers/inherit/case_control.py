# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/inherit/case_control.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._open_cases = ([ ])
            self._closed_cases = ([ ])
            self._recently_closed_cases = ([ ])
            self._next_case_id = 1
            self._next_note_id = 1


    def create_area(self, area: str) -> None:
            if (_open_cases[area]) {
            return


    def query_open_cases(self, area: str) -> List[int]:
            return _open_cases[area]


    def query_closed_cases(self, area: str) -> List[int]:
            return _closed_cases[area]


    def query_recently_closed_cases(self, area: str) -> List[int]:
            return _recently_closed_cases[area]


    def query_case_file_name(self, id: int) -> str:
            return NOMIC_CASE_SAVE + sprintf("cases/%02d/%d_case", id % 20, id)


    def query_next_case_id(self, ) -> int:
            int next
            do {
            next = _next_case_id++
            } while (sizeof(stat(query_case_file_name(next))))
            return next


    def query_note_file_name(self, id: int) -> str:
            return NOMIC_CASE_SAVE + sprintf("notes/%02d/%d_note", id % 20, id)


    def query_next_note_id(self, ) -> int:
            int next
            do {
            next = _next_note_id++
            } while (sizeof(stat(query_note_file_name(next))))
            return next


    def query_event_name(self, type: int) -> str:
            switch (type) {
            case NOMIC_CASE_EVENT_CLOSE :
            return "closed case"
            case NOMIC_CASE_EVENT_APPEAL :
            return "appealed case"
            case NOMIC_CASE_EVENT_ADD_PERSON :
            return "add person"
            case NOMIC_CASE_EVENT_REMOVE_PERSON :
            return "remove person"
            default :
            return "unknown"


    def add_new_case(self, area: str, opener: str, short: str, people: Any) -> int:
            int case_id
            if (!_open_cases[area]) {
            return 0


    def appeal_case(self, area: str, id: int, appealer: str, reason: str) -> int:
            class nomic_case the_case
            class nomic_case_event event
            the_case = query_recently_closed_case(area, id)
            if (!the_case || !stringp(reason)) {
            return 0


    def add_note_to_case(self, area: str, id: int, person: str, text: str) -> int:
            class nomic_case the_case
            int note_id
            the_case = query_open_case(area, id)
            if (!the_case) {
            return 0


    def update_recently_closed_cases(self, ) -> None:
            string area
            int* stuff
            int id
            class nomic_case the_case
            class nomic_case_event event
            int last_close
            foreach (area, stuff in _recently_closed_cases) {
            foreach (id in stuff) {
            the_case = query_recently_closed_case(area, id)
            last_close = 0
            foreach (event in the_case->events) {
            if (event->type == NOMIC_CASE_EVENT_CLOSE) {
            last_close = event->event_time



class Case_control(MudObject):

    _open_cases = '([ ])'

    _closed_cases = '([ ])'

    _recently_closed_cases = '([ ])'

    _next_case_id = 1

    _next_note_id = 1
