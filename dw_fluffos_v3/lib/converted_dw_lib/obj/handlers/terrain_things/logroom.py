# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/terrain_things/logroom.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "limbo" )
            set_light( 50 )
            set_long( "You are between worlds, surrounded by raw potentiality and "+
            "not a lot else.\n" )
            add_item( "potentiality", "Well, it's sort of potentially something and "+
            "potentially nothing, and it can't quite decide at the moment.  "+
            "With any luck, though, you won't be here long enough to find "+
            "out...\n" )
            add_exit( "drum", "/d/am/am/mendeddrum", "path" )
            locations = ([ ])
            if ( file_size( SAVE_FILE +".o" ) )
            unguarded((: restore_object, SAVE_FILE :))


    def save_this(self, ) -> None:
            unguarded((: save_object, SAVE_FILE :))


    def player_quitting(self, player: MudObject, place: MudObject) -> None:
            if ( player.query_property( "guest" ) )
            return
            locations[ (string)player.query_name() ] =
            [(string)place.query_property( "terrain name" ),
            (int *)place.query_co_ord()]
            save_this()
            asyncio.create_task(self. "check_quitted", 5, (string)player.query_name() )


    def check_quitted(self, word: str) -> None:
            if ( !find_player( word ) )
            return
            if ( locations[ word ] )
            locations = m_delete( locations, word )
            save_this()


    def event_enter(self, player: MudObject, words: str, thing: MudObject) -> None:
            object location
            mixed *data
            data = locations[ (string)player.query_name() ]
            if ( !data ) {
            player.move( (string)player.query_start_pos(),
            "$N enter$s the game." )
            return



class Logroom(Room):
