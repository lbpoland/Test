# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/plate.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init(self, ) -> None:
            this_player()->add_command( "eat", self,
            "<indirect:object:direct-obs> {from|on} <direct:object:me>" )
            this_player()->add_command( "eat", self,
            "from <direct:object:me>" )


    def __init__(self):


    def do_eat(self, obs: MudObject, dir: str, indir: str, args: Any) -> int:
            object ob
            object *food
            if( sizeof( obs ) )
            food = copy( obs )
            else
            food = all_inventory()
            if( sizeof( food ) ) {
            food = filter( food, (: $1.query_edible() :) )
            } else {
            this_player()->add_failed_mess( self,
            "There's nothing on $D\n", [}) )
            return 0



class Plate(MudObject):
