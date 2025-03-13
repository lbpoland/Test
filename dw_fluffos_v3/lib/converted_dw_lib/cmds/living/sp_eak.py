# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/sp_eak.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, which: str) -> int:
            {
            string *langs
            string skill
            int i
            mapping skills
            skills = TP.query_skills()
            if (!which) {
            langs = LANGUAGE_HAND.query_languages()
            for (i = 0; i < sizeof(langs); i++) {
            if (TP->
            query_skill(LANGUAGE_HAND->
            query_language_spoken_skill(langs[i])) > 1
            || TP->query_skill(LANGUAGE_HAND->
            query_language_written_skill(langs[i])) > 1) {
            } else {
            langs = langs[0..i - 1] + langs[i + 1..]
            i--



class Sp_eak(MudObject):
