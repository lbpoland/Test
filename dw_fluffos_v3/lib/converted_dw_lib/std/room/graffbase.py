# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/graffbase.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init(self, ) -> None:
            this_player()->add_command( "scrawl", self, "with charcoal on wall")
            this_player()->add_command( "scrawl", self, "on wall with charcoal")


    def do_scrawl(self, things: MudObject) -> int:
            string language
            if ( !ETP.query_property( GRAFFITI) ) {
            this_player()->add_failed_mess( self, "You can't scrawl on "+
            "this wall.\n")
            return 0


    def begin_writing(self, writer: MudObject) -> None:
            if ( !writer ) {
            writing_on = 0
            return


    def end_writing(self, words: str) -> None:
            string language
            string extra
            if ( !words || ( words == "" ) ) {
            write( "You don't scrawl anything on "+
            "the wall.\n")
            say( (string)this_player()->the_short() +" doesn't "+
            "scrawl anything after all.\n" )
            writing_on = 0
            return



class Graffbase(MudObject):
