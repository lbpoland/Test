# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/perfume_bottle.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def setup(self, ) -> None:
            set_name( "bottle" )
            set_short( "perfume bottle" )
            add_adjective( "perfume" )
            set_value( 4000 )
            set_weight( 2 )
            squirts = 12


    def set_glass(self, word: str) -> None:
            set_short( word +" perfume bottle" )
            add_adjective( word )
            set_main_plural( word +" perfume bottles" )
            glass = word


    def long(self, word: str, dark: int) -> str:
            string words
            words = "This is a perfume bottle made out of "+ glass +" crystal.  "+
            "It is "
            switch( squirts ) {
            case 0 :
            return words +"empty.\n"
            case 1 .. 3 :
            words += "about a quarter full"
            break
            case 4 .. 6 :
            words += "about half full"
            break
            case 7 .. 9 :
            words += "about three-quarters full"
            break
            default :
            words += "almost full"


    def init(self, ) -> None:
            this_player()->add_command( "spray", self, "<direct:object> at <indirect:object>" )


    def do_spray(self, things: MudObject) -> int:
            if ( query_wielded() != this_player() ) {
            this_player()->add_failed_mess( self, "You must be holding "+
            "$D to use it.\n", [}) )
            return 0


    def init_dynamic_arg(self, map: Any) -> None:
            if ( map[ "::" ] )
            ::init_dynamic_arg( map[ "::" ] )
            squirts = map[ "squirts" ]


    def init_static_arg(self, map: Any) -> None:
            if ( map[ "::" ] )
            ::init_static_arg( map[ "::" ] )
            if ( map[ "glass" ] )
            set_glass( map[ "glass" ] )
            if ( map[ "scent" ] )
            scent = map[ "scent" ]
            if ( map[ "scent_plural" ] )
            scent_plural = map[ "scent_plural" ]


    def dest_me(self, ) -> None:
            holdable::dest_me()
            object::dest_me()



class Perfume_bottle(MudObject):
