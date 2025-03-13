# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/concentrate.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def concentrate_list(self, ) -> int:
            object conc
            conc = this_player()->query_concentrating()
            if ( !conc ) {
            write("You are not currently concentrating on "
            "any particular opponent.\n" )
            } else {
            write("You are currently concentrating on "+
            conc.the_short() + ".\n")


    def concentrate(self, things: MudObject) -> int:
            if ( sizeof( things ) > 1 ) {
            return notify_fail( "You can only concentrate on one thing at once.\n" )



class Concentrate(MudObject):
