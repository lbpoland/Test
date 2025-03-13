# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/easel.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "easel" )
            set_short( "small easel" )
            add_adjective( "small" )
            set_main_plural( "small easels" )
            set_value( 800 )
            origin = [0, 0]
            lines = [})


    def long(self, word: str, dark: int) -> str:
            int i, max, min, width
            string part
            if ( !sizeof( lines ) )
            return "The easel is blank.\n"
            width = ( (int)this_player()->query_cols() - 2 ) / 2
            min = origin[ 0 ] - width
            max = origin[ 0 ] + width
            if ( min < 0 ) {
            max -= min
            min = 0


    def query_at(self, place: int) -> int:
            if ( !sizeof( lines ) )
            return 32
            if ( ( origin[ 0 ] + place[ 0 ] ) < 0 )
            return 32
            if ( ( origin[ 0 ] + place[ 0 ] ) >= strlen( lines[ 0 ] ) )
            return 32
            if ( ( origin[ 1 ] + place[ 1 ] ) < 0 )
            return 32
            if ( ( origin[ 1 ] + place[ 1 ] ) >= sizeof( lines ) )
            return 32
            return lines[ origin[ 1 ] + place[ 1 ] ][ origin[ 0 ] + place[ 0 ] ]


    def add_shape(self, start: int, pieces: str) -> None:
            int i, number, max, width
            string gap, front, back
            for ( i = 0; i < sizeof( pieces ); i++ )
            if ( strlen( pieces[ i ] ) > max )
            max = strlen( pieces[ i ] )
            if ( sizeof( lines ) )
            width = strlen( lines[ 0 ] )
            else
            lines = [""]
            if ( ( origin[ 0 ] + start[ 0 ] ) < 0 ) {
            gap = ""
            for ( i = origin[ 0 ] + start[ 0 ]; i < 0; i++ )
            gap += " "
            for ( i = 0; i < sizeof( lines ); i++ )
            lines[ i ] = gap + lines[ i ]
            origin[ 0 ] = -start[ 0 ]


    def make_map(self, locations: Any, connections: Any) -> None:
            int i, j, k, x, y, *sizes
            string *places
            mapping centres
            sizes = [})
            places = [})
            centres = ([ ])
            for ( i = 0; i < sizeof( locations ); i+= 2 ) {
            sizes += [locations[ i + 1 ]]
            places += [locations[ i ]]
            reset_eval_cost()



class Easel(MudObject):
