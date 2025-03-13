# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/plants/inherit/grain.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._max_strip = THRESHOLD


    def init(self, ) -> None:
            ::init()
            TP.add_command( "chew", TO )
            TP.add_command( "strip", TO )


    def set_max_strippable(self, num: int) -> None:
            _max_strip = num


    def query_max_strippable(self, ) -> int:
            return _max_strip


    def do_chew(self, ) -> int:
            int size
            size = query_amount()
            if ( ! size ) {
            add_failed_mess( "You can't chew thin air.\n" )
            return 0


    def do_strip(self, ) -> int:
            int i
            object stripped
            if ( query_amount() > query_max_strippable() ) {
            add_failed_mess( "That's far too much $D for you to strip by hand.  "
            "Perhaps you should look for a tool of some kind.\n" )
            return 0



class Grain(MudObject):

    _max_strip = 'THRESHOLD'
