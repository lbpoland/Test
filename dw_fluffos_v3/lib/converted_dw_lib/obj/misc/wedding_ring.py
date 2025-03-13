# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/wedding_ring.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "ring" )
            set_short( "wedding ring" )
            add_adjective( "wedding" )
            set_long( "This is a wedding ring crafted from the purest gold from the "+
            "mines of Rimward Klatch.\n" )
            set_main_plural( "wedding rings" )
            set_type( "ring" )
            add_property( "shop type", "jewellers" )
            add_property( "no recycling", 1 )
            set_weight( 1 )
            setup_armour( 1000 )
            set_percentage( 100 )
            set_damage_chance( 0 )
            owner = giver = "nobody"
            set_wear_remove_func( file_name( self ), "wear_remove" )


    def do_inscription(self, ) -> None:
            string language
            object player
            player = find_player( giver )
            if( !player ) {
            player = find_player( owner )


    def set_owner(self, word: str) -> None:
            owner = lower_case( word )
            do_inscription()


    def set_giver(self, word: str) -> None:
            giver = lower_case( word )
            do_inscription()


    def wear_remove(self, wear: int) -> None:
            if( environment() != this_player() )
            return
            if ( living( environment() )  &&  wear ) {
            if ( (string)this_player()->query_name() != owner )
            write( "The ring feels uncomfortable on your finger.\n" )
            else
            write( "You are warmed anew by "+ capitalize( giver ) +"'s love.\n" )


    def init_dynamic_arg(self, args: Any) -> None:
            if ( args[ "::" ] )
            ::init_dynamic_arg( args[ "::" ] )
            if ( args[ "owner" ] )
            owner = lower_case( args[ "owner" ] )
            if ( args[ "giver" ] )
            giver = lower_case( args[ "giver" ] )



class Wedding_ring(MudObject):
