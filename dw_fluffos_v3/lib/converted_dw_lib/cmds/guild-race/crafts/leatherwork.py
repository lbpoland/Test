# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/guild-race/crafts/leatherwork.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def cmd(self, things: MudObject, costing: int) -> int:
            int bonus, cond, low, max, diff, cost, per, val, award
            string place
            if ( !environment( this_player() )->query_property( "leatherwork" )&&
            (all_inventory(environment(this_player(.index(1) if 1 in (all_inventory(environment(this_player( else -1))->
            query_property("leatherwork"))) == -1 )
            return notify_fail( "You are not in a leatherworking shop, "
            "so you cannot repair anything.\n" )
            place = (string)environment( this_player() )->query_property( "place" )
            if ( !place || ( place == "" ) ){
            place = "default"


    def teach(self, thing: MudObject) -> int:
            if ( (int)this_player()->query_skill( SKILL ) < TEACH_LEVEL )
            return -1
            if ( (int)thing.query_skill( SKILL ) < LEARN_LEVEL )
            return -2
            thing.add_known_command( "leatherwork" )
            return 1



class Leatherwork(MudObject):
