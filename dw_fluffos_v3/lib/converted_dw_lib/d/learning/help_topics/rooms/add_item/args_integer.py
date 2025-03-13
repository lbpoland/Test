# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/add_item/args_integer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "'add_item' room telling about getting integer arguments" )
            set_light( 100 )
            add_property( "determinate", "the " )
            set_long( "This is the room telling about getting integer arguments from a "
            "command defined with add_item.  Go east to learn about getting "
            "string arguments, west to learn about the arguments passed "
            "to the function called when you do the command.\n"
            "This room is filled with an uncountable number of rats.  They "
            "all have numbers branded into them.  You can dissolve a rat if "
            "you know its number.\n" )
            add_item( "large filthy rat", ({
            "long", "The rats look vile.",
            "dissolve", [self, "do_dissolve",
            "<direct:object> [no|number] <number>"]
            }) )
            add_exit( "east", PATH +"args_string", "path")
            add_exit( "west", PATH +"func_arguments", "path")
            add_exit( "start", MAIN, "path" )
            add_exit( "exit", LEARNING +"search", "path" )



class Args_integer(Room):
