# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/honours.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._honours = ([ ])
            self._titles = []


    def __init__(self):
            self._honours = ([ ])
            self._titles = []
            void inform_of_honour_change(string type, string person,
            string reason, string changed_by) {


    def set_controlled_titles(self, title: Any) -> None:
            _titles = title


    def add_to_honour_roll(self, person: str, reason: str, added_by: str) -> None:
            string title
            if (_honours[person]) {
            return


    def remove_from_honour_roll(self, person: str) -> None:
            string title
            if (!_honours[person]) {
            return


    def is_on_honour_roll(self, person: str) -> int:
            return classp(_honours[person])


    def do_list_honour(self, ) -> int:
            string person
            class honour roll
            string ret
            string* people
            if (!_honours) {
            _honours = ([ ])


    def do_honour_add(self, person: str) -> int:
            if (!is_allowed_to_change(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add people to the honour "
            "roll.\n")
            return 0


    def end_honour_add(self, reason: str, person: str, bing: str) -> None:
            if (reason == "" || !reason) {
            write("Aborting.\n")
            return


    def honour_roll_confirm(self, response: str, person: str, reason: str) -> None:
            response = lower_case(response)
            if (!strlen(response) || response[0] != 'y') {
            write("Aborting.\n")
            return


    def do_honour_remove(self, person: str, reason: str) -> int:
            if (!is_allowed_to_change(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add people to the honour "
            "roll.\n")
            return 0


    def readd_all_titles(self, ) -> None:
            string person
            class honour roll
            foreach (person, roll in _honours) {
            foreach (string title in _titles) {
            PLAYER_TITLE_HANDLER.add_title_to_player(person, title)


    def init(self, ) -> None:
            if (!sizeof(_titles)) {
            return 0



class Honours(MudObject):

    _honours = '([ ])'

    _titles = '[]'
