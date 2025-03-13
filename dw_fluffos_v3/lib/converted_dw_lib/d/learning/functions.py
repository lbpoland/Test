# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/functions.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            string word
            set_short( "room of function examples" )
            add_property( "determinate", "the " )
            set_long( "This is the room that might lead you to better understanding "
            "of how to use some of the functions we have here.\n"
            "Try \"list functions\" to get a list of the functions known by "
            "the room, "
            "take the exit named by the function to get to a room with exits "
            "to the examples.\n"
            "If you have something you'd like to see here, "
            "mail "+ CURRENT_LORD +" and suggest it.\n" )
            set_light( 50 )
            functions = SEARCH.query_functions()
            foreach( word in functions ) {
            add_exit( word, "??", "path" )
            modify_exit( word, ["obvious", 0] )


    def init(self, ) -> None:
            ::init()
            add_command( "list","functions")


    def do_list(self, ) -> int:
            write( sprintf( "The following functions have examples of use:\n%#-*s\n",
            75, implode( functions, "\n" ) ) )
            return 1


    def set_destination(self, word: str) -> None:
            if( word != "exit" ) {
            modify_exit( word, ["dest", SEARCH.find_function_room( word )] )



class Functions(MudObject):
