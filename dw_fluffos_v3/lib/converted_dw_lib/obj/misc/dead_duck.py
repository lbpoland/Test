# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/dead_duck.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            {
            set_name( "duck" )
            set_short( "dead duck" )
            add_alias( ["corpse", "duck corpse"] )
            add_adjective( "dead" )
            set_main_plural( "dead ducks" )
            set_long( function()
            {
            if( plucked )
            return
            "This is the dead body of a bedraggled duck.  Judging "
            "from the lack of feathers it is ready to be "
            "cooked.\n"
            return
            "This is the dead body of a bedraggled duck.  "
            "Most people would pluck it and then cook it.\n"
            } )
            set_weight( 10 )
            set_value( 400 )
            set_weight_per_bite( 2 )


    def init(self, ) -> None:
            {
            ::init()
            this_player()->add_command( "pluck", self,
            "<direct:object:me-here>" )


    def query_dynamic_auto_load(self, ) -> Any:
            return ([ "::" : ::query_dynamic_auto_load(),
            "plucked" : plucked ])


    def init_dynamic_arg(self, arg: Any, object) -> None:
            ::init_dynamic_arg(arg["::"])
            plucked = arg["plucked"]



class Dead_duck(MudObject):
