# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/room/broken.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            void
            after_reset()
            {
            if ( !button )
            {
            button = clone_object( "/obj/misc/button" )
            button.move( self )


    def setup(self, ) -> None:
            set_light(100)
            set_short("Graveyard")
            set_long( "This room is full of broken bits and pieces of objects which "+
            "decided not to work or behave properly.\n" )


    def init(self, ) -> None:
            ::init()
            co_ord = 0



class Broken(MudObject):
