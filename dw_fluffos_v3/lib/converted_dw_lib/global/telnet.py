# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/telnet.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def telnet_suboption(self, str: str) -> None:
            switch (str[0]) {
            case TELOPT_TTYPE :
            if (str[1] != TELQUAL_IS)
            return
            check_terminal_type(str[2..1000])
            break


    def player_connected(self, ) -> None:
            printf("%c%c%c", IAC, DO, TELOPT_TTYPE)
            printf("%c%c%c%c%c%c", IAC, SB, TELOPT_TTYPE, TELQUAL_SEND, IAC, SE)


    def check_terminal_type(self, type: str) -> None:
            if (last_term == type) {
            if (!got_terminal)
            self.set_network_terminal_type(0)
            return



class Telnet(MudObject):
