# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/caterpillar.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "caterpillar" )
            set_long( "The elongated wormlike larva of a butterfly or moth.\n" )
            set_height( 5 )
            set_weight( 2 )
            set_desc( "a caterpillar, crawling along the ground" )
            set_stats( [-6, -6, -6, -6, -6] )


    def player_heart_beat(self, word: str, eater: MudObject) -> None:
            int i, time
            object flowers, *things
            if( !environment( eater ) ) return
            if( eater.query_property( "eating" ) ) return
            things = all_inventory( environment( eater ) ) - [eater]
            if( !sizeof( things ) ) return
            for( i = 0; i < sizeof( things ); i++ ) {
            if( !(int)things[ i ]->id( "flowers" ) ) {
            things -= [things[ i ]]
            i--
            } else {
            if( things[ i ]->query_property( "being eaten" ) ) {
            things -= [things[ i ]]
            i--


    def done_eating(self, eater: MudObject, flowers: MudObject) -> None:
            if( !eater ) return
            eater.remove_property( "eating" )
            if( !environment( eater ) ) return
            if( !flowers ) return
            if( all_inventory( environment( eater .index( flowers) if  flowers in all_inventory( environment( eater  else -1 ) ) == -1 )
            return
            tell_room( environment( eater ), "The " + (string)eater.query_short() +
            " finishes the " + (string)flowers.query_short() + " and burps " +
            "contentedly.\n" )
            flowers.dest_me()



class Caterpillar(MudObject):
