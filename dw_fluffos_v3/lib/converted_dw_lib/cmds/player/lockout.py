# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/lockout.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def get_pw(self, pass: str, player: MudObject) -> int:
            int tim
            if (!PLAYER_HANDLER.test_password(player->query_name(), pass)) {
            write("\nSorry, incorrect password.\n")
            return 0


    def confirm(self, yesno: str, player: MudObject) -> int:
            int tim
            string reason
            string* alts
            string name
            if (yesno[0] != 'y') {
            write("Ok, cancelling lockout...\n")
            write("Lockout cancelled.\n")
            return 1



class Lockout(MudObject):
