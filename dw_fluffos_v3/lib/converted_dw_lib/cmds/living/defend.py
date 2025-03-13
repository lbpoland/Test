# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/defend.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, things: MudObject) -> Any:
            int i
            object *defendees
            things -= [TP]
            if ( TP.query_property( "dead" ) ) {
            add_failed_mess("You cannot provide much defense as a ghost.\n" )
            return 0


    def show_defenders(self, ) -> int:
            object *defend
            object womble
            defend = this_player()->query_defenders()
            if (sizeof(defend)) {
            write("You are being defended by " + query_multiple_short(defend) +
            ".\n")
            } else {
            write("You are not being defended by anyone.\n")



class Defend(MudObject):
