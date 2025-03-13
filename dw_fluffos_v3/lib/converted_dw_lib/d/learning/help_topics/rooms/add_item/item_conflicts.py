# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/add_item/item_conflicts.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "'add_item' room telling about resolving item conflicts" )
            set_light( 100 )
            set_long( "This is the room telling about resolving item conflicts in "
            "items defined with add_item.\n"
            "This room still has some basic problems, and shouldn't be used "
            "as an example.\n"
            "Inside, add_item creates one "
            "object per room for its use and assigns an alias to each item "
            "pointing to this object.  Therefore it is likely that "
            "if you have multiple add_items with verbs that call functions "
            "you can run into problems.  In this room there is a fountain and "
            "a pool.  Both of these define 'toss'.  If the wrong function is "
            "called, then your function must return a 0 in order for the "
            "correct function to be called.  Otherwise you will have a bug!  "
            "Please look at this code and notice how each function checks to "
            "make sure that the appropriate pattern is used.  If this code "
            "were removed, then funny things would start to happen.:)\n" )
            add_item( "small fountain",
            ["long",
            "You can see a few platinum coins in the water.",
            "toss", [self, "do_throw_fount",
            "<number> platinum [coins|coin] into <direct:object>"]
            }) )
            add_item( "small pool",
            ["long", "You can see some silver coins lying around in the "
            "pool.",
            "toss", [ self,"do_throw_pool",
            "<number> silver [coins|coin] into <direct:object>"]
            }) )
            add_exit( "west", PATH + "args_object", "path" )
            add_exit( "start", MAIN, "path" )
            add_exit( "exit", LEARNING +"search", "path" )


    def do_success_thing(self, pool: int, silver: int, no: int) -> int:
            string coinstr, poolstr, nocoins
            if( no < 0 ) return 0
            if( silver ) coinstr = "silver"
            else coinstr = "platinum"
            if( pool ) poolstr = "pool"
            else poolstr = "fountain"
            nocoins = no+" "+coinstr+" coins"
            if( no == 1 ) nocoins = "one "+coinstr+" coin"
            this_player()->add_succeeded_mess( previous_object(),
            "$N $V "+ nocoins +" into a "+ poolstr +".\n", [}) )
            return 1



class Item_conflicts(Room):
