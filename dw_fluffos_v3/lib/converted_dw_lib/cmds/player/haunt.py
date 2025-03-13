# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/haunt.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def ooo(self, ) -> str:
            return implode( allocate( 3 + random( 15 ),
            (: ["O", "o"][ random( 2 ) ] :) ), "" )


    def haunt_player(self, victims: MudObject) -> int:
            victims = filter( victims, (: !sizeof( $1.query_ignoring( [this_player()] ) ) :) )
            victims = filter( victims, (: !$1->check_earmuffs( HAUNT_EARMUFF,
            $(this_player()) ) :) )
            victims = filter( victims,
            (: interactive( $1 ) || ( $1.query_property( "npc" ) &&
            environment( $1 ) == environment( this_player() ) ) :) )
            if ( !this_player()->query_property("dead") ) {
            add_failed_mess( "You are nowhere near wispy enough to "
            "haunt people.  You could probably scare a table or "
            "chair, though.\n" )
            return -1


    def cmd(self, ) -> int:
            if ( !this_player()->query_property("dead") ) {
            add_failed_mess( "You are nowhere near wispy enough to "
            "haunt people.  You could probably scare a table or "
            "chair, though.\n" )
            return -1



class Haunt(MudObject):
