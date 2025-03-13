# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/gob_ack.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            mixed dest
            string tname
            dest = this_player()->query_last_location()
            if(!dest)
            return notify_fail("No stored location.\n")
            if (stringp(dest)) {
            dest = load_object(dest)
            } else if (arrayp(dest) && stringp(dest[0]) && arrayp(dest[1])) {
            dest = TERRAIN_MAP.find_location(dest[0], dest[1])
            } else {
            return notify_fail("I don't understand your stored location.\n")


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()



class Gob_ack(MudObject):
