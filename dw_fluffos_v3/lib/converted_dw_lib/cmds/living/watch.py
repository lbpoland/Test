# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/watch.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> Any:
            if ( this_player()->query_blinded() ) {
            add_failed_mess( "How can you watch anything?  You're blind.\n" )
            return 0


    def stop_watching(self, ) -> int:
            int *enums, id
            enums = this_player()->effects_matching( "mind.alertness" )
            if ( sizeof( enums ) ) {
            foreach( id in enums ) {
            this_player()->delete_effect( id )



class Watch(MudObject):
