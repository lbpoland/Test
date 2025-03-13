# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/pstat.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, indirect_obs: MudObject) -> int:
            object ob
            mapping prop
            string *sorted, property
            string txt
            txt = "$P$Properties$P$"
            foreach( ob in indirect_obs ) {
            prop = filter( ob.query_properties(), (: $2 :) )
            sorted = sort_array( keys( prop ), 1 )
            foreach( property in sorted ) {
            txt += sprintf( "$I$0,5=(%s): %O$I$0,-5=\n", property, prop[ property ] )



class Pstat(MudObject):
