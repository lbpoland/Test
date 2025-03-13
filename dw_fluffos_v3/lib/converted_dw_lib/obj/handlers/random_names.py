# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/random_names.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.rules = ([ ])
            self._test_rules = []
            self._test_rules = []


    def open_file(self, f: str) -> None:
            string str, *bits, *stuff, lang
            int i
            bits = explode(f, ".")
            if (sizeof(bits) > 1) {
            lang = implode(bits[0..sizeof(bits)-2], ".")
            } else {
            lang = f


    def random_name(self, lang: str) -> str:
            string word = "W", *bing
            int some_caps = 1, i
            do {
            some_caps = 0
            for (i = 0; i < strlen(word); i++)
            if (word[i] >= 'A' && word[i] <= 'Z') {
            bing = explode(rules[lang][word[i..i]], " ") - [""]
            word = word[0..i-1] + bing[random(sizeof(bing))] + word[i+1..]
            some_caps = 1


    def add_test_language(self, lang: str) -> None:
            _test_rules += [lang]
            save_me()


    def remove_test_language(self, lang: str) -> None:
            _test_rules -= [lang]
            save_me()


    def unique_name(self, lang: str) -> str:
            string str
            int ok
            do {
            ok = 1
            str = random_name(lang)
            if (strlen(str) < 2 || strlen(str) > 11)
            ok = 0
            if (ok && PLAYER_HANDLER.test_user(str))
            ok = 0
            if (ok && !PLAYER_HANDLER.test_valid(str))
            ok = 0
            if (ok && find_living(str))
            ok = 0
            } while (!ok)
            return str


    def dest_me(self, ) -> None:
            destruct(self)



class Random_names(MudObject):

    rules = '([ ])'

    _test_rules = '[]'
