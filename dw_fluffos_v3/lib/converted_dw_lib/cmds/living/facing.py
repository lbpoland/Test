# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/facing.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, indirect_obs: MudObject) -> int:
            mapping details
            object *oblist
            string *show, dir
            if ( !check_reference_point( environment( this_player() ) ) ) {
            add_failed_mess( "You can't make out a point of reference "
            "to use to determine which way you're facing!\n" )
            return 0


    def find_direction(self, who: MudObject) -> str:
            int facing
            mapping directions
            facing = who.query_facing()[ 0 ]
            directions = filter( ABS_FACING, (: $2 == $(facing) :) )
            if ( !sizeof( directions ) )
            return "north"
            return keys( directions )[ 0 ]


    def check_reference_point(self, where: MudObject) -> int:
            string *relatives
            relatives = map( where.query_direc(),
            (: $(where)->query_relative( $1 ) :) )
            return relatives .index( 0) if  0 in relatives  else -1 > -1



class Facing(MudObject):
