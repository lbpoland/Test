# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/rodent.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "rodent" )
            set_long( "A generic rodent object.\n" )
            set_height( 10 )
            set_weight( 10 )
            set_desc( "a small rodent" )
            set_stats( [-4, 8, -4, -4, -6] )


    def new_set_level(self, args: Any) -> None:
            int level
            object thing
            if( sizeof(args) < 2 || !args[1] )
            return
            level = args[ 0 ]
            thing = args[ 1 ]
            level = 1 + ( 2 * args[ 0 ] + random( level ) ) / 10
            thing.add_ac( "blunt", "blunt", level )
            thing.add_ac( "sharp", "sharp", 2 + level )
            thing.add_ac( "pierce", "pierce", 2 * level )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = sqrt( number )
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "bite" )
            thing.add_attack( "bite", 100, [number, 5, number],
            "pierce", "unarmed", 0 )
            thing.tactics( "response dodge" )



class Rodent(MudObject):
