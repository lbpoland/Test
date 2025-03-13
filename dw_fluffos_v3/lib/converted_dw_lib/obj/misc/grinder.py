# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/grinder.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "grinder" )
            set_short( "food grinder" )
            add_adjective( "food" )
            set_main_plural( "food grinders" )
            set_long( "This is a mechanical contraption to grind food into small "
            "pieces.  There is a funnel-type piece at the top, a crank on one "
            "side and on the other a pipe where the ground food comes out and "
            "is caught in a small tray.\n" )
            set_value( 4000 )
            set_weight( 100 )
            set_max_weight( 100 )


    def init(self, ) -> None:
            this_player()->add_command( "grind", self,
            "<string'object'> in <direct:object'" + query_short() + "'>",
            (: do_grind( $4[0] ) :) )
            add_command( "empty", "<direct:object>" )


    def test_add(self, ob: MudObject, flag: int) -> int:
            object stuff = first_inventory()
            if (stuff) {
            add_failed_mess( "There is already some " + stuff.query_short()
            + " in the grinder.  You'll have to empty it first.\n")
            return 0
            } else return 1


    def do_grind(self, what: str) -> int:
            object *things, thing
            object ground
            object contents
            things = match_objects_for_existence( what, [self,
            this_player()] )
            if( !sizeof( things ) ) {
            add_failed_mess( "You must be holding something or put it in $D in "
            "order to $V it.\n" )
            return -1


    def do_empty(self, dest: MudObject, me: str, him: str, prep: str) -> int:
            object ground = first_inventory( self )
            if( !ground ) {
            add_failed_mess( "There is nothing in $D.\n" )
            return 0



class Grinder(Inventory):
