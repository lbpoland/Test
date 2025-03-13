# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/title_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def save_me(self, ) -> None:
            class blob {
            string ob
            string func


    def __init__(self):
            self._pending = ([ ])
            self._titles = ([ ])
            self._allowed_multiple = ['very reverend', 'mostly reverend']


    def is_allowed_multiple_title(self, title: str) -> int:
            return _allowed_multiple.index(lower_case(title)) if lower_case(title) in _allowed_multiple else -1 != -1


    def add_title_to_player(self, person: str, title: str) -> None:
            object ob
            ob = find_player(person)
            if (ob) {
            ob.add_player_title(title)
            return


    def add_controlled_title(self, title: str, ob: str, func: str) -> None:
            class blob fluff
            fluff = new(class blob)
            fluff->ob = ob
            fluff->func = func
            _titles[title] = fluff
            save_me()


    def check_player(self, player: MudObject) -> None:
            string* titles
            string title
            if (!player) {
            return


    def login_handler_call(self, person: str, type: str) -> None:
            if (type == LOGIN) {
            asyncio.create_task(self.(: check_player(find_player($1)) :), 2, person)


    def save_me(self, ) -> None:
            unguarded((: save_object(SAVE_FILE) :))


    def load_me(self, ) -> None:
            unguarded((: restore_object(SAVE_FILE, 1) :))



class Title_handler(MudObject):

    _pending = '([ ])'

    _titles = '([ ])'

    _allowed_multiple = "['very reverend', 'mostly reverend']"
