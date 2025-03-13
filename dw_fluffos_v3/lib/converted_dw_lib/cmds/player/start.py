# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/start.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def clear_starts(self, ) -> int:
            write( "Clearing your list of starting positions...\n" )
            this_player()->reset_starts()
            return 1


    def list_starts(self, ) -> int:
            int z, i
            string *starts
            starts = this_player()->query_starts()
            z = ( sizeof( starts ) - 2 ) / 2
            if ( z == -1 ) {
            write( "Your starting position is " +
            this_player()->query_start_pos()->the_short() + ".\n")
            return 1


    def set_start(self, num: int) -> int:
            string *starts
            int z
            starts = this_player()->query_starts()
            z = ( sizeof( starts ) - 2 ) / 2
            if (sizeof(starts) < 2) {
            add_failed_mess("You only have one starting location.\n")
            return 0



class Start(MudObject):
