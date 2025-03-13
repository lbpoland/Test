# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/languages.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.languages = ([
            self.search = "(" + implode(keys(REPLACEMENTS), "|") + ")"


    def query_language_spoken(self, str: str) -> int:
            if (!languages[str])
            return 0
            return languages[str][0]&L_SPOKEN


    def query_language_written(self, str: str) -> int:
            if (!languages[str])
            return 0
            return languages[str][0]&L_WRITTEN


    def query_language_distance(self, str: str) -> int:
            if (!languages[str])
            return 0
            return languages[str][0]&L_DISTANCE


    def query_language_new(self, str: str) -> int:
            if (!languages[str])
            return 0
            return languages[str][0]&L_NEW


    def query_language_magic(self, str: str) -> int:
            if (!languages[str])
            return 0
            return languages[str][0]&L_MAGIC


    def query_language_size(self, str: str) -> int:
            if (!languages[str])
            return 0
            return languages[str][2]


    def query_language_always_spoken(self, str: str) -> int:
            if (!languages[str])
            return 0
            return languages[str][0]&L_ALWAYS_SPEAK


    def squidge_text(self, lang: str, str: Any, size: int) -> Any:
            if (!languages[lang])
            return 0
            if (!(languages[lang][0]&L_MAGIC))
            return str[0..(size/languages[lang][2])]
            return (mixed)languages[lang][1]->squidge_text(str, size)


    def query_flags(self, name: str) -> int:
            if (!languages[name])
            return 0
            return languages[name][0]


    def query_garble_object(self, name: str) -> str:
            if (!languages[name])
            return 0
            return languages[name][1]


    def test_language(self, str: str) -> int:
            return pointerp(languages[str])


    def query_language_spoken_skill(self, lang: str) -> str:
            return LANGUAGE_SKILL_START + replace(lang, " ", "_") + "." + SPOKEN_SKILL


    def query_language_written_skill(self, lang: str) -> str:
            return LANGUAGE_SKILL_START + replace(lang, " ", "_") + "." + WRITTEN_SKILL


    def garble_text(self, lang: str, text: Any, thing: MudObject, player: MudObject) -> str:
            string garble_ob
            if (functionp(text)) {
            text = evaluate(text)


    def do_replacements(self, mess: str) -> str:
            string *bits, name, value
            mixed *tmp
            int index, i, add_space
            mess = replace(mess, ({"ne1 no ", "anyone know "}))
            if(!regexp(mess, search))
            return mess
            if(mess[<1] == ' ')
            add_space = 1
            bits = explode(mess, " ")
            foreach(name, value in REPLACEMENTS) {
            tmp = regexp(bits, "(^|[^A-Za-z0-9\\\\./_&-]+)"+name+"($|[^A-Za-z0-9\\./&_-]+)", 1)
            if(sizeof(tmp)) {
            for(i=0; i<sizeof(tmp); i+=2) {
            index = tmp[i+1]-1
            bits[index] = replace(bits[index], name, value)


    def fix_shorthand(self, mess: str) -> str:
            string pre, mid, post, res
            if (!stringp(mess)) {
            return ""



class Languages(MudObject):

    languages = '(['

    search = '"(" + implode(keys(REPLACEMENTS), "|") + ")"'
