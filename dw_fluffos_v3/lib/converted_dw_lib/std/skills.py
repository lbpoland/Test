# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/skills.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._skills = STD_SKILLS
            self._skill_tree = ([ ])
            self._immediate_children = ([ ])
            self._not_allowed_to_teach = ([ ])
            self._only_show_if_non_zero = ([ ])
            self._no_bonus = ([ ])
            self.lang_tree = []
            self.languages = LANGUAGE_HAND->query_languages()
            self.for (i = 0;i<sizeof(languages);i++) {
            self.rabbit = []
            self.rabbit + = ['SPOKEN_SKILL', '0', '0', '({ })']


    def __init__(self):
            self._skills = STD_SKILLS
            self._skill_tree = ([ ])
            self._immediate_children = ([ ])
            self._not_allowed_to_teach = ([ ])
            self._only_show_if_non_zero = ([ ])
            self._no_bonus = ([ ])
            self.lang_tree = []
            self.languages = LANGUAGE_HAND->query_languages()
            self.for (i = 0;i<sizeof(languages);i++) {
            self.rabbit = []
            self.rabbit + = ['SPOKEN_SKILL', '0', '0', '({ })']
            if (LANGUAGE_HAND.query_language_written(languages[i]) ||
            LANGUAGE_HAND.query_language_magic(languages[i])) {
            rabbit += [WRITTEN_SKILL, 0, 0, [})]


    def query_skill_stat(self, skill: str) -> str:
            int i
            string *bit, s
            bit = explode(skill, ".")
            i = sizeof(bit)
            while (i >= 0) {
            s = implode(bit[0..i], ".")
            if (_stat_bonus[s])
            return _stat_bonus[s][SKILL_BONUS]
            else
            i--


    def query_skill_cost(self, skill: str) -> int:
            if (_reg_skills[skill]) {
            return _reg_skills[skill][1]


    def query_skill(self, bits: str) -> str:
            mixed *arr
            int i
            string path, s1
            if( !bits || !sizeof(bits) ) {
            return 0


    def query_only_leaf(self, str: str) -> int:
            string *bits
            bits = explode(str, ".")
            return _only_leaf[bits[0]]


    def query_allowed_to_teach(self, str: str) -> int:
            return !_not_allowed_to_teach[str]


    def query_only_show_if_non_zero(self, str: str) -> int:
            return _only_show_if_non_zero[str]


    def query_no_bonus(self, str: str) -> int:
            return _no_bonus[str] || _ignore_bits[str]


    def is_skill_ignored(self, skill: str) -> int:
            return _ignore_bits[skill]


    def query_skill_depth(self, skill: Any) -> int:
            int depth
            int i
            depth = 0
            for (i = 0; i < sizeof(skill) - 1; i++) {
            if (!is_skill_ignored(implode(skill[0..i], "."))) {
            depth++



class Skills(MudObject):

    _skills = 'STD_SKILLS'

    _skill_tree = '([ ])'

    _immediate_children = '([ ])'

    _not_allowed_to_teach = '([ ])'

    _only_show_if_non_zero = '([ ])'

    _no_bonus = '([ ])'

    lang_tree = '[]'

    languages = 'LANGUAGE_HAND->query_languages()'

    for (i = '0;i<sizeof(languages);i++) {'

    rabbit = '[]'

    rabbit + = "['SPOKEN_SKILL', '0', '0', '({ })']"
