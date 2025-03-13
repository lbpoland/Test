# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/protect.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, things: MudObject) -> Any:
            int i
            object *protectees
            things -= [TP]
            if ( !sizeof( things ) ) {
            add_failed_mess("You cannot protect yourself!\n")
            return 0


    def show_protectors(self, ) -> int:
            object *protect
            object womble
            protect = this_player()->query_protectors()
            if (sizeof(protect)) {
            write("You are being protected by " + query_multiple_short(protect) +
            ".\n")
            } else {
            write("You are not being protected by anyone.\n")



class Protect(MudObject):
