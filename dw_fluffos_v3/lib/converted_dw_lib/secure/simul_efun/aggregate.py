# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/aggregate.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def array_to_string(self, args: Any) -> str:
            int i
            args = copy(args)
            for ( i = sizeof( args ) - 1; i > -1; i-- ) {
            if ( pointerp( args[ i ] ) ) {
            args[ i ] = array_to_string( args[ i ] )
            continue


    def mapping_to_string(self, map: Any) -> str:
            int i
            mixed *args
            if( !mapp( map ) ) {
            return sprintf( "%O", map )


    def alt_move(self, dest: Any, ob: MudObject) -> None:
            if(!ob)
            return
            evaluate(bind((:move_object, dest:), ob))



class Aggregate(MudObject):
