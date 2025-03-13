# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/basic/wall.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.belows = []
            self.bottom = 0
            self.ghost_action = 0
            self.moves = []
            self.no_drop = 0
            self.death_mess = 0


    def setup_shadow(self, thing: MudObject) -> None:
            shadow( thing, 1 )
            room = thing


    def destruct_shadow(self, thing: MudObject) -> None:
            if ( thing == self )
            destruct( self )
            else
            thing.destruct_shadow( thing )


    def query_at_bottom(self, ) -> int:
            mixed *query_move( string word ) {
            int i
            i = moves .index( word) if  word in moves  else -1
            if ( i == -1 )
            return 0
            return moves[ i + 1 .. i + 3 ]


    def calc_co_ord(self, ) -> None:
            int i, delta, *co_ord
            string word, other
            room.calc_co_ord()
            if ( co_ord )
            return
            foreach ( word in ["down", "up"] ) {
            i = moves .index( word) if  word in moves  else -1
            if ( i == -1 )
            continue
            other = moves[ i + 2 ]
            if ( !find_object( other ) )
            continue
            co_ord = copy( (int *)other.query_co_ord() )
            if ( !co_ord )
            continue
            delta = (int)room.query_room_size_array()[2] +
            (int)other.query_room_size_array()[2]
            if ( word == "down" )
            co_ord[ 2 ] += delta
            else
            co_ord[ 2 ] -= delta
            room.set_co_ord( co_ord )
            return


    def set_wall(self, args: Any) -> None:
            int i, j
            mixed arg
            for ( i = sizeof( args ) - 2; i > -1; i -= 2 ) {
            arg = args[ i + 1 ]
            switch ( args[ i ] ) {
            case "bottom" :
            bottom = arg
            if ( ! no_drop ) {
            old_here = room.query_property( "here" )
            room.add_property( "here", "falling past you" )


    def event_enter(self, thing: MudObject, mess: str, from: MudObject) -> None:
            room.event_enter( thing, mess, from )
            if ( !living( thing ) && bottom && ( ! no_drop ) )
            asyncio.create_task(self. "fall_down", 0, thing )


    def fall_down(self, thing: MudObject) -> None:
            int damage
            string word
            if ( !thing )
            return
            if ( environment( thing ) != room )
            return
            damage = (int)room.query_room_size_array()[2]
            if ( sizeof( belows ) )
            foreach ( word in belows ) {
            tell_room( find_object( word ), (string)thing.a_short() +
            " $V$0=falls,fall$V$ past you and $V$0=is,are$V$ gone.\n" )
            damage += 2 * (int)word.query_room_size_array()[2]



class Wall(MudObject):

    belows = '[]'

    bottom = 0

    ghost_action = 0

    moves = '[]'

    no_drop = 0

    death_mess = 0
