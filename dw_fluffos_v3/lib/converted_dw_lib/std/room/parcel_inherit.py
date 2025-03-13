# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/parcel_inherit.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def make_shelf(self, short: str, long: str) -> None:
            shelf = clone_object( "/std/surface" )
            shelf.set_name( short )
            shelf.set_long( long )
            shelf.set_max_weight( 10000 )
            shelf.move( self )
            shelf.add_property( "there", "fixed to one wall" )
            shelf.reset_get()


    def init(self, ) -> None:
            ::init()
            this_player()->add_command( "deposit", self,
            "<indirect:object> for <string>",
            (: do_deposit( $1, $4[1] ) :) )
            this_player()->add_command( "collect", self, "",
            (: do_collect() :) )


    def deposit_parcel(self, obs: MudObject, name: str, show_sender: int) -> int:
            if ( obs == 0 || name == 0 ) {
            return 0


    def do_collect(self, ) -> int:
            string this_player_name
            this_player_name = lower_case(this_player()->query_name())
            if( PLAYER_MULTIPLAYER_HANDLER.member_denied_parcel(this_player_name) ) {
            add_failed_mess("You are not allowed to collect things.\n")
            return 0


    def set_shelf(self, ob: MudObject) -> None:
            shelf = ob


    def query_shelf(self, ) -> MudObject:
            return shelf



class Parcel_inherit(MudObject):
