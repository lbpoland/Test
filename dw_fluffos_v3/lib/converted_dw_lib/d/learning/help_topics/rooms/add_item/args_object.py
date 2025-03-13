# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/add_item/args_object.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "'add_item' room telling about getting the object as argument" )
            set_light(100)
            add_property( "determinate", "the " )
            set_long( "This is the room telling about getting string arguments from a "
            "command defined with add_item.  Go east to see about getting "
            "string arguments, west to see about item conflicts.\n"
            "There is a large stone in the middle of the room.  It looks as "
            "if you can unlock it if you have the correct key.\n" )
            add_item( "large stone", ({
            "long","It can be unlocked.",
            "unlock", [self, "do_unlock",
            "<direct:object> [with] <indirect:object>"]
            }) )
            add_exit( "east", PATH +"item_conflicts", "path" )
            add_exit( "west", PATH +"args_string", "path" )
            add_exit( "start", MAIN, "path" )
            add_exit( "exit", LEARNING +"search", "path" )


    def reset(self, ) -> None:
            asyncio.create_task(self. "check_key", 2 )


    def check_key(self, ) -> None:
            if( !key ) {
            key = clone_object( "std/object" )
            key.set_name( "key" )
            key.set_short( "Mithal's key" )
            key.add_property( "Mithal", 1 )
            key->move( self, "Mithal sneaks through the room, "
            "dropping $N in the process." )



class Args_object(Room):
