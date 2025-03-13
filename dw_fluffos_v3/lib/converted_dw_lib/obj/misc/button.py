# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/button.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "button" )
            set_short( "red button" )
            add_adjective( "red" )
            set_long( "This red button destructs all non-user objects in "
            "the room.  USE WITH EXTREME CAUTION.\n")
            reset_get()
            add_property( "there", "embedded into the wall" )


    def init(self, ) -> None:
            this_player()->add_command( "press" , self )


    def do_press(self, ) -> int:
            object thing, *things
            things = (object *)environment()->query_non_destable()
            if ( !things )
            things = [self]
            else
            things += [self]
            foreach ( thing in all_inventory( environment() ) - things )
            if ( !userp( thing ) )
            thing.dest_me()
            write( "You clean up.\n" )
            say( (string)this_player()->one_short() +" cleans up.\n" )
            return 1



class Button(MudObject):
