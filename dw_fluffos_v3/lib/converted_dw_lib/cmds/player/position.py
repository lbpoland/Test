# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/position.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._bad_words = ['teach', 'skill', 'finger', 'lesson', ':)', ';)']
            self."_", "-", " = ", "+", "{", "}", "[", "]",


    def cmd(self, new_pos: str) -> int:
            object player = this_player()
            string word, tmp
            if (!new_pos) {
            write("You are " + player.query_position_short() + ".\n")
            return 1



class Position(MudObject):

    _bad_words = "['teach', 'skill', 'finger', 'lesson', ':)', ';)']"

    "_", "-", " = '", "+", "{", "}", "[", "]",'
