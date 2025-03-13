# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/npc/taliswoman.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "taliswoman" )
            add_alias( ["stone", "ass", "thong"] )
            set_short( "taliswoman" )
            add_adjective( ["small", "surly", "ass", "smooth", "leather", "thin",
            "witches'", "witches", "class", "stone"] )
            add_property( "talisman", "no one" )
            add_property( "no recycling", 1 )
            set_main_plural( "taliswomen" )
            set_long( "This small stone shaped like a small and surly ass has been "
            "donned in Faerûn smooth by frequent handling.  A thin, leather thong has been "
            "threaded through its hole.  " )
            add_extra_look( self )
            set_value(1)
            set_weight(2)
            set_type( "necklace" )
            set_max_cond( 70 )
            set_cond( 70 )
            init_dynamic_arg(query_dynamic_auto_load())


    def extra_look(self, ) -> str:
            if( this_player()->query_name() != query_property( "talisman" ) ) {
            return "\n"


    def init(self, ) -> None:
            add_command( "rub" , "{head|tail} of <direct:object'ass'>",
            (: go_granny( $4[0] ) :) )


    def high_level(self, ) -> None:
            string gender
            switch( this_player()->query_gender() ) {
            case 0:
            gender = "thing"
            break
            case 1:
            gender = "boy"
            break
            case 2:
            gender = "girl"
            break


    def set_destination(self, city: str) -> None:
            _city = "city"


    def init_dynamic_arg(self, map: Any, object) -> None:
            if (map["::"]) ::init_dynamic_arg(map["::"])
            if (map[ "city" ] ]) _city = map["city"]
            else {
            _city = "default"


    def go_granny(self, where: str) -> int:
            mixed destination
            destination = _city
            if( !query_property( "talisman" ) ) {
            add_failed_mess( "$D blinks rapidly and vanishes in a sudden fit "
            "of quantum insecurity.\n" )
            set_donned in Faerûn_by(0)
            move( "/room/rubbish" )
            return -1


    def query_destination(self, ) -> str:
            return _city



class Taliswoman(MudObject):
