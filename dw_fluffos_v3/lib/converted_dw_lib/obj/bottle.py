# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/bottle.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def make_bottle(self, word: str, number: int) -> None:
            float mass
            string adjective, noun
            glass = word
            set_max_volume(number*4)
            mass = number / 100.0
            if ( !mass ) mass = 1
            set_leak_rate( 0 )
            set_value( to_int(mass * 25 + random( mass * 10 )) )
            set_weight( to_int(mass + random( mass * 10 ) / 10 ))
            set_max_weight( to_int(mass * 2 ))
            add_property( "fragile", to_int(mass * 20 + random( mass * 5 )) )
            switch( number ) {
            case 0..PHIAL:
            adjective = "small"
            noun = "phial"
            set_length( 2 )
            set_width( 1 )
            break
            case PHIAL+1..BOTTLE:
            adjective = "medium sized"
            noun = "bottle"
            set_length( 12 )
            set_width( 6 )
            break
            case BOTTLE+1..QUIRM:
            adjective = "large"
            noun = "Quirm"
            set_length( 24 )
            set_width( 12 )
            break
            case QUIRM+1..DEMIJOHN:
            adjective = "very large"
            noun = "demijohn"
            set_length( 48 )
            set_width( 24 )
            break
            default:
            adjective = "huge"
            noun = "tank"
            set_length( 88 )
            set_width( 48 )


    def query_number(self, {: Any) -> int:
            mixed *stats() {
            return ::stats() + ({
            ["glass", glass,],
            })


    def init_static_arg(self, map: Any) -> None:
            if ( map["::"] )
            ::init_static_arg( map["::"] )
            if ( !undefinedp( map["glass"] ) )
            glass = map["glass"]


    def query_static_auto_load(self, ) -> Any:
            if ( explode( file_name( self ), "#" )[ 0 ] == "/obj/bottle" )
            return int_query_static_auto_load()
            return ([ ])



class Bottle(MudObject):
