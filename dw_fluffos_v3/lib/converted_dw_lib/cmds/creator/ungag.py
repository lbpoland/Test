# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/ungag.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, victim: MudObject) -> int:
            if( !victim.query_property( "gagged" ) )
            return notify_fail( victim.query_short() +" is not gagged.\n" )
            victim.remove_property("gagged")
            log_file("GAG", ctime(time()) + ": " + this_player()->
            query_short() + " ungagged " + victim.query_short() + ".\n")
            await  victim.send(this_player()->query_short() + " ungags you.\n"
            "%^YELLOW%^Be more careful with what you say "
            "in future.%^RESET%^\n" )
            write( "Okay, ungagged " + victim.query_short() + ".\n" )
            return 1



class Ungag(MudObject):
