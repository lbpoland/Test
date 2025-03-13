# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/owned_room.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._allowed = []


    def init(self, ) -> None:
            if (this_player()->query_name() == query_owner()) {
            add_command("room",
            "allow <string'person'>",
            (: do_allow($4[0]) :))
            add_command("room",
            "disallow <string'person'>",
            (: do_disallow($4[0]) :))
            add_command("room",
            "throwout <indirect:living'person'>",
            (: do_throwout($4[0]) :))


    def set_save_file(self, name: str) -> None:
            _save_file = name


    def query_save_file(self, ) -> str:
            return _save_file


    def query_owner(self, ) -> str:
            return _owner


    def set_owner(self, owner: str) -> None:
            _owner = owner


    def set_front_door(self, exit: str) -> None:
            _front_door = exit


    def query_front_door(self, ) -> str:
            return _front_door


    def is_allowed_in(self, person: str) -> int:
            person = lower_case(person)
            if (person != query_owner()) {
            if (call_door(_front_door,
            "query_locked")) {
            if (_allowed.index(person) if person in _allowed else -1 != -1) {
            return 0


    def is_allowed(self, person: str) -> int:
            if (person == query_owner() ||
            query_allowed(.index(person) if person in query_allowed( else -1) != -1) {
            return 1


    def load_room(self, ) -> None:
            if (_save_file) {
            restore_object(_save_file)
            call_door(_front_door,
            "set_locked",
            1)


    def save_room(self, ) -> None:
            if (_save_file) {
            save_object(_save_file)



class Owned_room(MudObject):

    _allowed = '[]'
