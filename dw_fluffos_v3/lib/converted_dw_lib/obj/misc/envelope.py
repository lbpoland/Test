# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/envelope.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def make_envelope(self, description: str, size: int) -> None:
            string adjective, noun
            if( size < 2 )
            size = 2
            switch( size ) {
            case 0..SMALL:
            adjective = "small"
            noun = "envelope"
            break
            case SMALL + 1..MEDIUM:
            adjective = "medium sized"
            noun = "envelope"
            break
            case MEDIUM + 1..LARGE:
            adjective = "large"
            noun = "envelope"
            break
            default:
            adjective = "large"
            noun = "packet"
            add_alias("packet")


    def init(self, ) -> None:
            ::init()
            this_player()->add_command( "seal", self,
            "<direct:object:me>" )
            this_player()->add_command( "unseal", self,
            "<direct:object:me>" )


    def long(self, str: str, dark: int) -> str:
            string desc
            switch( status ) {
            case UNSEALED :
            desc = "It has a sticky flap at one end with which you could "
            "probably seal it if you wanted to, though it might be wise to put "
            "something into it first or you're going to feel rather silly.\n"
            break
            case SEALED :
            desc = "The sticky flap seems to have been sealed down.\n"
            break
            case OPENED :
            desc = "It looks like it has been sealed and then opened up.\n"
            break
            default :
            desc = "It is completely broken - you'd better tell a liaison.\n"


    def do_seal(self, ) -> int:
            if( status != UNSEALED ) {
            return notify_fail( self.the_short() + " has already been "
            "sealed.\n" )


    def do_unseal(self, ) -> int:
            if( status != SEALED ) {
            return notify_fail( self.the_short() + " has not been "
            "sealed.\n" )


    def query_envelope_status(self, ) -> int:
            return status


    def init_static_arg(self, map: Any) -> None:
            if( map["::"] )
            ::init_static_arg( map["::"] )
            if( !undefinedp( map["status"] ) )
            status = map["status"]


    def query_static_auto_load(self, ) -> Any:
            if( base_name( self ) + ".c" == __FILE__ )
            return int_query_static_auto_load()
            return ([ ])



class Envelope(MudObject):
