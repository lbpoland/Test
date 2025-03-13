# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/languages/wommon.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def long(self, ) -> str:
            return
            "International womens day language.\n"


    def filter_string(self, str: str) -> str:
            return replace(" "+str,
            [" he ", " they ",
            " He ", " They ",
            " HE ", " THEY ",
            " his ", " theirs ",
            " His ", " Theirs ",
            " HIs ", " THEIrs ",
            " HIS ", " THEIRS ",
            " him ", " them ",
            " Him ", " Them ",
            " HIm ", " THem ",
            " HIM ", " THEM ",
            "man", "person",
            "Man", "Person",
            "MAn", "PERson",
            "MAN", "PERSON",])[1..10000]


    def garble_tell(self, start: str, mess: str) -> Any:
            return [start, filter_string(mess)]


    def garble_shout(self, start: str, mess: str) -> Any:
            return [start, filter_string(mess)]


    def garble_say(self, start: str, mess: str) -> Any:
            return [start, filter_string(mess)]


    def garble_text(self, str: str, ob: MudObject) -> Any:
            return filter_string(str)



class Wommon(MudObject):
