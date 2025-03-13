# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/rot13.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> int:
            printf("You rot: \"%s\".\n", rot13(str))
            return 1


    def rot13(self, str: str) -> str:
            int i
            for(i = 0; i < sizeof(str); i++) {
            if(str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = ((13 + str[i] - 'A') % 26) + 'A'
            } else if(str[i] >= 'a' && str[i] <= 'z') {
            str[i] = ((13 + str[i] - 'a') % 26) + 'a'
            } else if(str[i] >= '0' && str[i] <= '9') {
            str[i] = ((5 + str[i] - '0') % 10) + '0'



class Rot13(MudObject):
