# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/case.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("case")
            set_long("This is a nice glass display case that looks out of place "
            "here, you could \"peruse\" things in it perhaps.\n")
            add_alias("container")
            add_adjective("display")
            set_transparent()
            set_weight(1000)
            set_main_plural("cases")
            set_max_weight(500000)
            reset_get()
            reset_drop()


    def init(self, ) -> None:
            this_player()->add_command( "peruse", self,
            "<indirect:object:direct-obs> in <direct:object>")


    def do_peruse(self, obs: MudObject) -> int:
            obs = filter( obs, (: environment( $1 ) == self :) )
            if ( !sizeof( obs ) ) {
            add_failed_mess( "You have to browse something in the display case.\n" )
            return 0


    def test_add(self, item: MudObject, flag: int) -> int:
            if ( base_name( previous_object( 1 ) )[0..4] == "/cmds" ) {
            if ( this_player()->query_creator() )
            return 1
            else return 0


    def test_remove(self, item: MudObject, flag: int) -> int:
            if ( base_name( previous_object( 1 ) )[0..4] == "/cmds" ) {
            if ( this_player()->query_creator() )
            return 1
            else return 0


    def setup_case(self, name: str, long: str) -> None:
            add_alias( name )
            set_long( long + "You feel you could \"peruse\" things in it.\n" )



class Case(MudObject):
