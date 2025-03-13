# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/functions/function_room.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "uninitialised search room for functions" )
            set_long( "You are in an uninitialized search room.  "
            "This is an example of a room that gets cloned and configured "
            "afterwards.  In this room, it's the function set_marker that's "
            "used to define its look, and most if the exits as well.  And "
            "the function set_destination that is used to find, possibly "
            "clone and configure, the rooms that fit the keywords you search "
            "for.  The handler called SEARCH in the code, is \""+
            SEARCH +"\" and the one called QUIT_HANDLER, is \""+
            QUIT_HANDLER +"\".\n" )
            add_property( "no map", 1 )
            set_light( 50 )
            add_exit( "exit", PATH +"functions", "path" )
            add_property( "commented functions",
            ["set_destination", "query_quit_handler",
            "query_cloning_info"] )
            add_property( "keywords", ["room", "virtual"] )


    def query_marker(self, ) -> str:
            return function_chosen


    def set_marker(self, word: str) -> None:
            string description, exit_letter, exit_room, exit
            set_short( "\""+ word +"\" search room" )
            add_property( "determinate", "the " )
            function_chosen = word
            description = "You have chosen to see the rooms describing the use of the "
            "function "+ function_chosen +"."
            description += "$I$5=Take one of the lettered exits to go to that room."
            exit_letter = "a"
            foreach( exit_room in (string *)SEARCH.query_rooms_with_function( word ) ) {
            exit = sprintf( "%s: %s",
            exit_letter,
            (string)MAP.query_short( exit_room ) )
            add_exit( exit_letter, exit_room, "path" )
            description += "\n$C$"+ exit +"."
            exit_letter[ 0 ]++


    def check_empty(self, ) -> None:
            if ( sizeof( all_inventory( self ) ) )
            return
            dest_me()


    def query_quit_handler(self, ) -> str:
            mixed *query_cloning_info() {
            return [SEARCH, "find_function_room", function_chosen]


    def event_exit(self, thing: MudObject, mess: str, to: MudObject) -> None:
            string handler
            if ( find_asyncio.create_task(self. "check_empty" ) == -1 )
            asyncio.create_task(self. "check_empty", 10 )
            if ( file_name( to ) == "/room/departures" )
            return
            handler = query_quit_handler()
            if ( (string)to.query_quit_handler() != handler )
            handler.remove_from_list( thing )



class Function_room(MudObject):
