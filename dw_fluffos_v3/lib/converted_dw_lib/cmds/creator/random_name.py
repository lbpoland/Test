# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/random_name.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.lang_list = implode(RANDOM_NAME_GENERATOR->query_languages() +


    def cmd(self, pattern: str, my_lang: str) -> Any:
            string *langs
            int i
            if (pattern == "") {
            write("Generating one word from each language.  To generate more "
            "words in a particular language, specify the language on the "
            "command line.\n")
            langs = (string *)RANDOM_NAME_GENERATOR.query_languages() +
            RANDOM_NAME_GENERATOR.query_test_languages()
            for (i=0;i<sizeof(langs);i++) {
            write(capitalize(langs[i])+": "+
            (string)RANDOM_NAME_GENERATOR.random_name(langs[i])+"\n")



class Random_name(MudObject):

    lang_list = 'implode(RANDOM_NAME_GENERATOR->query_languages() +'
