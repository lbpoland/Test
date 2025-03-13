# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/add_item/args_string.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "'add_item' room telling about getting string arguments" )
            set_light( 100 )
            add_property( "determinate", "the " )
            set_long( "This is the room telling about getting string arguments from a "
            "command defined with add_item.  Go east to see about getting "
            "object arguments, west to see about integer arguments.\n"
            "There is a large stone in the middle of the room.  It looks as "
            "if you can engrave your name onto it.\n")
            add_item( "large stone",
            ["long", "It can be engraved.",
            "engrave", [self, "do_engrave",
            "[the text] <string> [into] [the] <direct:object>"]
            }) )
            add_exit( "east", PATH +"args_object", "path")
            add_exit( "west", PATH +"args_integer", "path")
            add_exit( "start", MAIN, "path" )
            add_exit( "exit", LEARNING +"search", "path" )



class Args_string(Room):
