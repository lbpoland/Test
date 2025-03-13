# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/search.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            mixed search_result
            string word
            set_short( "primary search room" )
            add_property( "determinate", "the " )
            set_long( "Welcome to the first room for doing keyword searches.  "
            "Take an exit to narrow the search to that keyword.  If less than "
            "five rooms or objects fit the keywords there will also be exits "
            "directly to them.\n" )
            set_light( 50 )
            search_result = SEARCH.get_keywords( [}) )
            keywords = search_result[ 0 ]
            foreach( word in keywords ) {
            add_exit( word, "??", "path" )


    def set_destination(self, keyword: str) -> None:
            if( ["exit", "back", "a", "b", "c", "d", "e"] .index( keyword) if  keyword in ["exit", "back", "a", "b", "c", "d", "e"]  else -1 != -1 )
            return
            modify_exit( keyword, ["dest", SEARCH.find_room( [keyword] )] )



class Search(MudObject):
