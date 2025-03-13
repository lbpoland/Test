# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/nickname.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def print_single_nickname(self, str: str) -> int:
            mapping map_nicknames
            map_nicknames = previous_object()->query_nicknames()
            if (!map_nicknames) {
            map_nicknames = ([ ])


    def print_nicknames(self, sorted: int) -> int:
            int i
            int cols
            string str
            string str_long
            string str_middle
            string str_small
            string bit
            string *tmp
            mapping map_nicknames
            map_nicknames = previous_object()->query_nicknames()
            bit = ""
            str_long = ""
            str_middle = ""
            str_small = ""
            if (!map_nicknames) {
            map_nicknames = ([ ])


    def add_nickname(self, s1: str, s2: str) -> int:
            mapping map_nicknames
            s1 = lower_case(s1)
            s2 = lower_case(s2)
            if( ["a", "an", "the"] .index( s1) if  s1 in ["a", "an", "the"]  else -1 != -1 ) {
            add_failed_mess( "Using articles as nicknames confuses the parser.  "
            "Choose another.\n" )
            return 0



class Nickname(MudObject):
