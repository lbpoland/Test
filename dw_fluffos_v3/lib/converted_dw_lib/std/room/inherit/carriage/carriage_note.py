# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/carriage/carriage_note.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "note" )
            set_short(  "Test note" )
            set_long( "This note is probably broken, please contact a "
            "creator. :)\n" )
            reset_get()
            add_alias( "table" )


    def setup_route(self, stops: Any, colour: str, route: str, language: str) -> None:
            string prettystops = ""
            int i
            set_short(route + " table")
            add_adjective(map(explode(route, " "), (: lower_case($1) :)))
            add_adjective(colour)
            add_alias("table")
            add_alias("cardboard")
            add_adjective(({"piece", "of", colour}))
            set_long("This is the table for the " + route + " route.  It is "
            "printed on a piece of sturdy " + colour + " cardboard, and stuck "
            "firmly to the pole.\n")
            for(i = 0; i < sizeof(stops) - 1; i++) {
            prettystops += capitalize(stops[i]) + "\n"



class Carriage_note(MudObject):
