# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/mineral.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            this_player()->add_command( "chip", self, "<direct:object> 'with' <indirect:object>" )
            this_player()->add_command( "chip", self, "<direct:object> 'using' <indirect:object>" )
            this_player()->add_command( "smash", self, "<direct:object> 'with' <indirect:object>" )
            this_player()->add_command( "smash", self, "<direct:object> 'using' <indirect:object>" )


    def long(self, str: str, dark: int) -> str:
            string bit1, bit2, ret
            sscanf( ::long( str, dark ), "%s$mineral$%s", bit1, bit2 )
            ret = bit1 + (string)HANDLER.identify_material( mineral, this_player(), 1 )
            + bit2
            return ret


    def query_value(self, ) -> int:
            return ( query_weight() * (int)(PRICE_INDEX)->query_price( mineral,
            DEFAULT_MARKET ) )


    def query_value_in(self, word: str) -> int:
            if ( ( !word || ( word == "" ) ) || ( word == "default" ) )
            word = DEFAULT_MARKET
            return ( query_weight() * (int)(PRICE_INDEX)->query_price( mineral, word ) )


    def do_chip(self, tools: MudObject) -> int:
            object chip
            if ( !check_tool( tools ) )
            return 0
            if ( query_weight() == 1 ) {
            write( "This piece of "+ (string)HANDLER->identify_material( mineral,
            this_player(), 0 ) +" is already a chip.\n" )
            return 0


    def do_smash(self, tools: MudObject) -> int:
            int i, j, largest, number, size
            object debris, remains
            if ( !check_tool( tools ) )
            return 0
            largest = this_player()->query_max_weight()
            if ( largest >= query_weight() )
            largest = query_weight()
            else {
            remains = clone_object( MINERAL )
            remains.make_mineral( mineral, query_weight() - largest )
            remains.move( environment() )


    def check_tool(self, tools: MudObject) -> int:
            string tool
            object *held
            if ( sizeof( tools ) > 1 ) {
            write( "You only need to use one tool at a time.\n" )
            return 0


    def init_static_arg(self, map: Any) -> None:
            if ( map["::"] )
            ::init_static_arg( map["::"] )
            if ( !undefinedp( map["mineral"] ) )
            mineral = map["mineral"]


    def query_static_auto_load(self, ) -> Any:
            if ( file_name( self )[ 0 .. 11 ] == "/std/mineral" )
            return int_query_static_auto_load()
            return ([ ])



class Mineral(MudObject):
