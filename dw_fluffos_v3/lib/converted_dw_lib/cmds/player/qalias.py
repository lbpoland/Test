# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/qalias.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> int:
            {
            string *aliases, alias_mess, message
            int cols
            aliases = keys( this_player()->query_aliases() )
            if( !sizeof( aliases ) )
            {
            await  this_player().send("You have no aliases.\n" )
            return 1



class Qalias(MudObject):
