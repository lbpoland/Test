# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/wand.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def set_weight(self, number: int) -> None:
            weapon::set_weight( number )
            new_weapon( 80 * number )
            add_attack( "prod", 90, [0, 5, weight], "blunt", "blunt", 0 )


    def long(self, word: int, dark: int) -> str:
            return artifact::long( word, dark ) + weapon::long( word, dark )


    def init(self, ) -> None:
            this_player()->add_command( "zap", self, "<direct:object> at <indirect:object>" )
            this_player()->add_command( "zap", self, "<indirect:object> with <direct:object>" )


    def do_zap(self, things: MudObject) -> int:
            int outcome
            if ( query_wielded() != this_player() ) {
            this_player()->add_failed_mess( self, "You must be holding "+
            "$D to $V it.\n", [}) )
            return 0


    def init_dynamic_arg(self, map: Any) -> None:
            if ( map[ "::" ] )
            weapon::init_dynamic_arg( map[ "::" ] )
            if ( map[ "artifact" ] )
            artifact::init_dynamic_arg( map[ "artifact" ] )


    def init_static_arg(self, map: Any) -> None:
            if ( map[ "::" ] )
            weapon::init_static_arg( map[ "::" ] )
            if ( map[ "artifact" ] )
            artifact::init_static_arg( map[ "artifact" ] )



class Wand(MudObject):
