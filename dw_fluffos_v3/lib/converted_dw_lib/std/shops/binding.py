# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/binding.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._cost_per_book = 4000
            self._cost_per_page = 400


    def init(self, ) -> None:
            add_command("bind", "<object:indirect:me'pages'> into book")


    def check_for_magic_writing(self, ob: MudObject) -> int:
            mixed *stuff
            int i
            stuff = ob.query_read_mess()
            for (i = 0; i < sizeof(stuff); i++) {
            if (LANGUAGE_HAND.query_language_magic(stuff[i][READ_LANG])) {
            return 1


    def do_bind(self, obs: MudObject) -> int:
            object *magic
            object *paper
            object *fail
            object ob
            object book
            string place
            int cost
            foreach (ob in obs) {
            if (ob.query_paper()) {
            if (check_for_magic_writing(ob)) {
            magic += [ob]
            } else {
            paper += [ob]



class Binding(MudObject):

    _cost_per_book = 4000

    _cost_per_page = 400
