# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/add_a.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def add_a(self, s: str) -> str:
            int i
            if (!stringp(s))
            return 0
            i = 0
            while (s[i] == ' ') i++
            if(s[i..i+1] == "a " || s[i..i+2] == "an ")
            return s
            switch (s[i]) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
            return "an " + s[i..]
            default:
            return "a " + s[i..]


    def vowel(self, i: int) -> int:
            return (i == 'a' || i == 'e' || i == 'i' || i == 'o' || i == 'u' ||
            i == 'A' || i == 'E' || i == 'I' || i == 'O' || i == 'U')



class Add_a(MudObject):
