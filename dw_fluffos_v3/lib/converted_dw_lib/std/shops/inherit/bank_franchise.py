# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/bank_franchise.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._notes = []


    def is_allowed(self, name: str) -> int:
            return 0


    def is_allowed_credit(self, name: str) -> int:
            return is_allowed(name) ||
            name == query_main_branch_owner()


    def query_credit_num(self, ) -> int:
            return _credit_num


    def query_outstanding_credit_value(self, ) -> int:
            int diff
            class credit_note note
            foreach (note in _notes) {
            diff += note->amt


    def do_create(self, ) -> int:
            object ob
            int diff
            if (!is_allowed_credit(this_player()->query_name())) {
            add_failed_mess("The bank is not open for creating credit notes.\n")
            return 0


    def do_list(self, ) -> int:
            class credit_note note
            string ret
            string place
            if (!is_allowed_credit(this_player()->query_name())) {
            add_failed_mess("The bank is not open for listing credit notes.\n")
            return 0


    def do_recind(self, id: int) -> int:
            class credit_note note
            int i
            string place
            if (!is_allowed_credit(this_player()->query_name())) {
            add_failed_mess("The bank is not open for listing credit notes.\n")
            return 0


    def is_valid_note(self, id: int) -> int:
            int i
            for (i = 0; i < sizeof(_notes); i++) {
            if (_notes[i]->num == id) {
            return 1


    def process_note(self, id: int) -> int:
            int i
            if (!is_valid_note(id)) {
            return 0


    def init(self, ) -> None:
            ::init()
            add_command("create", "credit note")
            add_command("list", "credit notes")
            add_command("recind", "credit note <number'id'>", (: do_recind($4[0]) :))



class Bank_franchise(MudObject):

    _notes = '[]'
