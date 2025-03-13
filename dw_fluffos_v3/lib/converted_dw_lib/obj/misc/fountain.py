# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/fountain.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "fountain" )
            set_short( "fountain" )
            set_long( "This is a fountain.\n" )
            set_max_volume( FOUNTAIN_SIZE )
            set_weight( 100000 )
            set_stuck( 1 )


    def make_water(self, ) -> None:
            object water
            if ( !( query_max_volume() - query_volume() ) ) {
            tell_room( environment(), sprintf( "Some of the %s in %s sloshes over the sides.\n",
            query_multiple_short( all_inventory() ), self.the_short() ) )
            remove_volume( -VOLUME_QUART * random( 4 ) * 2 )



class Fountain(MudObject):
