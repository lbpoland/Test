# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/history.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def substitute_history(self, arg: str) -> str:
            string s1, s2
            if (sscanf(arg, "%s^%s", s1, s2) != 2)
            return arg
            sscanf(s2, "%s^", s2)
            if (hoffset)
            return replace(history[hoffset-1], s1, s2)
            else
            return replace(history[sizeof(history)-1], s1, s2)


    def ignore_from_history(self, str: str) -> None:
            ignore_history = str


    def add_history(self, arg: str) -> None:
            if (ignore_history) {
            if (ignore_history == arg) {
            ignore_history = 0
            return



class History(MudObject):
