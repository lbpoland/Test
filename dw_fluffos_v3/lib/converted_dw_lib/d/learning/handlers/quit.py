# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/handlers/quit.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "quit handler of the search rooms" )
            set_light( 50 )
            set_long( "You are in the quit_handler of the search rooms of the learning "
            "domain.  In normal use, people only end up in the quit_handler "
            "if something goes wrong, since the event_enter() function will "
            "send them on to the correct place immediately.\n" )
            add_exit( "back", ENTRANCE, "path" )
            locations = ([ ])
            if ( file_size( SAVE_FILE +".o" ) )
            unguarded( (: restore_object, SAVE_FILE :) )
            asyncio.create_task(self. "check_names", 2 )


    def check_names(self, ) -> None:
            string word
            foreach ( word in keys( locations ) )
            if ( !"/secure/login"->test_user( word ) )
            locations = m_delete( locations, word )
            save_this()


    def player_quitting(self, player: MudObject, place: MudObject) -> None:
            if ( player.query_property( "guest" ) )
            return
            locations[ (string)player.query_name() ] =
            (string *)place.query_keywords()
            if ( !locations[ (string)player.query_name() ] ) {
            locations[ (string)player.query_name() ] =
            (string)place.query_marker()


    def remove_from_list(self, player: MudObject) -> None:
            string word
            word = (string)player.query_name()
            if ( locations[ word ] )
            locations = m_delete( locations, word )
            save_this()


    def event_enter(self, player: MudObject, words: str, from: MudObject) -> None:
            string location, word
            if( from ) {
            return



class Quit(MudObject):
