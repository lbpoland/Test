# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/ptest_ers.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def main_menu(self, cmd: str, name: str, reason: str) -> int:
            string str
            switch ( cmd[ 0 ] ) {
            case 'L' :
            case 'l' :
            str = PLAYTESTER_HAND.query_show_list()
            str += "\n\nSee: 'ptesters H' for help.\n"
            this_player()->more_string(str, "Playtester")
            return 1
            case 'A' :
            case 'a' :
            if ( !name ) {
            return 0



class Ptest_ers(MudObject):
